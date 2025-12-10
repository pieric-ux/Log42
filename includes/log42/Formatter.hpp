/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Formatter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG42_FORMATTER_HPP
#define LOG42_FORMATTER_HPP

/**
 * @file Formatter.hpp
 * @brief Declares the Formatter class for formatting log records with 
 * customizable formats and time handling.
 */ 

#include <log42/PercentStyle.hpp>
#include <log42/types.hpp>
#include <ctime>

namespace log42
{
namespace formatter
{

/**
 * @class Formatter
 * @brief Formats log records using percent-style formatting and optional time
 * formatting.
 */
class Formatter
{
	public:
		static const std::string	defaultPercentFormat;
		static const std::string	defaultTimeFormat;

		explicit Formatter(const std::string &fmt = defaultPercentFormat, 
			const std::string &datefmt = defaultTimeFormat, 
			bool validate = true,
			const t_defaults defaults = std::map<std::string, std::string>());
		~Formatter();

		Formatter(const Formatter &rhs);
		Formatter &operator=(const Formatter &rhs);

		bool		useTime() const;
		std::string	formatTime(const logRecord::LogRecord &record, const std::string &datefmt = "") const;
		std::string	formatMessage(const logRecord::LogRecord &record) const;
		std::string	format(logRecord::LogRecord &record) const;


	private:
		static struct std::tm		*(*_converter)(const time_t *);
		style::PercentStyle			_style;
		std::string					_fmt;
		std::string					_datefmt;
};

} // !formatter
} // !log42

#endif // !LOG42_FORMATTER_HPP

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
