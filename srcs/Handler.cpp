/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Handler.cpp
 * @brief Implements the Handler class for processing and emitting log records.
 */ 

#include "log42/Filterer.hpp"
#include "log42/Handler.hpp"
#include "log42/LogRecord.hpp"
#include <iostream>

namespace log42
{
namespace handler 
{

/**
 * @brief Constructs a Handler with the specified log level.
 *
 * @param level The minimum log level for this handler.
 */
Handler::Handler(const logRecord::e_LogLevel level) 
	: filterer::Filterer(), 
	_name(""), 
	_level(level), 
	_formatter(), 
	_closed(false) 
{}

/**
 * @brief Destructor for Handler.
 */
Handler::~Handler() {};

/**
 * @brief Copy constructor for Handler.
 *
 * @param rhs The Handler to copy.
 */
Handler::Handler(const Handler &rhs) : filterer::Filterer(rhs), _name(rhs._name), _level(rhs._level), _formatter(rhs._formatter), _closed(rhs._closed) {}

/**
 * @brief Assignment operator for Handler.
 *
 * @param rhs The Handler to assign from.
 * @return Reference to this Handler.
 */
Handler	&Handler::operator=(const Handler &rhs)
{
	if (this != &rhs)
	{
		filterer::Filterer::operator=(rhs);
		this->_name = rhs._name;
		this->_level = rhs._level;
		this->_formatter = rhs._formatter;
		this->_closed = rhs._closed;
	}
	return (*this);
}

/**
 * @brief Gets the name of the handler.
 *
 * @return Reference to the handler's name.
 */
const std::string	&Handler::getName() const
{
	return (this->_name);
}

/**
 * @brief Sets the name of the handler.
 *
 * @param name The new name for the handler.
 */
void	Handler::setName(const std::string &name)
{
	this->_name = name;
}

/**
 * @brief Gets the log level of the handler.
 *
 * @return The log level.
 */
logRecord::e_LogLevel	Handler::getLevel() const
{
	return (this->_level);
}

/**
 * @brief Sets the log level of the handler.
 *
 * @param level The new log level.
 */
void	Handler::setLevel(const logRecord::e_LogLevel level)
{
	this->_level = level;
}

/**
 * @brief Formats a log record using the handler's formatter.
 *
 * @param record The log record to format.
 * @return The formatted log message.
 */
std::string	Handler::format(logRecord::LogRecord &record) const
{
	return (this->_formatter.format(record));
}

/**
 * @brief Handles a log record: filters, checks level, emits, and handles errors.
 *
 * @param record The log record to handle.
 * @return True if the record was handled, false otherwise.
 */
bool	Handler::handle(logRecord::LogRecord &record)
{
	if (this->_closed)
		return (false);
	if (!this->filter(record))
		return (false);
	if (record.getLevelNo() < this->_level)
		return (false);
	try
	{
		this->emit(record);
	}
	catch (...)
	{
		this->handlerError(record);
		return (false);
	}
	return (true);
}

/**
 * @brief Gets the formatter used by this handler.
 *
 * @return Reference to the formatter.
 */
const formatter::Formatter	&Handler::getFormatter() const
{
	return (this->_formatter);
}

/**
 * @brief Sets the formatter for this handler.
 *
 * @param fmt The formatter to use.
 */
void	Handler::setFormatter(const formatter::Formatter &fmt)
{
	this->_formatter = fmt;
}

/**
 * @brief Closes the handler, preventing further handling of log records.
 */
void	Handler::close()
{
	this->_closed = true;
}

/**
 * @brief Handles errors that occur during record emission.
 *
 * @param record The log record that caused the error.
 */
void	Handler::handlerError(const logRecord::LogRecord &record) const
{
	std::cerr << "--- Logging error ---\n";
	std::cerr << "Logged from file " << record.getFilename() << ", at line " << record.getLineNo() << "\n";
	std::cerr << "Function: " << record.getFuncName() << "\n";
	std::cerr << "Logger: " << record.getName() << "\n";
	std::cerr << "Level: " << record.getLevelName() << "\n";
	std::cerr << "Message: " << record.getMessage() << std::endl;
}

/**
 * @brief Returns a string representation of the handler.
 *
 * @return String representation.
 */
std::string	Handler::toString() const
{
	return ("<Handler (" + logRecord::levelToString(this->_level) + ")>");
}

} // !handler
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
