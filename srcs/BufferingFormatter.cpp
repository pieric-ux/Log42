/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BufferingFormatter.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file BufferingFormatter.cpp
 * @brief Implements the BufferingFormatter class for formatting batches of log records.
 */ 

#include "BufferingFormatter.hpp"
#include <sstream>

namespace log42
{
namespace formatter
{

/**
 * @brief Constructs a BufferingFormatter with a given line formatter.
 *
 * @param linefmt Reference to a Formatter used for individual log records.
 */
BufferingFormatter::BufferingFormatter(const Formatter &linefmt) : _linefmt(linefmt) {}

/**
 * @brief Destructor for BufferingFormatter.
 */
BufferingFormatter::~BufferingFormatter() {}

/**
 * @brief Copy constructor for BufferingFormatter.
 *
 * @param rhs The BufferingFormatter to copy.
 */
BufferingFormatter::BufferingFormatter(const BufferingFormatter &rhs) : _linefmt(rhs._linefmt) {}

/**
 * @brief Assignment operator for BufferingFormatter.
 *
 * @param rhs The BufferingFormatter to assign from.
 * @return Reference to this BufferingFormatter.
 */
BufferingFormatter	&BufferingFormatter::operator=(const BufferingFormatter &rhs)
{
	if (this != &rhs)
		this->_linefmt = rhs._linefmt;
	return (*this);
}

/**
 * @brief Formats the header for a batch of log records.
 *
 * @param records The vector of log records.
 * @return The formatted header string (default: empty).
 */
std::string	BufferingFormatter::formatHeader(const std::vector<logRecord::LogRecord> &records) const
{
	(void)records;
	return "";
}

/**
 * @brief Formats the footer for a batch of log records.
 *
 * @param records The vector of log records.
 * @return The formatted footer string (default: empty).
 */
std::string	BufferingFormatter::formatFooter(const std::vector<logRecord::LogRecord> &records) const
{
	(void)records;
	return "";
}

/**
 * @brief Formats a batch of log records using the line formatter, header, and footer.
 *
 * @param records The vector of log records to format.
 * @return The formatted string for the batch.
 */
std::string	BufferingFormatter::format(std::vector<logRecord::LogRecord> &records) const
{
	std::ostringstream	oss;
	oss << "";
	if (!records.empty())
	{
		oss << this->formatHeader(records);
		
		std::vector<logRecord::LogRecord>::iterator it;
		for (it = records.begin(); it != records.end(); ++it)
			oss << this->_linefmt.format(*it) << "\n";
		oss << this->formatFooter(records);

	}
	return (oss.str());
}

} //!formatter
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
