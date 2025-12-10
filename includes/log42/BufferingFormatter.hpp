/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BufferingFormatter.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG42_BUFFERINGFORMATTER_HPP
#define LOG42_BUFFERINGFORMATTER_HPP

/**
 * @file BufferingFormatter.hpp
 * @brief Declares the BufferingFormatter class for formatting multiple log records
 * with optional header and footer.
 */ 

#include <log42/Formatter.hpp>
#include <log42/types.hpp>

namespace log42
{
namespace formatter
{

/**
 * @class BufferingFormatter
 * @brief Formats a collection of log records, supporting custom header, footer, 
 * and line formatting.
 */
class BufferingFormatter
{
	public:
		explicit BufferingFormatter(const Formatter	&linefmt = Formatter());
		~BufferingFormatter();

		BufferingFormatter(const BufferingFormatter &rhs);
		BufferingFormatter &operator=(const BufferingFormatter &rhs);

		std::string	formatHeader(const t_records &records) const;
		std::string	formatFooter(const t_records &records) const;

		std::string format(t_records &records) const;

	private:
		Formatter _linefmt;
};

} // !formatter
} // !log42

#endif // !LOG42_BUFFERINGFORMATTER

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
