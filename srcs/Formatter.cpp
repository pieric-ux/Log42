/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Formatter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Formatter.cpp
 * @brief Implements the Formatter class for formatting log records.
 */ 

#include "Formatter.hpp"
#include "PercentStyle.hpp"
#include "types.hpp"
#include <cstring>

namespace log42
{
namespace formatter
{

/**
 * @brief Default percent-style format string for log messages.
 */
const std::string Formatter::defaultPercentFormat = "%(levelname):%(name):%(message)";

/**
 * @brief Default time format string for log messages.
 */
const std::string Formatter::defaultTimeFormat = "%Y-%m-%d %H:%M:%S,%(msecs) %Z";

/**
 * @brief Pointer to the time converter function (default: localtime).
 */
struct std::tm *(*Formatter::_converter)(const time_t *) = localtime;

/**
 * @brief Constructs a Formatter with the given format and date format.
 *
 * @param fmt The format string for log messages.
 * @param datefmt The format string for timestamps.
 * @param validate If true, validates the format string.
 * @param defaults Default values for format fields.
 */
Formatter::Formatter(const std::string &fmt, const std::string &datefmt, 
					 bool validate, const t_defaults defaults)
	: _style(fmt.empty() ? defaultPercentFormat : fmt, defaults), 
	_fmt(this->_style.getFmt()), _datefmt(datefmt)
{
	if (validate)
		this->_style.validate();
}

/**
 * @brief Destructor for Formatter.
 */
Formatter::~Formatter() {}

/**
 * @brief Copy constructor for Formatter.
 *
 * @param rhs The Formatter to copy.
 */
Formatter::Formatter(const Formatter &rhs) :_style(rhs._style), _fmt(rhs._fmt), _datefmt(rhs._datefmt) {}

/**
 * @brief Assignment operator for Formatter.
 *
 * @param rhs The Formatter to assign from.
 * @return Reference to this Formatter.
 */
Formatter	&Formatter::operator=(const Formatter &rhs)
{
	if (this != &rhs)
	{
		this->_style = rhs._style;
		this->_fmt = rhs._fmt;
		this->_datefmt = rhs._datefmt;
	}
	return (*this);
}

/**
 * @brief Checks if the formatter uses time in its format.
 *
 * @return True if time is used, false otherwise.
 */
bool	Formatter::useTime() const
{
	return (this->_style.useTime());
}

/**
 * @brief Formats a log record's message using the style.
 *
 * @param record The log record to format.
 * @return The formatted message string.
 */
std::string	Formatter::formatMessage(const logRecord::LogRecord &record) const
{
	return (this->_style.format(record));
}

/**
 * @brief Formats a log record, including time if needed.
 *
 * @param record The log record to format.
 * @return The formatted log message.
 */
std::string	Formatter::format(logRecord::LogRecord &record) const
{
	record.setAsctime(Formatter::formatTime(record, this->_datefmt));
	return (formatMessage(record));
}

/**
 * @brief Formats the time for a log record.
 *
 * @param record The log record.
 * @param datefmt The date format string.
 * @return The formatted time string.
 */
std::string	Formatter::formatTime(const logRecord::LogRecord &record, const std::string &datefmt) const
{
	time_t	t = record.getCreated();
	struct std::tm *tm= this->_converter(&t);

	const std::string &fmt = datefmt.empty() ? defaultTimeFormat : datefmt;
	std::string buffer(100, 0);
	std::strftime(&buffer[0], buffer.size(), fmt.c_str(), tm);
	buffer.resize(std::strlen(&buffer[0]));

	return (buffer);
}

} // !formatter
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
