/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RootLogger.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOTLOGGER_HPP
#define ROOTLOGGER_HPP

/**
 * @file RootLogger.hpp
 * @brief Declares the RootLogger class, representing the root logger in the 
 * logging hierarchy.
 */ 

#include "Logger.hpp"
#include "LogRecord.hpp"

namespace log42
{
namespace logger
{

/**
 * @class RootLogger
 * @brief The root logger class, serving as the top-level logger in the logging 
 * system.
 *
 * RootLogger is a specialized Logger that acts as the root of the logger hierarchy.
 * It is responsible for handling log records at the highest level.
 */
class RootLogger : public Logger
{
	public:
		RootLogger(const logRecord::e_LogLevel level = logRecord::NOTSET);
		~RootLogger();

		std::string		toString() const;

	private:
		RootLogger(const RootLogger &rhs);
		RootLogger &operator=(RootLogger &rhs);
};

} // !logger
} // !log42

#endif // !ROOTLOGGER_HPP

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
