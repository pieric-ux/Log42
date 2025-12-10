/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logLevel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/17                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG42_LOGLEVEL_HPP
#define LOG42_LOGLEVEL_HPP

/**
 * @file logLevel.hpp
 * @brief Defines log levels and utilities for converting log levels to strings.
 */ 

#include <string>

namespace log42
{
namespace logRecord
{

/**
 * @enum e_LogLevel
 * @brief Enumeration of log levels used for categorizing log messages.
 *
 * NOTSET   - No log level set.
 * DEBUG    - Detailed information, typically of interest only when diagnosing problems.
 * INFO     - Confirmation that things are working as expected.
 * WARNING  - An indication that something unexpected happened, or indicative of some problem.
 * ERROR    - Due to a more serious problem, the software has not been able to perform some function.
 * CRITICAL - A very serious error, indicating that the program itself may be unable to continue running.
 */
enum e_LogLevel { NOTSET, DEBUG, INFO, WARNING, ERROR, CRITICAL };

/**
 * @brief Converts a log level enum value to its corresponding string representation.
 *
 * @param level The log level to convert.
 * @return std::string The string representation of the log level.
 */
std::string levelToString(e_LogLevel level);

} // !logRecord
} // !log42

#endif // !LOG42_LOGLEVEL_HPP

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
