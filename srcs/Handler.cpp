// TODO: Don't forget to add 42 header !

/**
 * @file Handler.cpp
 * @brief
 */ 

#include "Filterer.hpp"
#include "Handler.hpp"
#include "LogRecord.hpp"
#include <iostream>

namespace logging
{
namespace handler 
{

/**
 * @brief 
 *
 * @param level 
 */
Handler::Handler(const logRecord::e_LogLevel level) 
	: filterer::Filterer(), 
	_name(""), 
	_level(level), 
	_formatter(), 
	_closed(false) 
{}

/**
 * @brief 
 */
Handler::~Handler() {};

/**
 * @brief 
 *
 * @param rhs 
 */
Handler::Handler(const Handler &rhs) : filterer::Filterer(rhs), _name(rhs._name), _level(rhs._level), _formatter(rhs._formatter), _closed(rhs._closed) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
Handler	&Handler::operator=(const Handler &rhs)
{
	if (this != &rhs)
	{
		filterer::Filterer::operator=(rhs);
		this->_name = rhs._name;
		this->_level = rhs._level;
		this->_formatter = rhs._formatter;
		this->_closed = rhs._closed;
	}
	return (*this);
}

/**
 * @brief 
 *
 * @return 
 */
const std::string	&Handler::getName() const
{
	return (this->_name);
}

/**
 * @brief 
 *
 * @param name 
 */
void	Handler::setName(const std::string &name)
{
	this->_name = name;
}

/**
 * @brief 
 *
 * @return 
 */
logRecord::e_LogLevel	Handler::getLevel() const
{
	return (this->_level);
}

/**
 * @brief 
 *
 * @param level 
 */
void	Handler::setLevel(const logRecord::e_LogLevel level)
{
	this->_level = level;
}

/**
 * @brief 
 *
 * @param record 
 */
std::string	Handler::format(logRecord::LogRecord &record) const
{
	return (this->_formatter.format(record));
}

/**
 * @brief 
 *
 * @param record 
 * @return 
 */
bool	Handler::handle(logRecord::LogRecord &record)
{
	if (this->_closed)
		return (false);
	if (!this->filter(record))
		return (false);
	if (record.getLevelNo() < this->_level)
		return (false);
	try
	{
		this->emit(record);
	}
	catch (...)
	{
		this->handlerError(record);
		return (false);
	}
	return (true);
}

/**
 * @brief 
 *
 * @return 
 */
const formatter::Formatter	&Handler::getFormatter() const
{
	return (this->_formatter);
}

/**
 * @brief 
 *
 * @param fmt 
 */
void	Handler::setFormatter(const formatter::Formatter &fmt)
{
	this->_formatter = fmt;
}

/**
 * @brief 
 */
void	Handler::close()
{
	this->_closed = true;
}

/**
 * @brief 
 *
 * @param record 
 */
void	Handler::handlerError(const logRecord::LogRecord &record) const
{
	std::cerr << "--- Logging error ---\n";
	std::cerr << "Logged from file " << record.getFilename() << ", at line " << record.getLineNo() << "\n";
	std::cerr << "Function: " << record.getFuncName() << "\n";
	std::cerr << "Logger: " << record.getName() << "\n";
	std::cerr << "Level: " << record.getLevelName() << "\n";
	std::cerr << "Message: " << record.getMessage() << std::endl;
}

/**
 * @brief 
 */
std::string	Handler::toString() const
{
	return ("<Handler (" + logRecord::levelToString(this->_level) + ")>");
}

} // !handler
} // !logging
