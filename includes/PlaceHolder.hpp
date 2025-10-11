/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlaceHolder.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLACEHOLDER_HPP
#define PLACEHOLDER_HPP

/**
 * @file PlaceHolder.hpp
 * @brief Declares the PlaceHolder class for managing placeholder loggers in the logging hierarchy.
 */ 

#include "Node.hpp"
#include <set>

namespace log42
{
namespace placeholder
{

/**
 * @class PlaceHolder
 * @brief Represents a placeholder node for loggers not yet fully defined.
 *
 * PlaceHolder objects are used to temporarily hold references to loggers
 * that have not yet been fully constructed or attached in the logging hierarchy.
 */
class PlaceHolder : public Node
{
	public:
		explicit PlaceHolder(Node *alogger);
		~PlaceHolder();

		PlaceHolder(const PlaceHolder &rhs);
		PlaceHolder &operator=(const PlaceHolder &rhs);

		void append(Node *alogger);
		const std::set<Node *> &getLoggerSet() const;

		std::string toString() const;

	private:
		std::set<Node*> _loggerSet;
};

} // !placeholder
} // !log42

#endif // !PLACEHOLDER_HPP

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
