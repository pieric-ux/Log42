// TODO: Don't forget to add 42 header !

/**
 * @file Formatter.cpp
 * @brief
 */ 

#include "Formatter.hpp"
#include "PercentStyle.hpp"
#include <cstring>
#include <iomanip>
#include <sstream>

namespace logging
{
namespace formatter
{

/**
 * @brief 
 */
const std::string Formatter::defaultPercentFormat = "%(levelname):%(name):%(message)";

/**
 * @brief 
 */
const std::string Formatter::defaultTimeFormat = "%Y-%m-%d %H:%M:%S";

/**
 * @brief 
 */
struct std::tm *(*Formatter::_converter)(const time_t *) = localtime;

/**
 * @brief 
 *
 * @param fmt 
 * @param datefmt 
 * @param validate 
 * @param defaults 
 */
Formatter::Formatter(const std::string &fmt, const std::string &datefmt, bool validate,
					 const std::map<std::string, std::string> defaults)
	: _style(fmt.empty() ? defaultPercentFormat : fmt, defaults), 
	_fmt(this->_style.getFmt()), _datefmt(datefmt)
{
	if (validate)
		this->_style.validate();
}

/**
 * @brief 
 */
Formatter::~Formatter() {}

/**
 * @brief 
 *
 * @param rhs 
 */
Formatter::Formatter(const Formatter &rhs) :_style(rhs._style), _fmt(rhs._fmt), _datefmt(rhs._datefmt) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
Formatter	&Formatter::operator=(const Formatter &rhs)
{
	if (this != &rhs)
	{
		this->_style = rhs._style;
		this->_fmt = rhs._fmt;
		this->_datefmt = rhs._datefmt;
	}
	return (*this);
}

/**
 * @brief 
 *
 * @return 
 */
bool	Formatter::useTime() const
{
	return (this->_style.useTime());
}

/**
 * @brief 
 *
 * @param record 
 * @return 
 */
std::string	Formatter::formatMessage(const logRecord::LogRecord &record) const
{
	return (this->_style.format(record));
}

/**
 * @brief 
 *
 * @param record 
 */
std::string	Formatter::format(logRecord::LogRecord &record) const
{
	record.setAsctime(Formatter::formatTime(record, this->_datefmt));
	return (formatMessage(record));
}

/**
 * @brief 
 *
 * @param record 
 */
std::string	Formatter::formatTime(const logRecord::LogRecord &record, const std::string &datefmt) const
{
	time_t	t = record.getCreated();
	struct std::tm *tm= this->_converter(&t);

	const std::string &fmt = datefmt.empty() ? defaultTimeFormat : datefmt;
	std::string buffer(100, 0);
	std::strftime(&buffer[0], buffer.size(), fmt.c_str(), tm);
	buffer.resize(std::strlen(&buffer[0]));

	long milli = record.getMsecs() % 1000;

	std::ostringstream oss;
	oss << "[" << buffer << "," << std::setfill('0') << std::setw(3) << milli << "]";

	return (oss.str());
}

} // !formatter
} // !logging
