/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log42.hpp                                        :+:      :+:    :+:     */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG42_LOGGING_HPP
#define LOG42_LOGGING_HPP

/**
 * @file Log42.hpp
 * @brief Main logging interface, macros, and utility functions for the 
 * logging system.
 */ 

#include <log42/BufferingFormatter.hpp>
#include <log42/FileHandler.hpp>
#include <log42/Filter.hpp>
#include <log42/Filterer.hpp>
#include <log42/Formatter.hpp>
#include <log42/Handler.hpp>
#include <log42/Logger.hpp>
#include <log42/Manager.hpp>
#include <log42/StreamHandler.hpp>
#include <log42/types.hpp>
#include <fstream>
#include <set>
#include <string>

namespace log42
{
/**
 * @def ROOT_DEBUG(msg, ...)
 * @brief Logs a debug message using the root logger, including file, line, and function info.
 */
#define ROOT_DEBUG(msg, ...)	ensureRootReady()->debug((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def ROOT_INFO(msg, ...)
 * @brief Logs an info message using the root logger, including file, line, and function info.
 */
#define ROOT_INFO(msg, ...)		ensureRootReady()->info((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def ROOT_WARNING(msg, ...)
 * @brief Logs a warning message using the root logger, including file, line, and function info.
 */
#define ROOT_WARNING(msg, ...)	ensureRootReady()->warning((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def ROOT_ERROR(msg, ...)
 * @brief Logs an error message using the root logger, including file, line, and function info.
 */
#define ROOT_ERROR(msg, ...)	ensureRootReady()->error((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def ROOT_CRITICAL(msg, ...)
 * @brief Logs a critical message using the root logger, including file, line, and function info.
 */
#define ROOT_CRITICAL(msg, ...)	ensureRootReady()->critical((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def ROOT_EXCEPTION(msg, ...)
 * @brief Logs an exception message using the root logger, including file, line, and function info.
 */
#define ROOT_EXCEPTION(msg, ...)ensureRootReady()->exception((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def ROOT_LOG(msg, ...)
 * @brief Logs a message at a custom level using the root logger, including file, line, and function info.
 */
#define ROOT_LOG(msg, ...)		ensureRootReady()->log((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

void	basicConfig(
	const std::string &filename = "", 
	const std::ios_base::openmode &fileMode = std::ios_base::app, 
	t_handlers handlers = t_handlers(),
	std::ostream *stream = NULL,
	const std::string &datefmt = "",
	const std::string &fmt = "",
	const logRecord::e_LogLevel level = logRecord::NOTSET,
	bool force = false
);

common::core::raii::SharedPtr<logger::Logger> getLogger(const std::string &name = "");
common::core::raii::SharedPtr<logger::Logger> ensureRootReady();

void debug(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
void info(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
void warning(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
void error(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
void exception(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
void critical(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);

void log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);

void disable(logRecord::e_LogLevel level = logRecord::CRITICAL);

void shutdown();

} // !log42

#endif // !LOG42_LOGGING_HPP

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
