/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StreamHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG42_STREAMHANDLER_HPP
#define LOG42_STREAMHANDLER_HPP

/**
 * @file StreamHandler.hpp
 * @brief Declares the StreamHandler class for logging to output streams.
 */ 

#include <log42/Handler.hpp>
#include <log42/types.hpp>
#include <iostream>

namespace log42
{
namespace handler
{

/**
 * @class StreamHandler
 * @brief Handler that writes logging records to a given output stream.
 *
 * StreamHandler is responsible for emitting log records to a specified std::ostream,
 * such as std::cerr or std::cout.
 *
 * @startuml
 * class "StreamHandler" as StreamHandler {
		- _stream : ostream
		--
		+ StreamHandler(stream : ostream)
		+ flush() : void
		+ emit(record : LogRecord) : void
		+ setStream(ost : ostream) : ostream
		+ toString() : string
	}
 * @enduml
 */
class StreamHandler : public Handler
{
	public:
		explicit StreamHandler(std::ostream &stream = std::cerr);
		virtual ~StreamHandler();

		StreamHandler &operator=(const StreamHandler &rhs);
		StreamHandler(const StreamHandler &rhs);

		void			flush();
		void			emit(logRecord::LogRecord &record);
		std::ostream	&setStream(std::ostream &ost);
		std::string		toString() const;

	protected:
		std::ostream *_stream;

};

} // !handler
} // !log42

#endif // !LOG42_STREAMHANDLER_HPP

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
