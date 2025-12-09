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

#include "log42/logLevel.hpp"
#include "log42/types.hpp"
#include <ctime>
#include <string>

namespace log42
{
namespace logRecord
{

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
					 const t_args *args, 
					 const std::string &func = "");
		~LogRecord();

		LogRecord(const LogRecord &rhs);
		LogRecord &operator=(const LogRecord &rhs);

		static	clock_t	&getStartTime();

		std::string	toString() const;

		const std::string	&getName() const;
		std::string			getMessage() const;
		const e_LogLevel	&getLevelNo() const;
		const std::string	&getLevelName() const;
		const std::string	&getPathname() const;
		const std::string	&getFilename() const;
		const std::string	&getModule() const;
		const int			&getLineNo() const;
		const std::string	&getFuncName() const;
		const std::time_t	&getCreated() const;
		const long			&getMsecs() const;
		const double		&getRelativeCreated() const;
		const std::string	&getAsctime() const;

		void		setAsctime(const std::string &asctime);

	private:
		static clock_t	_startTime;

		std::string		_name;
		std::string		_msg;
		t_args			_args;
		e_LogLevel		_levelNo;
		std::string		_levelName;
		std::string		_pathname;
		std::string		_filename;
		std::string		_module;
		int				_lineNo;
		std::string		_funcName;
		std::time_t		_created; 
		long			_msecs;
		double			_relativeCreated;
		std::string		_asctime;

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
