// TODO: Don't forget to add 42 header !

/**
 * @file Manager.cpp
 * @brief
 */ 

#include "Logger.hpp"
#include "Logging.hpp"
#include "RootLogger.hpp"
#include "Manager.hpp"
#include <stdexcept>

namespace logging
{
namespace manager
{

/**
 * @brief 
 *
 * @param root 
 * @return 
 */
Manager &Manager::getInstance(logger::Logger *root) 
{
    static Manager instance(root);

    return (instance);
}

/**
 * @brief 
 *
 * @param root 
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
 * @brief 
 */
Manager::~Manager() 
{
	shutdown();
}

/**
 * @brief 
 *
 * @return 
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
 * @brief 
 */
void	Manager::resetRoot()
{
	this->_root = NULL;
}

/**
 * @brief 
 *
 * @return 
 */
logRecord::e_LogLevel	Manager::getDisable() const
{
	return (this->_disable);
}

/**
 * @brief 
 *
 * @param value 
 */
void	Manager::setDisable(const logRecord::e_LogLevel value)
{
	this->_disable = value;
}

/**
 * @brief 
 *
 * @return 
 */
bool	Manager::getEmittedNoHandlerWarning() const
{
	return (this->_emittedNoHandlerWarning);
}

/**
 * @brief 
 *
 * @param value 
 */
void	Manager::setEmittedNoHandlerWarning(bool value)
{
	this->_emittedNoHandlerWarning = value;
}

/**
 * @brief 
 *
 * @return 
 */
std::map<std::string, Node *>	&Manager::getLoggerMap()
{
	return (this->_loggerMap);
}

/**
 * @brief 
 *
 * @param name 
 * @return 
 */
logger::Logger *Manager::getLogger(const std::string &name)
{
	if (!this->_root)
		this->getRoot();
	if (name.empty())
		throw std::invalid_argument("Logger name must be a non-empty string");

	logger::Logger *alogger = NULL;
	std::map<std::string, Node*>::iterator it;
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
 * @brief 
 */
void	Manager::clearCache()
{
	std::map<std::string, Node *>::iterator it;
	for (it = this->_loggerMap.begin(); it != this->_loggerMap.end(); ++it)
	{
		logger::Logger *alogger = dynamic_cast<logger::Logger *>(it->second);
		if (alogger)
			alogger->clearCache();
	}
	this->_root->cacheClear();
}

/**
 * @brief 
 *
 * @param alogger 
 */
void Manager::_fixupParents(logger::Logger *alogger)
{
    const std::string &name = alogger->getName();
    std::size_t pos = name.rfind('.');
    Node *foundParent = NULL;

    while (pos != std::string::npos && !foundParent) 
    {
        std::string substr = name.substr(0, pos);
        std::map<std::string, Node*>::iterator it;
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
 * @brief 
 *
 * @param ph 
 * @param alogger 
 */
void Manager::_fixupChildren(placeholder::PlaceHolder *ph, logger::Logger *alogger)
{
    const std::string &name = alogger->getName();
    std::size_t namelen = name.length();

    const std::set<Node*> &children = ph->getLoggerSet();
	std::set<Node*>::const_iterator it;
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
} // !logging
