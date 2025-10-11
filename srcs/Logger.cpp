/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Logger.cpp
 * @brief Implements the Logger class for hierarchical logging.
 */ 

#include "Filterer.hpp"
#include "Logger.hpp"
#include "LogRecord.hpp"
#include "Manager.hpp"
#include "Node.hpp"
#include <iostream>
#include <map>

namespace logging
{
namespace logger
{

/**
 * @brief Constructs a Logger with the given name and log level.
 *
 * @param name The name of the logger.
 * @param level The log level for this logger.
 */
Logger::Logger(const std::string &name, const logRecord::e_LogLevel level) 
	: Node(name), filterer::Filterer(), _level(level), _propagate(true),
	_handlers(), _disabled(false), _cache(), _manager(manager::Manager::getInstance()) {}

/**
 * @brief Destructor for Logger.
 */
Logger::~Logger() {}

/**
 * @brief Copy constructor for Logger.
 *
 * @param rhs The Logger to copy.
 */
Logger::Logger(const Logger &rhs)
	: Node(rhs), filterer::Filterer(), _level(rhs._level), _propagate(rhs._propagate), 
	_handlers(rhs._handlers), _disabled(rhs._disabled), _cache(rhs._cache), _manager(rhs._manager) {}

/**
 * @brief Assignment operator for Logger.
 *
 * @param rhs The Logger to assign from.
 * @return Reference to this Logger.
 */
Logger &Logger::operator=(const Logger &rhs)
{
	if (this != &rhs)
	{
		Node::operator=(rhs);
		filterer::Filterer::operator=(rhs);
		this->_level = rhs._level;
		this->_propagate = rhs._propagate;
		this->_handlers = rhs._handlers;
		this->_disabled = rhs._disabled;
		this->_cache = rhs._cache;
	}
	return (*this);
}

/**
 * @brief Sets the log level for this logger and clears the cache.
 *
 * @param level The new log level.
 */
void	Logger::setLevel(const logRecord::e_LogLevel level)
{
	this->_level = level;
	this->_manager.clearCache();
}

/**
 * @brief Sets whether this logger propagates records to parent loggers.
 *
 * @param propagate True to propagate, false otherwise.
 */
void	Logger::setPropagate(bool propagate)
{
	this->_propagate = propagate;
}

 /**
 * @brief Logs a message with DEBUG level.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	Logger::debug(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
	if (this->isEnabledFor(logRecord::DEBUG))
		this->_log(logRecord::DEBUG, msg, args, filename, lineNo, funcName);
}

/**
 * @brief Logs a message with INFO level.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	Logger::info(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::INFO))
	   this->_log(logRecord::INFO, msg, args, filename, lineNo, funcName);
}

/**
 * @brief Logs a message with WARNING level.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	Logger::warning(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::WARNING))
	   this->_log(logRecord::WARNING, msg, args, filename, lineNo, funcName);
}

/**
 * @brief Logs a message with ERROR level.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	Logger::error(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::ERROR))
	   this->_log(logRecord::ERROR, msg, args, filename, lineNo, funcName);
}

/**
 * @brief Logs an exception with ERROR level.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	Logger::exception(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::ERROR))
	   this->_log(logRecord::ERROR, msg, args, filename, lineNo, funcName);
}

/**
 * @brief Logs a message with CRITICAL level.
 *
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	Logger::critical(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::CRITICAL))
	   this->_log(logRecord::CRITICAL, msg, args, filename, lineNo, funcName);
}

/**
 * @brief Logs a message with a specified log level.
 *
 * @param level The log level.
 * @param msg The message to log.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 * @param args Optional arguments.
 */
void	Logger::log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
	if (this->isEnabledFor(level))
		this->_log(level, msg, args, filename, lineNo, funcName);
}

/**
 * @brief Handles a log record: applies filters and calls handlers.
 *
 * @param record The log record to handle.
 */
void	Logger::handle(logRecord::LogRecord &record)
{
	if (this->_disabled)
		return ;
	if (!this->filter(record))
		return ;
	this->callHandlers(record);
}

/**
 * @brief Adds a handler to this logger.
 *
 * @param handler Pointer to the handler to add.
 */
void	Logger::addHandler(handler::Handler *handler)
{
	if (!handler)
		return ;
	this->_handlers.insert(handler);
}

/**
 * @brief Removes a handler from this logger.
 *
 * @param handler Pointer to the handler to remove.
 */
void	Logger::removeHandler(handler::Handler *handler)
{
	if (!handler)
		return ;
	this->_handlers.erase(handler);
}

/**
 * @brief Checks if this logger or its ancestors have any handlers.
 *
 * @return True if any handler is present, false otherwise.
 */
bool	Logger::hasHandler() const
{
	const Logger *c = this;
	while (c)
	{
		if (!c->_handlers.empty())
			return (true);
		if (!c->_propagate)
			break ;
		else
			c = dynamic_cast<const Logger *>(c->_parent);
	}
	return false;
}

/**
 * @brief Calls all handlers for this logger and its ancestors.
 *
 * @param record The log record to process.
 */
void	Logger::callHandlers(logRecord::LogRecord &record)
{
	const Logger	*c = this;
	bool			found = false;

	while (c)
	{
		std::set<handler::Handler *>::iterator it;
		for (it = c->_handlers.begin(); it != c->_handlers.end(); ++it)
		{
			handler::Handler *hdlr = *it;		
			found = true;
			if (record.getLevelNo() >= hdlr->getLevel())
				hdlr->handle(record);
		}
		if (!c->_propagate)
			break ;
		c = dynamic_cast<const Logger *>(c->_parent);
	}

	if (!found)
	{
		if (this->_manager.getEmittedNoHandlerWarning())
		{
			std::cerr << "No handlers could be found for logger \"" << this->_name << std::endl;
			_manager.setEmittedNoHandlerWarning(true);
		}
	}
}

/**
 * @brief Gets the set of handlers attached to this logger.
 *
 * @return Reference to the set of handler pointers.
 */
const std::set<handler::Handler *>	&Logger::getHandlers() const
{
	return (this->_handlers);
}

/**
 * @brief Gets the effective log level for this logger, considering ancestors.
 *
 * @return The effective log level.
 */
logRecord::e_LogLevel	Logger::getEffectiveLevel() const
{
	const Logger	*logger = this;

	while (logger)
	{
		if (logger->_level != logRecord::NOTSET)
			return (logger->_level);
		logger = dynamic_cast<const Logger *>(logger->_parent);
	}
	return (logRecord::NOTSET);
}

/**
 * @brief Checks if this logger is enabled for the specified log level.
 *
 * @param level The log level to check.
 * @return True if enabled, false otherwise.
 */
bool	Logger::isEnabledFor(const logRecord::e_LogLevel level)
{
	if (this->_disabled)
		return (false);
	
	std::map<logRecord::e_LogLevel, bool>::const_iterator it = this->_cache.find(level);
	if (it != this->_cache.end())
		return (it->second);

	bool	is_enabled = false;
	if (this->_manager.getDisable() >= level)
		is_enabled = false;
	else
		is_enabled = (level >= this->getEffectiveLevel());

	this->_cache[level] = is_enabled;

	return (is_enabled);
}

/**
 * @brief Gets a child logger with the given suffix.
 *
 * @param suffix The suffix for the child logger's name.
 * @return Pointer to the child logger.
 */
Logger	*Logger::getChild(const std::string &suffix) const
{ 
	std::string fullname = suffix;
	if (this != this->_manager.getRoot())
		fullname = this->getName() + "." + suffix;
	return (this->_manager.getLogger(fullname));
}

/**
 * @brief Gets the set of direct child loggers.
 *
 * @return Set of pointers to child loggers.
 */
std::set<Logger *>	Logger::getChildren() const
{
	std::set<Logger *> children;

	std::map<std::string, Node *> loggerMap = this->_manager.getLoggerMap();
	std::map<std::string, Node *>::const_iterator it;

	for (it = loggerMap.begin(); it != loggerMap.end(); ++it)
	{
		Logger	*alogger = dynamic_cast<Logger *>(it->second);
		if (!alogger)
			continue ;
		if (alogger->getParent() != this)
			continue ;

		int hierLevel = 0;
		const Node *parentIter = alogger;
		while (parentIter != this->_manager.getRoot())
		{
			parentIter = parentIter->getParent();
			hierLevel++;
		}

		int selfLevel = 0;
		parentIter = this;
		while (parentIter != this->_manager.getRoot())
		{
			parentIter = parentIter->getParent();
			selfLevel++;
		}

		if (hierLevel == selfLevel + 1)
			children.insert(alogger);
	}
	return (children);
}

/**
 * @brief Returns a string representation of the logger.
 *
 * @return String representation.
 */
std::string Logger::toString() const
{
    return ("<Logger " + getName() + " (" + logRecord::levelToString(getEffectiveLevel()) + ")>");
}

/**
 * @brief Internal method to log a message at a given level.
 *
 * @param level The log level.
 * @param msg The message to log.
 * @param args Optional arguments.
 * @param filename Source file name.
 * @param lineNo Source line number.
 * @param funcName Function name.
 */
void	Logger::_log(const logRecord::e_LogLevel level, const std::string &msg, const std::vector<std::string> *args,
					const std::string filename, int lineNo, const std::string funcName)
{
	logRecord::LogRecord record(
		this->getName(),
		level,
		filename,
		lineNo,
		msg,
		args,
		funcName
	);
	this->handle(record);
}


/**
 * @brief Clears the cache for this logger and all its children.
 */
void Logger::cacheClear()
{
	this->clearCache();

	std::set<Logger *> children = this->getChildren();
	for (std::set<Logger *>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->cacheClear();
}

/**
 * @brief Clears the cache for this logger.
 */
void Logger::clearCache()
{
    _cache.clear();
}

} // !logger
} // !logging

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
