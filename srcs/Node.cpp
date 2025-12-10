/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Node.cpp
 * @brief Implements the Node base class for the logging hierarchy.
 */ 

#include <common/common.hpp>
#include <log42/Node.hpp>
#include <string>

namespace log42
{

/**
 * @brief Constructs a Node with the given name.
 *
 * @param name The name of the node.
 */
Node::Node(const std::string &name) : _name(name), _parent() {}

/**
 * @brief Destructor for Node.
 */
Node::~Node() {};

/**
 * @brief Copy constructor for Node.
 *
 * @param rhs The Node to copy.
 */
Node::Node(const Node &rhs) : _name(rhs._name), _parent(rhs._parent) {}

/**
 * @brief Assignment operator for Node.
 *
 * @param rhs The Node to assign from.
 * @return Reference to this Node.
 */
Node &Node::operator=(const Node &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_parent = rhs._parent;
	}
	return (*this);
}

/**
 * @brief Gets the name of the node.
 *
 * @return Reference to the node's name.
 */
const std::string	&Node::getName() const
{
	return (this->_name);
}

/**
 * @brief Gets the parent node.
 *
 * @return Pointer to the parent Node.
 */
common::core::raii::SharedPtr<Node> Node::getParent() const
{
	common::core::raii::SharedPtr<Node> parentSp = this->_parent.lock();
	return (parentSp);
}

/**
 * @brief Sets the parent node.
 *
 * @param parent Pointer to the parent Node.
 */
void	Node::setParent(const common::core::raii::SharedPtr<Node> &parent)
{
	this->_parent = common::core::raii::WeakPtr<Node>(parent);
}

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
