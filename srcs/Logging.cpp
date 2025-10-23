/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logging.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Logging.cpp
 * @brief Implements the core logging API functions for configuration and message 
 * emission.
 */ 

#include "common.hpp"
#include "FileHandler.hpp"
#include "Log42.hpp"
#include "Manager.hpp"
#include "StreamHandler.hpp"
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>

namespace log42
{

/**
 * @brief Configures the root logger with basic settings and handlers.
 *
 * Sets up the root logger with file or stream handlers, formatters, and log level.
 * If 'force' is true, existing handlers are removed and deleted.
 *
 * @param filename Name of the log file (if any).
 * @param fileMode File open mode for file handler.
 * @param handlers Set of custom handlers to use (optional).
 * @param stream Output stream for logging (optional).
 * @param datefmt Date format string for log messages.
 * @param fmt Log message format string.
 * @param level Log level to set for the root logger.
 * @param force If true, forcibly reconfigures the root logger.
 */
void	basicConfig(
	const std::string &filename, 
	const std::ios_base::openmode &fileMode, 
	t_handlers handlers,
	std::ostream *stream,
	const std::string &datefmt,
	const std::string &fmt,
	const logRecord::e_LogLevel level,
	bool force)
{
	logger::Logger &root = *manager::Manager::getInstance().getRoot();

	if (force)
	{
		t_handlers rootHandlers = root.getHandlers();
		t_handlers::iterator it;
		for (it = rootHandlers.begin(); it != rootHandlers.end(); ++it)
		{
			raii::SharedPtr<handler::FileHandler> fileHandler = raii::dynamicPointerCast<handler::FileHandler>(*it);
			if (fileHandler)
				fileHandler->close();
			root.removeHandler(*it);
		}
		rootHandlers.clear();
	}

	if (root.getHandlers().empty())
	{
		if (!handlers.empty())
		{
			if (stream || !filename.empty())
				throw std::invalid_argument("'stream' or 'filename' sould not be specified together with 'handlers'");
		}
		else
		{
			if (stream && !filename.empty())
				throw std::invalid_argument("'stream' and 'filename' sould not be specified together");

			if (!filename.empty())
				handlers.insert(raii::staticPointerCast<handler::Handler>(MAKE_SHARED(handler::FileHandler, filename, fileMode)));
			else
			{
				if (stream)
					handlers.insert(raii::staticPointerCast<handler::Handler>(MAKE_SHARED(handler::StreamHandler, *stream)));
				else
					handlers.insert(raii::staticPointerCast<handler::Handler>(MAKE_SHARED(handler::StreamHandler)));
			}
		}
	}

	formatter::Formatter formatter (fmt, datefmt);

	t_handlers::iterator it;
	for (it = handlers.begin(); it != handlers.end(); ++it)
	{
		raii::SharedPtr<handler::Handler> h = *it;
		h->setFormatter(formatter);
		root.addHandler(h);
	}
	
	if (level != logRecord::NOTSET)
		root.setLevel(level);
}

/**
 * @brief Retrieves a logger by name.
 *
 * Returns the root logger if the name is empty or matches the root logger's name.
 * Otherwise, returns or creates a logger with the given name.
 *
 * @param name The name of the logger.
 * @return Pointer to the logger.
 */
logger::Logger* getLogger(const std::string &name)
{
    manager::Manager &manager = manager::Manager::getInstance();
    if (name.empty() || name == manager.getRoot()->getName())
        return manager.getRoot();
    return manager.getLogger(name);
}

/**
 * @brief Ensures the root logger is ready for logging.
 *
 * If the root logger has no handlers, configures it with default settings.
 * @return Pointer to the root logger.
 */
logger::Logger *ensureRootReady()
{
    manager::Manager &manager = manager::Manager::getInstance();
    logger::Logger *root = manager.getRoot();
    if (root->getHandlers().empty())
        basicConfig();
    return root;
}

/**
 * @brief Emits a DEBUG level log message using the root logger.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	debug(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const t_args *args)
{
    ensureRootReady()->debug(msg, filename, lineNo, funcName, args);
}

/**
 * @brief Emits an INFO level log message using the root logger.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	info(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const t_args *args)
{
    ensureRootReady()->info(msg, filename, lineNo, funcName, args);
}

/**
 * @brief Emits a WARNING level log message using the root logger.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	warning(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const t_args *args)
{
    ensureRootReady()->warning(msg, filename, lineNo, funcName, args);
}

/**
 * @brief Emits an ERROR level log message using the root logger.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	error(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const t_args *args)
{
    ensureRootReady()->error(msg, filename, lineNo, funcName, args);
}

/**
 * @brief Emits an exception log message (ERROR level) using the root logger.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	exception(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const t_args *args)
{
    ensureRootReady()->error(msg, filename, lineNo, funcName, args);
}

/**
 * @brief Emits a CRITICAL level log message using the root logger.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	critical(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const t_args *args)
{
    ensureRootReady()->critical(msg, filename, lineNo, funcName, args);
}

/**
 * @brief Emits a log message at the specified level using the root logger.
 *
 * @param level The log level.
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const t_args *args)
{
    ensureRootReady()->log(level, msg, filename, lineNo, funcName, args);
}

/**
 * @brief Disables logging at and below the specified log level.
 *
 * @param level The log level to disable.
 */
void disable(logRecord::e_LogLevel level)
{
    manager::Manager::getInstance().setDisable(level);
    manager::Manager::getInstance().clearCache();
}

 /**
 * @brief Shuts down the logging system, closing and deleting all loggers and handlers.
 *
 * Iterates through all loggers, closes and deletes their handlers, clears the logger map,
 * and resets the root logger.
 */
void shutdown()
{
	manager::Manager &manager = manager::Manager::getInstance();

	t_loggerMap &loggers = manager.getLoggerMap();
	
	t_loggerMap::iterator lIt;
	for (lIt = loggers.begin(); lIt != loggers.end(); ++lIt)
	{
		logger::Logger *logger = dynamic_cast<logger::Logger *>(lIt->second);
		if (logger)
		{
			t_handlers handlers = logger->getHandlers();

			t_handlers::iterator hIt;
			for (hIt = handlers.begin(); hIt != handlers.end(); ++hIt)
			{
				raii::SharedPtr<handler::Handler> handler = *hIt;
				if (handler)
				{
					try
					{
						handler->flush();
						handler->close();
					}
					catch (...) {}
				}
			}
			handlers.clear();
			delete logger;
		}
		else
		{
			placeholder::PlaceHolder	*ph = dynamic_cast<placeholder::PlaceHolder *>(lIt->second);
			if (ph)
				delete ph;
		}
	}
    loggers.clear();
	manager.resetRoot();
}

} // !log42

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
