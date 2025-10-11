/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogRecord.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGRECORD_HPP
#define LOGRECORD_HPP

/**
 * @file LogRecord.hpp
 * @brief Defines the LogRecord class and related logging utilities.
 */ 

#include <ctime>
#include <string>
#include <vector>

namespace log42
{
namespace logRecord
{

/**
 * @enum e_LogLevel
 * @brief Enumeration of log levels.
 */
enum e_LogLevel { NOTSET, DEBUG, INFO, WARNING, ERROR, CRITICAL };
std::string levelToString(e_LogLevel level);

/**
 * @class LogRecord
 * @brief Represents a single log entry with metadata.
 */
class LogRecord
{
	public:
		LogRecord(const std::string &name,
					 const e_LogLevel level,
					 const std::string &pathname, 
					 const int lineno, 
					 const std::string &msg, 
					 const std::vector<std::string> *args, 
					 const std::string &func = "");
		~LogRecord();

		LogRecord(const LogRecord &rhs);
		LogRecord &operator=(const LogRecord &rhs);

		static	clock_t	&getStartTime();

		std::string	toString() const;

		std::string	getName() const;
		std::string	getMessage() const;
		e_LogLevel	getLevelNo() const;
		std::string	getLevelName() const;
		std::string	getPathname() const;
		std::string	getFilename() const;
		std::string	getModule() const;
		int			getLineNo() const;
		std::string	getFuncName() const;
		std::time_t	getCreated() const;
		long		getMsecs() const;
		double		getRelativeCreated() const;
		std::string	getAsctime() const;

		void		setAsctime(const std::string &asctime);

	private:
		static clock_t				_startTime;

		std::string					_name;
		std::string					_msg;
		std::vector<std::string>	_args;
		e_LogLevel					_levelNo;
		std::string					_levelName;
		std::string					_pathname;
		std::string					_filename;
		std::string					_module;
		int							_lineNo;
		std::string					_funcName;
		std::time_t					_created; 
		long						_msecs;
		double						_relativeCreated;
		std::string					_asctime;

};

} // !logRecord
} // !log42

#endif // !LOGRECORD_HPP

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
