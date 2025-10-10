// TODO: Don't forget to add 42 header !

/**
 * @file Logger.cpp
 * @brief
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
 * @brief 
 *
 * @param name 
 * @param level 
 */
Logger::Logger(const std::string &name, const logRecord::e_LogLevel level) 
	: Node(name), filterer::Filterer(), _level(level), _propagate(true),
	_handlers(), _disabled(false), _cache(), _manager(manager::Manager::getInstance()) {}

/**
 * @brief 
 */
Logger::~Logger() {}

/**
 * @brief 
 *
 * @param rhs 
 */
Logger::Logger(const Logger &rhs)
	: Node(rhs), filterer::Filterer(), _level(rhs._level), _propagate(rhs._propagate), 
	_handlers(rhs._handlers), _disabled(rhs._disabled), _cache(rhs._cache), _manager(rhs._manager) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
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
 * @brief 
 *
 * @param level 
 */
void	Logger::setLevel(const logRecord::e_LogLevel level)
{
	this->_level = level;
	this->_manager.clearCache();
}

/**
 * @brief 
 *
 * @param propagate 
 */
void	Logger::setPropagate(bool propagate)
{
	this->_propagate = propagate;
}

/**
 * @brief 
 *
 * @param msg 
 * @param filename 
 * @param lineNo 
 * @param funcName 
 * @param args 
 */
void	Logger::debug(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
	if (this->isEnabledFor(logRecord::DEBUG))
		this->_log(logRecord::DEBUG, msg, args, filename, lineNo, funcName);
}

/**
 * @brief 
 *
 * @param msg 
 * @param filename 
 * @param lineNo 
 * @param funcName 
 * @param args 
 */
void	Logger::info(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::INFO))
	   this->_log(logRecord::INFO, msg, args, filename, lineNo, funcName);
}

/**
 * @brief 
 *
 * @param msg 
 * @param filename 
 * @param lineNo 
 * @param funcName 
 * @param args 
 */
void	Logger::warning(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::WARNING))
	   this->_log(logRecord::WARNING, msg, args, filename, lineNo, funcName);
}

/**
 * @brief 
 *
 * @param msg 
 * @param filename 
 * @param lineNo 
 * @param funcName 
 * @param args 
 */
void	Logger::error(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::ERROR))
	   this->_log(logRecord::ERROR, msg, args, filename, lineNo, funcName);
}

/**
 * @brief 
 *
 * @param msg 
 * @param filename 
 * @param lineNo 
 * @param funcName 
 * @param args 
 */
void	Logger::exception(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::ERROR))
	   this->_log(logRecord::ERROR, msg, args, filename, lineNo, funcName);
}

/**
 * @brief 
 *
 * @param msg 
 * @param filename 
 * @param lineNo 
 * @param funcName 
 * @param args 
 */
void	Logger::critical(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
   if (this->isEnabledFor(logRecord::CRITICAL))
	   this->_log(logRecord::CRITICAL, msg, args, filename, lineNo, funcName);
}

/**
 * @brief 
 *
 * @param level 
 * @param msg 
 * @param filename 
 * @param lineNo 
 * @param funcName 
 * @param args 
 */
void	Logger::log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
	if (this->isEnabledFor(level))
		this->_log(level, msg, args, filename, lineNo, funcName);
}

/**
 * @brief 
 *
 * @param record 
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
 * @brief 
 *
 * @param handler 
 */
void	Logger::addHandler(handler::Handler *handler)
{
	if (!handler)
		return ;
	this->_handlers.insert(handler);
}

/**
 * @brief 
 *
 * @param handler 
 */
void	Logger::removeHandler(handler::Handler *handler)
{
	if (!handler)
		return ;
	this->_handlers.erase(handler);
}

/**
 * @brief 
 *
 * @return 
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
 * @brief 
 *
 * @param record 
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
 * @brief 
 *
 * @return 
 */
const std::set<handler::Handler *>	&Logger::getHandlers() const
{
	return (this->_handlers);
}

/**
 * @brief 
 *
 * @return 
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
 * @brief 
 *
 * @param level 
 * @return 
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
 * @brief 
 *
 * @param suffix 
 * @return 
 */
Logger	*Logger::getChild(const std::string &suffix) const
{ 
	std::string fullname = suffix;
	if (this != this->_manager.getRoot())
		fullname = this->getName() + "." + suffix;
	return (this->_manager.getLogger(fullname));
}

/**
 * @brief 
 *
 * @return 
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
 * @brief 
 *
 * @return 
 */
std::string Logger::toString() const
{
    return ("<Logger " + getName() + " (" + logRecord::levelToString(getEffectiveLevel()) + ")>");
}

/**
 * @brief 
 *
 * @param level 
 * @param msg 
 * @param args 
 * @param filename 
 * @param lineNo 
 * @param funcName 
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
 * @brief 
 */
void Logger::cacheClear()
{
	this->clearCache();

	std::set<Logger *> children = this->getChildren();
	for (std::set<Logger *>::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->cacheClear();
}

/**
 * @brief 
 */
void Logger::clearCache()
{
    _cache.clear();
}

} // !logger
} // !logging
