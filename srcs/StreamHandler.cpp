/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StreamHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file StreamHandler.cpp
 * @brief Implementation of the StreamHandler class for logging to output streams.
 */ 

#include "StreamHandler.hpp"
#include <iostream>

namespace log42
{
namespace handler
{

/**
 * @brief Constructs a StreamHandler with the specified output stream.
 *
 * @param stream Reference to the output stream to which log records will be written.
 */
StreamHandler::StreamHandler(std::ostream &stream) : Handler(), _stream(&stream) {}

/**
 * @brief Destructor for StreamHandler.
 */
StreamHandler::~StreamHandler() {}

/**
 * @brief Copy constructor for StreamHandler.
 *
 * @param rhs The StreamHandler instance to copy from.
 */
StreamHandler::StreamHandler(const StreamHandler &rhs) : Handler(rhs), _stream(rhs._stream) {}

/**
 * @brief Assignment operator for StreamHandler.
 *
 * @param rhs The StreamHandler instance to assign from.
 * @return Reference to this StreamHandler.
 */
StreamHandler	&StreamHandler::operator=(const StreamHandler &rhs)
{
	if (this != &rhs)
	{
		Handler::operator=(rhs);
		this->_stream = rhs._stream;
	}
	return (*this);
}

/**
 * @brief Flushes the associated output stream.
 */
void	StreamHandler::flush()
{
	if (this->_stream)
		this->_stream->flush();
}

/**
 * @brief Emits a log record to the associated output stream.
 *
 * @param record The log record to emit.
 */
void	StreamHandler::emit(logRecord::LogRecord &record)
{
	try
	{
		std::string msg = this->format(record);
		*this->_stream << msg << "\n";	
		this->flush();
	}
	catch (...)
	{
		this->handlerError(record);
	}
}

/**
 * @brief Sets a new output stream for the handler.
 *
 * @param stream Reference to the new output stream.
 * @return Reference to the previous output stream.
 */
std::ostream	&StreamHandler::setStream(std::ostream &stream)
{
	std::ostream	&old = *this->_stream;
	this->flush();
	this->_stream = &stream;
	return (old);
}

/**
 * @brief Returns a string representation of the StreamHandler.
 *
 * @return A string describing the StreamHandler and its log level.
 */
std::string	StreamHandler::toString() const
{
	return ("<StreamHandler (" + logRecord::levelToString(this->_level) + ")>");
}

} //!handler
} //!log42

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
