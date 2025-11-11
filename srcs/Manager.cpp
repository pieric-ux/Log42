/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+#+#+#+#+#        */
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
	: _root(),
	_disable(logRecord::NOTSET),
	_emittedNoHandlerWarning(false), 
	_loggerMap() 
{
	if (root)
	{
		this->_root = raii::SharedPtr<logger::Logger>(root);
		this->_loggerMap[this->_root->getName()] = raii::staticPointerCast<Node>(this->_root);
	}
}

/**
 * @brief Destructor for Manager. Calls shutdown on destruction.
 */
Manager::~Manager() 
{
}

/**
 * @brief Gets the root logger, creating it if necessary.
 *
 * @return Pointer to the root logger.
 */
raii::SharedPtr<logger::Logger> Manager::getRoot()
{
	if (!this->_root)
	{
		this->_root = raii::SharedPtr<logger::Logger>(new logger::RootLogger());
		this->_loggerMap[this->_root->getName()] = raii::staticPointerCast<Node>(this->_root);
	}
	return (this->_root);
}

/**
 * @brief Resets the root logger to NULL.
 */
void	Manager::resetRoot()
{
	this->_loggerMap.clear();
	this->_root = raii::SharedPtr<logger::Logger>();
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
t_loggerMap	&Manager::getLoggerMap()
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
raii::SharedPtr<logger::Logger> Manager::getLogger(const std::string &name)
{
	if (!this->_root)
		this->getRoot();
	if (name.empty())
		throw std::invalid_argument("Logger name must be a non-empty string");
	raii::SharedPtr<logger::Logger> alogger;
	t_loggerMap::iterator it;
	it = this->_loggerMap.find(name);

	if (it != this->_loggerMap.end())
	{
		raii::SharedPtr<placeholder::PlaceHolder> ph = raii::dynamicPointerCast<placeholder::PlaceHolder>(it->second);
		if (ph)
		{
			raii::SharedPtr<logger::Logger> alogger_sp(new logger::Logger(name));
			this->_loggerMap[name] = raii::staticPointerCast<Node>(alogger_sp);
			_fixupChildren(ph, alogger_sp);
			_fixupParents(alogger_sp);
			alogger = alogger_sp;
		}
		else
		{
			raii::SharedPtr<logger::Logger> alogger_sp = raii::dynamicPointerCast<logger::Logger>(it->second);
			if (alogger_sp)
				alogger = alogger_sp;
			else
				alogger = raii::SharedPtr<logger::Logger>();
		}
	}
	else
	{
		raii::SharedPtr<logger::Logger> alogger_sp(new logger::Logger(name));
		this->_loggerMap[name] = raii::staticPointerCast<Node>(alogger_sp);
		_fixupParents(alogger_sp);
		alogger = alogger_sp;
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
		raii::SharedPtr<logger::Logger> alogger_sp = raii::dynamicPointerCast<logger::Logger>(it->second);
		if (alogger_sp)
			alogger_sp->clearCache();
	}
	if (this->_root)
		this->_root->cacheClear();
}

/**
 * @brief Fixes parent relationships for a logger, updating the logger hierarchy.
 *
 * @param alogger Pointer to the logger.
 */
void Manager::_fixupParents(const raii::SharedPtr<logger::Logger> &alogger)
{
	const std::string &name = alogger->getName();
	std::size_t pos = name.rfind('.');
	raii::SharedPtr<Node> foundParentSp;

	while (pos != std::string::npos && !foundParentSp) 
	{
		std::string substr = name.substr(0, pos);
		t_loggerMap::iterator it;
		it = this->_loggerMap.find(substr);

		if (it == this->_loggerMap.end()) 
			this->_loggerMap[substr] = raii::SharedPtr<Node>(new placeholder::PlaceHolder(this->_loggerMap[name]));
		else 
		{
			raii::SharedPtr<logger::Logger> parentLoggerSp = raii::dynamicPointerCast<logger::Logger>(it->second);
			if (parentLoggerSp)
				foundParentSp = it->second;
			else
			{
				raii::SharedPtr<placeholder::PlaceHolder> ph = raii::dynamicPointerCast<placeholder::PlaceHolder>(it->second);
				if (ph)
					ph->append(this->_loggerMap[name]);
			}
		}
		pos = name.rfind('.', pos - 1);
	}

	if (!foundParentSp)
		foundParentSp = raii::staticPointerCast<Node>(this->_root);
	alogger->setParent(foundParentSp);
}

/**
 * @brief Fixes child relationships for a placeholder and logger.
 *
 * @param ph Pointer to the placeholder.
 * @param alogger Pointer to the logger.
 */
void Manager::_fixupChildren(const raii::SharedPtr<placeholder::PlaceHolder> &ph, const raii::SharedPtr<logger::Logger> &alogger)
{
	const std::string &name = alogger->getName();
	std::size_t namelen = name.length();

	const t_nodes &children = ph->getLoggerSet();
	t_nodes::const_iterator it;
	for (it = children.begin(); it != children.end(); ++it)
	{
		raii::SharedPtr<Node> csp = *it;
		Node *cparent = csp->getParent().get();
		if (cparent && cparent->getName().compare(0, namelen, name) != 0)
		{
			raii::SharedPtr<Node> cparentSp = this->_loggerMap[cparent->getName()];
			raii::SharedPtr<Node> aloggerSp = this->_loggerMap[alogger->getName()];
			alogger->setParent(cparentSp);
			csp->setParent(aloggerSp);
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
