/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogRecord.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file LogRecord.cpp
 * @brief Implements the LogRecord class and related logging utilities.
 */ 

#include "fileUtils.hpp"
#include "timeUtils.hpp"
#include "LogRecord.hpp"
#include <ctime>
#include <string>
#include <sstream>

namespace logging
{
namespace logRecord 
{

/**
 * @brief Converts a log level enum to its string representation.
 *
 * @param level The log level.
 * @return The string representation of the log level.
 */
std::string	levelToString(e_LogLevel level)
{
	switch (level)
	{
		case DEBUG: return ("DEBUG");
		case INFO: return ("INFO");
		case WARNING: return ("WARNING");
		case ERROR: return ("ERROR");
		case CRITICAL: return ("CRITICAL");
		default: return ("UNKNOWN");
	}
}

/**
 * @brief Static variable to store the start time for relative timing.
 */
clock_t	LogRecord::_startTime = std::clock();

/**
 * @brief Gets the static start time for relative timing.
 *
 * @return Reference to the static start time.
 */
clock_t	&LogRecord::getStartTime()
{
	return (_startTime);
}

/**
 * @brief Constructs a LogRecord object with all metadata.
 *
 * @param name Logger name.
 * @param level Log level.
 * @param pathname Source file path.
 * @param lineNo Line number in source file.
 * @param msg Log message.
 * @param args Optional arguments for the message.
 * @param func Function name (optional).
 */
LogRecord::LogRecord(const std::string &name,
					 const e_LogLevel level,
					 const std::string &pathname, 
					 const int lineNo, 
					 const std::string &msg, 
					 const std::vector<std::string> *args, 
					 const std::string &func)
					 : _name(name), 
					 _msg(msg),
					 _args(args ? *args : std::vector<std::string>()),
					 _levelNo(level),
					 _levelName(levelToString(level)),
					 _pathname(pathname),
					 _filename(utils::filenameNoPath(pathname)),
					 _module(utils::filenameNoExt(this->_filename, ".cpp")),
					 _lineNo(lineNo),
					 _funcName(func),
					 _created(utils::nowSec()),
					 _msecs(utils::nowMilli()),
					 _relativeCreated(utils::relativeSec(this->_startTime)),
					 _asctime("") {}

/**
 * @brief Destructor for LogRecord.
 */
LogRecord::~LogRecord() {}

/**
 * @brief Copy constructor for LogRecord.
 *
 * @param rhs The LogRecord to copy.
 */
LogRecord::LogRecord(const LogRecord &rhs) 
	: _name(rhs._name), _msg(rhs._msg), _args(rhs._args), _levelNo(rhs._levelNo), 
	_levelName(rhs._levelName), _pathname(rhs._pathname), _filename(rhs._filename),
	_module(rhs._module), _lineNo(rhs._lineNo), _funcName(rhs._funcName),
	_created(rhs._created), _msecs(rhs._msecs), _relativeCreated(rhs._relativeCreated), 
	_asctime(rhs._asctime) {}

/**
 * @brief Assignment operator for LogRecord.
 *
 * @param rhs The LogRecord to assign from.
 * @return Reference to this LogRecord.
 */
LogRecord	&LogRecord::operator=(const LogRecord &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_msg = rhs._msg;
		this->_args = rhs._args;
		this->_levelNo = rhs._levelNo;
		this->_levelName = rhs._levelName;
		this->_pathname = rhs._pathname;
		this->_filename = rhs._filename;
		this->_module = rhs._module;
		this->_lineNo = rhs._lineNo;
		this->_funcName = rhs._funcName;
		this->_created = rhs._created;
		this->_msecs = rhs._msecs;
		this->_relativeCreated = rhs._relativeCreated;
		this->_asctime = rhs._asctime;
	}
	return (*this);
}

/**
 * @brief Returns a string representation of the log record.
 *
 * @return String representation.
 */
std::string	LogRecord::toString() const
{
	std::ostringstream oss;

	oss << "<LogRecord: "
		<< this->_name << ", "
		<< this->_levelNo << ", "
		<< this->_pathname << ", "
		<< this->_lineNo << ", \""
		<< this->_msg << "\">";
	return (oss.str());
}

/**
 * @brief Gets the logger name.
 *
 * @return Logger name.
 */
std::string	LogRecord::getName() const
{
	return (this->_name);
}

/**
 * @brief Gets the log message, substituting arguments if present.
 *
 * @return The formatted log message.
 */
std::string	LogRecord::getMessage() const
{
	if (this->_args.empty())
		return (this->_msg);

	std::string result = this->_msg;

	std::size_t pos = 0;
	std::vector<std::string>::const_iterator it;
	for (it = this->_args.begin(); it != this->_args.end() && (pos = result.find("%s", pos)) != std::string::npos; ++it)
	{
		result.replace(pos, 2, *it);
		pos += it->size();
	}
	return (result);
}

/**
 * @brief Gets the log level enum.
 *
 * @return Log level.
 */
e_LogLevel	LogRecord::getLevelNo() const
{
	return (this->_levelNo);
}

/**
 * @brief Gets the log level as a string.
 *
 * @return Log level name.
 */
std::string	LogRecord::getLevelName() const
{
	return (this->_levelName);
}

/**
 * @brief Gets the source file path.
 *
 * @return Pathname.
 */
std::string	LogRecord::getPathname() const
{
	return (this->_pathname);
}

/**
 * @brief Gets the source file name.
 *
 * @return Filename.
 */
std::string	LogRecord::getFilename() const
{
	return (this->_filename);
}

/**
 * @brief Gets the module name.
 *
 * @return Module name.
 */
std::string	LogRecord::getModule() const
{
	return (this->_module);
}

/**
 * @brief Gets the line number in the source file.
 *
 * @return Line number.
 */
int	LogRecord::getLineNo() const
{
	return (this->_lineNo);
}

/**
 * @brief Gets the function name.
 *
 * @return Function name.
 */
std::string	LogRecord::getFuncName() const
{
	return (this->_funcName);
}

/**
 * @brief Gets the creation time (seconds since epoch).
 *
 * @return Creation time.
 */
std::time_t	LogRecord::getCreated() const
{
	return (this->_created);
}

/**
 * @brief Gets the milliseconds since epoch.
 *
 * @return Milliseconds.
 */
long	LogRecord::getMsecs() const
{
	return (this->_msecs);
}

/**
 * @brief Gets the time since start (relative creation time).
 *
 * @return Relative creation time.
 */
double	LogRecord::getRelativeCreated() const
{
	return (this->_relativeCreated);
}

/**
 * @brief Gets the formatted time string.
 *
 * @return Asctime string.
 */
std::string	LogRecord::getAsctime() const
{
	return (this->_asctime);
}

/**
 * @brief Sets the formatted time string.
 *
 * @param asctime The formatted time string.
 */
void	LogRecord::setAsctime(const std::string &asctime)
{
	this->_asctime = asctime;
}

} //!logRecord
} //!logging

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
