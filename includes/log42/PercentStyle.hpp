/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PercentStyle.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG42_PERCENTSTYLE_HPP
#define LOG42_PERCENTSTYLE_HPP

/**
 * @file PercentStyle.hpp
 * @brief Declares the PercentStyle class for formatting log records using 
 * percent-style formatting.
 */ 

#include <log42/LogRecord.hpp>
#include <log42/types.hpp>
#include <map>
#include <string>

namespace log42
{
namespace style
{

/**
 * @class PercentStyle
 * @brief Provides percent-style formatting for log records.
 *
 * This class allows formatting of log messages using a format string
 * with percent-style substitutions, similar to printf-style formatting.
 */
class PercentStyle
{
	public:
		static const std::string	defaultFormat;
		static const std::string	asctimeFormat;
		static const std::string	asctimeSearch;

		explicit PercentStyle(const std::string &fmt = defaultFormat,
			const t_defaults defaults = std::map<std::string, std::string>());
		virtual ~PercentStyle();

		PercentStyle(const PercentStyle &rhs);
		PercentStyle &operator=(const PercentStyle &rhs);

		std::string getFmt() const;

		bool				useTime() const;
		virtual void		validate() const;
		virtual std::string	format(const logRecord::LogRecord &record) const;
	
	protected:
		virtual std::string	_format(const logRecord::LogRecord &record) const;

	private:
		std::string	_fmt;
		t_defaults	_defaults;
};

} // !style
} // !log42

#endif // !LOG42_PERCENTSTYLE_HPP

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
