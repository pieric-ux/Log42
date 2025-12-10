/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlaceHolder.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/11/10 22:09:35 by pdemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file PlaceHolder.cpp
 * @brief Implements the PlaceHolder class for managing placeholder loggers.
 */ 

#include <common/common.hpp>
#include <log42/Node.hpp>
#include <log42/PlaceHolder.hpp>

namespace log42
{
namespace placeholder
{

/**
 * @brief Constructs a PlaceHolder with an initial logger.
 *
 * @param alogger Pointer to the initial logger node.
 */
PlaceHolder::PlaceHolder(const common::core::raii::SharedPtr<Node> &alogger) : Node(alogger ? alogger->getName() : ""), _loggerSet()
{
	if (alogger)
		this->_loggerSet.insert(alogger);
};

/**
 * @brief Destructor for PlaceHolder.
 */
PlaceHolder::~PlaceHolder() {}

/**
 * @brief Copy constructor for PlaceHolder.
 *
 * @param rhs The PlaceHolder to copy.
 */
PlaceHolder::PlaceHolder(const PlaceHolder &rhs) : Node(rhs), _loggerSet(rhs._loggerSet) {}

/**
 * @brief Assignment operator for PlaceHolder.
 *
 * @param rhs The PlaceHolder to assign from.
 * @return Reference to this PlaceHolder.
 */
PlaceHolder &PlaceHolder::operator=(const PlaceHolder &rhs) 
{
	if (this != &rhs)
	{
		Node::operator=(rhs);
		this->_loggerSet = rhs._loggerSet;
	}
	return (*this);
}

/**
 * @brief Appends a logger node to the placeholder set.
 *
 * @param alogger Pointer to the logger node to append.
 */
void	PlaceHolder::append(const common::core::raii::SharedPtr<Node> &alogger)
{
	if (alogger)
		this->_loggerSet.insert(alogger);
}

/**
 * @brief Gets the set of logger nodes associated with this placeholder.
 *
 * @return Reference to the set of logger node pointers.
 */
const std::set<common::core::raii::SharedPtr<Node> > &PlaceHolder::getLoggerSet() const
{
	return (this->_loggerSet);
}


/**
 * @brief Returns a string representation of the placeholder.
 *
 * @return String representation.
 */
std::string PlaceHolder::toString() const
{
	return ("<PlaceHolder " + getName());
}

} // !placeholder
} // !log42

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
