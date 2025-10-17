/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SharedPtr.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/16                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP

/**
 * @file SharedPtr.hpp
 * @brief Implementation of a reference-counted shared ownership smart pointer 
 * with customizable deleter.
 */

#include "common/core/utils/algoUtils.hpp"
#include "common/core/raii/Deleters.hpp"
#include <cstddef>

namespace common
{
namespace core
{
namespace raii
{

/**
 * @def MAKE_SHARED(TYPE, ...)
 * @brief Helper macro to create a SharedPtr for a single object.
 *
 * Constructs a SharedPtr of the specified TYPE, forwarding any constructor arguments.
 */
#define MAKE_SHARED(TYPE, ...) SharedPtr<TYPE>(new TYPE(__VA_ARGS__))

/**
 * @def MAKE_SHARED_ARRAY(TYPE, SIZE)
 * @brief Helper macro to create a SharedPtr for an array.
 *
 * Constructs a SharedPtr for an array of TYPE with the given SIZE.
 */
#define MAKE_SHARED_ARRAY(TYPE, SIZE) SharedPtr<TYPE[]>(new TYPE[SIZE])

/**
 * @class SharedPtrBase
 * @brief Base class for reference-counted shared ownership smart pointers.
 *
 * Manages a pointer, a deleter, and a reference count for shared ownership.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 */
template<typename T, typename Deleter>
class SharedPtrBase
{
	public:
		void			reset(T *ptr = 0) throw();
		void			swap(SharedPtrBase &other) throw();

		T				*get() const throw();
		Deleter			&getDeleter() throw();
		const Deleter	&getDeleter() const throw();

		std::size_t		useCount() const throw();
		bool			unique() const throw();

	protected:
		T				*_ptr;
		Deleter			_deleter;
		std::size_t		*_count;

		explicit SharedPtrBase(T *ptr = 0, Deleter deleter = Deleter()) throw();
		~SharedPtrBase();

		SharedPtrBase(const SharedPtrBase &rhs) throw();
		SharedPtrBase &operator=(const SharedPtrBase &rhs) throw();
};

/**
 * @class SharedPtr
 * @brief Reference-counted shared ownership smart pointer for single objects.
 *
 * Provides shared ownership semantics for a dynamically allocated object.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor (default: DefaultDelete<T>).
 */
template<typename T, typename Deleter = DefaultDelete<T> >
class SharedPtr : public SharedPtrBase<T, Deleter>
{
	public:
		typedef SharedPtrBase<T, Deleter> Base;

		explicit SharedPtr(T *ptr = 0, Deleter deleter = Deleter()) throw() : Base(ptr, deleter) {}
		~SharedPtr() {}

		SharedPtr(const SharedPtr &rhs) throw() : Base(rhs) {}
		SharedPtr &operator=(const SharedPtr &rhs) throw()
		{
			Base::operator=(rhs);
			return (*this);
		}

		T	*operator->() const throw();
		T	&operator*() const throw();
};

/**
 * @class SharedPtr<T[], Deleter>
 * @brief Reference-counted shared ownership smart pointer specialization for arrays.
 *
 * Provides shared ownership semantics for a dynamically allocated array.
 *
 * @tparam T Type of the managed array elements.
 * @tparam Deleter Type of the deleter functor.
 */
template<typename T, typename Deleter>
class SharedPtr<T[], Deleter> : SharedPtrBase<T, Deleter>
{
	public:
		typedef SharedPtrBase<T, Deleter> Base;

		explicit SharedPtr(T *ptr = 0, Deleter deleter = Deleter()) throw() : Base(ptr, deleter) {}
		~SharedPtr() {}

		SharedPtr(const SharedPtr &rhs) throw() : Base(rhs) {}
		SharedPtr &operator=(const SharedPtr &rhs) throw()
		{
			Base::operator=(rhs);
			return (*this);
		}

		T	&operator[](std::size_t i) const;
};

/**
 * @brief Constructs a SharedPtrBase with a pointer and deleter.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @param ptr The pointer to manage.
 * @param deleter The deleter to use.
 */
template<typename T, typename Deleter>
SharedPtrBase<T, Deleter>::SharedPtrBase(T *ptr, Deleter deleter) throw() : _ptr(ptr), _deleter(deleter), _count(0)
{
	if (this->_ptr)
		this->_count = new std::size_t(1);
}

/**
 * @brief Destructor. Decrements reference count and deletes managed pointer if needed.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 */
template<typename T, typename Deleter>
SharedPtrBase<T, Deleter>::~SharedPtrBase()
{
	reset();
}

/**
 * @brief Copy constructor. Increments reference count.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @param rhs SharedPtrBase to copy from.
 */
template<typename T, typename Deleter>
SharedPtrBase<T, Deleter>::SharedPtrBase(const SharedPtrBase &rhs) throw() : _ptr(rhs._ptr), _deleter(rhs._deleter), _count(rhs._count)
{
	if (this->_count)
		++(this->_count);
}

/**
 * @brief Assignment operator. Handles reference count and pointer management.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @param rhs SharedPtrBase to assign from.
 * @return Reference to this instance.
 */
template<typename T, typename Deleter>
SharedPtrBase<T, Deleter>	&SharedPtrBase<T, Deleter>::operator=(const SharedPtrBase &rhs) throw()
{
	if (this != &rhs)
	{
		this->reset();
		this->_ptr = rhs._ptr;
		this->_deleter = rhs._deleter;
		this->_count = rhs._count;
		if (this->_count)
			++(*this->_count);
	}
	return (*this);
}

/**
 * @brief Replaces the managed pointer with a new one, updating reference count and deleting if necessary.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @param ptr The new pointer to manage.
 */
template<typename T, typename Deleter>
void	SharedPtrBase<T, Deleter>::reset(T *ptr) throw()
{
	if (this->_ptr == ptr)
		return ;
	if (this->_count && --(*this->_count) == 0)
	{
		this->_deleter(this->_ptr);
		delete this->_count;
	}

	if (ptr)
	{
		this->_ptr = ptr;
		this->_count = new std::size_t(1);
	}
	else
	{
		this->_ptr = 0;
		this->_count = 0;
	}
}

/**
 * @brief Swaps the managed pointer, deleter, and reference count with another SharedPtrBase.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @param other The other SharedPtrBase to swap with.
 */
template<typename T, typename Deleter>
void	SharedPtrBase<T, Deleter>::swap(SharedPtrBase &other) throw()
{
	utils::swap(this->_ptr, other._ptr);
	utils::swap(this->_deleter, other._deleter);
	utils::swap(this->_count, other._count);
}

/**
 * @brief Gets the managed pointer.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @return The managed pointer.
 */
template<typename T, typename Deleter>
T	*SharedPtrBase<T, Deleter>::get() const throw()
{
	return (this->_ptr);
}

/**
 * @brief Gets a reference to the deleter.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @return Reference to the deleter.
 */
template<typename T, typename Deleter>
Deleter	&SharedPtrBase<T, Deleter>::getDeleter() throw()
{
	return (this->_deleter);
}

/**
 * @brief Gets a const reference to the deleter.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @return Const reference to the deleter.
 */
template<typename T, typename Deleter>
const Deleter	&SharedPtrBase<T, Deleter>::getDeleter() const throw()
{
	return (this->_deleter);
}

/**
 * @brief Gets the number of SharedPtr instances sharing ownership.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @return Reference count.
 */
template<typename T, typename Deleter>
std::size_t		SharedPtrBase<T, Deleter>::useCount() const throw()
{
	return (this->_count ? *this->_count : 0);
}

/**
 * @brief Checks if this is the only SharedPtr owning the managed pointer.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @return True if unique, false otherwise.
 */
template<typename T, typename Deleter>
bool	SharedPtrBase<T, Deleter>::unique() const throw()
{
	return (this->useCount() == 1);
}

/**
 * @brief Member access operator for SharedPtr.
 * 
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @return Pointer to the managed object.
 */
template<typename T, typename Deleter>
T	*SharedPtr<T, Deleter>::operator->() const throw()
{
	return (this->_ptr);
}

/**
 * @brief Dereference operator for SharedPtr.
 *
 * @tparam T Type of the managed object.
 * @tparam Deleter Type of the deleter functor.
 * @return Reference to the managed object.
 */
template<typename T, typename Deleter>
T	&SharedPtr<T, Deleter>::operator*() const throw()
{
	return (*this->_ptr);
}

/**
 * @brief Array subscript operator for SharedPtr<T[], Deleter>.
 *
 * @tparam T Type of the managed array elements.
 * @tparam Deleter Type of the deleter functor.
 * @param i Index of the element.
 * @return Reference to the element at index i.
 */
template<typename T, typename Deleter>
T	&SharedPtr<T[], Deleter>::operator[](std::size_t i) const
{
	return (this->_ptr[i]);
}

} // !raii
} // !core
} // !common

#endif // !SHAREDPTR_HPP

/* ************************************************************************** */
/*                                                                            */
/*                                MIT License                                 */
/*                                                                            */
/*   Copyright (c) 2025 Demont Pieric, Lucken Bénédict                        */
/*                                                                            */
/*   Inspired by the Python 'logging' module by Vinay Sajip.                  */
/*   This implementation was rewritten in C++98 and contains no original      */
/*   Python source code.                                                      */
/*                                                                            */
/*   Permission is hereby granted, free of charge, to any person obtaining    */
/*   a copy of this software and associated documentation files (the          */
/*   "Software"), to deal in the Software without restriction, including      */
/*   without limitation the rights to use, copy, modify, merge, publish,      */
/*   distribute, sublicense, and/or sell copies of the Software, and to       */
/*   permit persons to whom the Software is furnished to do so, subject to    */
/*   the following conditions:                                                */
/*                                                                            */
/*   The above copyright notice and this permission notice shall be included  */
/*   in all copies or substantial portions of the Software.                   */
/*                                                                            */
/*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  */
/*   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               */
/*   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   */
/*   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     */
/*   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     */
/*   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        */
/*   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   */
/*                                                                            */
/* ************************************************************************** */
