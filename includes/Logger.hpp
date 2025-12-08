/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
#define LOGGER_HPP

/**
 * @file Logger.hpp
 * @brief Declares the Logger class for hierarchical logging with level, 
 * handler, and propagation control.
 */ 

#include "Filterer.hpp"
#include "Handler.hpp"
#include "LogRecord.hpp"
#include "Node.hpp"
#include "types.hpp"

namespace log42
{
namespace manager
{
class Manager;
} // !manager
namespace logger
{

/**
 * @def DEBUG(logger, msg, ...)
 * @brief Logs a debug message with file, line, and function info.
 */
#define DEBUG(logger, msg, ...)			(logger)->debug((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def INFO(logger, msg, ...)
 * @brief Logs an info message with file, line, and function info.
 */
#define INFO(logger, msg, ...)			(logger)->info((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def WARNING(logger, msg, ...)
 * @brief Logs a warning message with file, line, and function info.
 */
#define WARNING(logger, msg, ...)		(logger)->warning((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def ERROR(logger, msg, ...)
 * @brief Logs an error message with file, line, and function info.
 */
#define ERROR(logger, msg, ...)			(logger)->error((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def CRITICAL(logger, msg, ...)
 * @brief Logs a critical message with file, line, and function info.
 */
#define CRITICAL(logger, msg, ...)		(logger)->critical((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def EXCEPTION(logger, msg, ...)
 * @brief Logs an exception message with file, line, and function info.
 */
#define EXCEPTION(logger, msg, ...)		(logger)->exception((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
/**
 * @def LOG(logger, level, msg, ...)
 * @brief Logs a message at the specified level with file, line, and function info.
 */
#define LOG(logger, level, msg, ...)	(logger)->log((level), (msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

/**
 * @class Logger
 * @brief Provides hierarchical logging with level, handler, filter, and propagation support.
 */
class Logger : public Node, public  filterer::Filterer
{
	public:
		explicit Logger(const std::string &name, const logRecord::e_LogLevel level = logRecord::NOTSET);
		virtual ~Logger();

		Logger(const Logger &rhs);
		Logger &operator=(const Logger &rhs);

		void setLevel(const logRecord::e_LogLevel level);
		void setPropagate(bool propagate);

		void debug(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
		void info(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
		void warning(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
		void error(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
		void exception(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);
		void critical(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);

		void log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const t_args *args = NULL);

		void handle(logRecord::LogRecord &record);
		void addHandler(const common::core::raii::SharedPtr<handler::Handler> &handler);
		void removeHandler(const common::core::raii::SharedPtr<handler::Handler> &handler);
		bool hasHandler() const;
		void callHandlers(logRecord::LogRecord &record);
		const t_handlers &getHandlers() const;

		logRecord::e_LogLevel getEffectiveLevel() const;
		bool isEnabledFor(const logRecord::e_LogLevel level);
		
		common::core::raii::SharedPtr<Logger>    getChild(const std::string &suffix) const;
		t_loggers	getChildren() const;

		virtual std::string	toString() const;
	
		void clearCache();
		void cacheClear();
		
	private:
		logRecord::e_LogLevel					_level;
		bool									_propagate;
		t_handlers								_handlers;
		bool									_disabled;
		std::map<logRecord::e_LogLevel, bool>	_cache;
		manager::Manager						&_manager;

		void _log(const logRecord::e_LogLevel level, const std::string &msg, const t_args *args,
					const std::string filename, int lineNo, const std::string funcName);
};

} // !logger
} // !log42

#endif // !LOGGER_HPP

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
