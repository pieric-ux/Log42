/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG42_NODE_HPP
#define LOG42_NODE_HPP

/**
 * @file Node.hpp
 * @brief Declares the Node base class for representing nodes in the logging hierarchy.
 */ 

#include <common/common.hpp>
#include <string>

namespace log42
{

/**
 * @class Node
 * @brief Abstract base class representing a node in the logging hierarchy.
 */
class Node
{
	public:
		explicit Node(const std::string &name);
		virtual ~Node();

		Node(const Node &rhs);
		Node &operator=(const Node &rhs);

		const std::string	&getName() const;
		/**
		 * @brief Get the parent node (non-owning).
		 *
		 * NOTE: The returned pointer is non-owning. Node lifetimes are managed
		 * centrally (for example by `Manager` using `raii::SharedPtr`). Do not
		 * delete the returned pointer.
		 */
		common::core::raii::SharedPtr<Node>    getParent() const;
		/**
		 * @brief Set the parent node (non-owning).
		 *
		 * @param Parent SharedPtr to the parent node. Ownership is not transferred
	 * (the Manager typically holds the owning SharedPtr); the child will store
	 * a WeakPtr reference.
		 */
		void			setParent(const common::core::raii::SharedPtr<Node> &Parent);

		virtual std::string toString() const = 0;

	protected:
		std::string _name;
		/**
		 * Non-owning pointer to the parent node. Ownership is managed elsewhere
		 * (e.g. Manager with raii::SharedPtr). This raw pointer must not be
		 * deleted by the child.
		 */
	common::core::raii::WeakPtr<Node>	_parent;
		
};

} //!log42

#endif // !LOG42_NODE_HPP

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
