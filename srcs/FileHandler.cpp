/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file FileHandler.cpp
 * @brief Implements the FileHandler class for logging to files.
 */

#include "FileHandler.hpp"
#include <fstream>
#include <string>

namespace log42
{
namespace handler
{

/**
 * @brief Constructs a FileHandler for logging to a file.
 *
 * @param filename The name of the file to log to.
 * @param mode The file open mode (e.g., std::ios_base::out).
 * @param delay If true, delays file opening until the first log record is emitted.
 */
FileHandler::FileHandler(const std::string &filename, 
						 const std::ios_base::openmode &mode, 
						 bool delay) 
	: StreamHandler(), _baseFilename(filename), _mode(mode), _delay(delay), _fstream()
{
	if (!this->_delay)
	{
		this->_open();
		this->_stream = &this->_fstream;
	}
	else
		this->_stream = NULL;

}

/**
 * @brief Destructor for FileHandler. Closes the file if open.
 */
FileHandler::~FileHandler() 
{
	this->close();
}

/**
 * @brief Closes the file stream and flushes any buffered output.
 */
void	FileHandler::close()
{
	if (this->_stream)
	{
		this->flush();
		this->_fstream.close();
		this->_stream = NULL;
	}
	this->_closed = true;
}

/**
 * @brief Opens the file stream if it is not already open.
 */
void	FileHandler::_open()
{
	if (this->_fstream.is_open())
		return ;
	this->_fstream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	this->_fstream.open(this->_baseFilename.c_str(), this->_mode);
}

/**
 * @brief Emits a log record to the file, opening the file if necessary.
 *
 * @param record The log record to emit.
 */
void	FileHandler::emit(logRecord::LogRecord &record)
{
	if (!this->_stream)
	{
		if (this->_mode != std::ios_base::out || !this->_closed)
		{
			this->_open();
			this->_stream = &this->_fstream;
		}
	}
	if (this->_stream)
		StreamHandler::emit(record);
}

/**
 * @brief Returns a string representation of the FileHandler.
 *
 * @return String representation.
 */
std::string	FileHandler::toString() const
{
	return ("<FileHandler (" + logRecord::levelToString(this->_level) + ")>");
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
