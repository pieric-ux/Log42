/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Manager.cpp
 * @brief Implements the Manager class for managing loggers and their hierarchy.
 */ 

#include "Logger.hpp"
#include "Log42.hpp"
#include "RootLogger.hpp"
#include "Manager.hpp"
#include <stdexcept>

namespace log42
{
namespace manager
{

/**
 * @brief Retrieves the singleton instance of Manager.
 *
 * @param root Optional root logger pointer.
 * @return Reference to the Manager instance.
 */
Manager &Manager::getInstance(logger::Logger *root) 
{
    static Manager instance(root);

    return (instance);
}

/**
 * @brief Constructs a Manager with an optional root logger.
 *
 * @param root Pointer to the root logger.
 */
Manager::Manager(logger::Logger *root) 
	: _root(root),
	_disable(logRecord::NOTSET),
	_emittedNoHandlerWarning(false), 
	_loggerMap() 
{
	if (this->_root)
		this->_loggerMap[this->_root->getName()] = this->_root;
}

/**
 * @brief Destructor for Manager. Calls shutdown on destruction.
 */
Manager::~Manager() 
{
	shutdown();
}

/**
 * @brief Gets the root logger, creating it if necessary.
 *
 * @return Pointer to the root logger.
 */
logger::Logger	*Manager::getRoot()
{
	if (!this->_root)
	{
		this->_root = new logger::RootLogger();
		this->_loggerMap[this->_root->getName()] = this->_root;
	}
	return (this->_root);
}

/**
 * @brief Resets the root logger to NULL.
 */
void	Manager::resetRoot()
{
	this->_root = NULL;
}

/**
 * @brief Gets the current disabled log level.
 *
 * @return The disabled log level.
 */
logRecord::e_LogLevel	Manager::getDisable() const
{
	return (this->_disable);
}

/**
 * @brief Sets the disabled log level.
 *
 * @param value The log level to disable.
 */
void	Manager::setDisable(const logRecord::e_LogLevel value)
{
	this->_disable = value;
}

/**
 * @brief Checks if a "no handler" warning has been emitted.
 *
 * @return True if warning has been emitted, false otherwise.
 */
bool	Manager::getEmittedNoHandlerWarning() const
{
	return (this->_emittedNoHandlerWarning);
}

/**
 * @brief Sets the "no handler" warning emitted flag.
 *
 * @param value True if warning has been emitted, false otherwise.
 */
void	Manager::setEmittedNoHandlerWarning(bool value)
{
	this->_emittedNoHandlerWarning = value;
}

/**
 * @brief Gets the map of logger names to their nodes.
 *
 * @return Reference to the logger map.
 */
std::map<std::string, Node *>	&Manager::getLoggerMap()
{
	return (this->_loggerMap);
}

/**
 * @brief Retrieves a logger by name, creating it if necessary.
 *
 * @param name The name of the logger.
 * @return Pointer to the logger.
 * @throws std::invalid_argument if the logger name is empty.
 */
logger::Logger *Manager::getLogger(const std::string &name)
{
	if (!this->_root)
		this->getRoot();
	if (name.empty())
		throw std::invalid_argument("Logger name must be a non-empty string");

	logger::Logger *alogger = NULL;
	t_loggerMap::iterator it;
	it = this->_loggerMap.find(name);

	if (it != this->_loggerMap.end())
	{
		placeholder::PlaceHolder *ph = dynamic_cast<placeholder::PlaceHolder*>(it->second);
		if (ph)
		{
			alogger = new logger::Logger(name);
			this->_loggerMap[name] = alogger;
			_fixupChildren(ph, alogger);
			_fixupParents(alogger);
			delete ph;
		} 
		else
			alogger = dynamic_cast<logger::Logger*>(it->second);
	}
	else
	{
		alogger = new logger::Logger(name);
		this->_loggerMap[name] = alogger;
		_fixupParents(alogger);
	}

	return (alogger);
}

/**
 * @brief Clears the cache for all loggers and the root logger.
 */
void	Manager::clearCache()
{
	t_loggerMap::iterator it;
	for (it = this->_loggerMap.begin(); it != this->_loggerMap.end(); ++it)
	{
		logger::Logger *alogger = dynamic_cast<logger::Logger *>(it->second);
		if (alogger)
			alogger->clearCache();
	}
	this->_root->cacheClear();
}

/**
 * @brief Fixes parent relationships for a logger, updating the logger hierarchy.
 *
 * @param alogger Pointer to the logger.
 */
void Manager::_fixupParents(logger::Logger *alogger)
{
    const std::string &name = alogger->getName();
    std::size_t pos = name.rfind('.');
    Node *foundParent = NULL;

    while (pos != std::string::npos && !foundParent) 
    {
        std::string substr = name.substr(0, pos);
        t_loggerMap::iterator it;
        it = this->_loggerMap.find(substr);

        if (it == this->_loggerMap.end()) 
            this->_loggerMap[substr] = new placeholder::PlaceHolder(alogger);
        else 
        {
            logger::Logger *parentLogger = dynamic_cast<logger::Logger*>(it->second);
            if (parentLogger) 
                foundParent = parentLogger;
            else 
            {
                placeholder::PlaceHolder *ph = dynamic_cast<placeholder::PlaceHolder*>(it->second);
                if (ph) 
                    ph->append(alogger);
            }
        }
        pos = name.rfind('.', pos - 1);
    }

    if (!foundParent) 
        foundParent = _root;
    alogger->setParent(foundParent);
}

/**
 * @brief Fixes child relationships for a placeholder and logger.
 *
 * @param ph Pointer to the placeholder.
 * @param alogger Pointer to the logger.
 */
void Manager::_fixupChildren(placeholder::PlaceHolder *ph, logger::Logger *alogger)
{
    const std::string &name = alogger->getName();
    std::size_t namelen = name.length();

    const t_nodes &children = ph->getLoggerSet();
	t_nodes::const_iterator it;
    for (it = children.begin(); it != children.end(); ++it) 
	{
        Node *c = *it;
        Node *cparent = c->getParent();
        if (cparent && cparent->getName().compare(0, namelen, name) != 0) 
		{
			alogger->setParent(cparent);
			c->setParent(alogger);
		}
    }
}

} // !manager
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
