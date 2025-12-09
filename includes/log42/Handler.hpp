/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
#define HANDLER_HPP

/**
 * @file Handler.hpp
 * @brief Declares the Handler base class for processing and emitting log records.
 */ 

#include "log42/Filterer.hpp"
#include "log42/Formatter.hpp"
#include "log42/LogRecord.hpp"
#include "log42/types.hpp"

namespace log42
{
namespace handler
{

/**
 * @class Handler
 * @brief Abstract base class for log handlers that process and emit log records.
 *        Supports filtering, formatting, and error handling.
 */
class Handler : public filterer::Filterer
{
	public:
		explicit Handler(const logRecord::e_LogLevel level = logRecord::NOTSET);
		virtual ~Handler();

		Handler(const Handler &rhs);
		Handler &operator=(const Handler &rhs);

		const std::string			&getName() const;
		void						setName(const std::string &name);
		logRecord::e_LogLevel		getLevel() const;
		void						setLevel(const logRecord::e_LogLevel level);
		std::string					format(logRecord::LogRecord &record) const;
		virtual void				emit(logRecord::LogRecord &record) = 0;
		bool						handle(logRecord::LogRecord &record);
		const formatter::Formatter	&getFormatter() const;
		void						setFormatter(const formatter::Formatter &fmt);
		virtual void				flush() = 0;
		virtual void				close();
		void						handlerError(const logRecord::LogRecord &record) const;	
		virtual std::string			toString() const;

	protected:
		std::string				_name;
		logRecord::e_LogLevel	_level;
		formatter::Formatter	_formatter;
		bool					_closed;
};

} // !handler
} // !log42

#endif // !HANDLER_HPP

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
