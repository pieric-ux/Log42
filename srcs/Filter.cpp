/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filter.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Filter.cpp
 * @brief Implements the Filter class for filtering log records by logger name.
 */ 

#include "Filter.hpp"

namespace log42
{
namespace filter
{

/**
 * @brief Constructs a Filter with the specified logger name.
 *
 * @param name The logger name or prefix to filter on.
 */
Filter::Filter(const std::string &name) : _name(name), _len(name.length()) {}

/**
 * @brief Destructor for Filter.
 */
Filter::~Filter() {}

/**
 * @brief Copy constructor for Filter.
 *
 * @param rhs The Filter to copy.
 */
Filter::Filter(const Filter &rhs) : _name(rhs._name), _len(rhs._len) {}

/**
 * @brief Assignment operator for Filter.
 *
 * @param rhs The Filter to assign from.
 * @return Reference to this Filter.
 */
Filter	&Filter::operator=(const Filter &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_len = rhs._len;
	}
	return (*this);
}

/**
 * @brief Less-than comparison operator for Filter.
 *
 * @param rhs The Filter to compare with.
 * @return True if this Filter's name is less than rhs's name.
 */
bool	Filter::operator<(const Filter &rhs) const
{
	return (this->_name < rhs._name);
}

/**
 * @brief Equality comparison operator for Filter.
 *
 * @param rhs The Filter to compare with.
 * @return True if both Filters have the same name and length.
 */
bool	Filter::operator==(const Filter &rhs) const
{
	return (this->_name == rhs._name && this->_len == rhs._len);
}

/**
 * @brief Determines if a log record passes the filter.
 *
 * @param record The log record to check.
 * @return True if the record's logger name matches the filter.
 */
bool	Filter::filter(const logRecord::LogRecord &record) const
{
	if (this->_len == 0)
		return (true);
	
	const std::string name = record.getName();
	
	if (this->_name == name)
		return (true);
	if (name.compare(0, this->_len, this->_name) != 0)
		return (false);
	return (name.size() > this->_len && name[this->_len] == '.');
}

} // !filter
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
