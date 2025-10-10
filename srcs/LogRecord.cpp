// TODO: Don't forget to add 42 header !

/**
 * @file LogRecord.cpp
 * @brief
 */ 

#include "fileUtils.hpp"
#include "timeUtils.hpp"
#include "LogRecord.hpp"
#include <ctime>
#include <string>
#include <sstream>

namespace logging
{
namespace logRecord 
{

/**
 * @brief 
 *
 * @param level 
 */
std::string	levelToString(e_LogLevel level)
{
	switch (level)
	{
		case DEBUG: return ("DEBUG");
		case INFO: return ("INFO");
		case WARNING: return ("WARNING");
		case ERROR: return ("ERROR");
		case CRITICAL: return ("CRITICAL");
		default: return ("UNKNOWN");
	}
}

/**
 * @brief 
 */
clock_t	LogRecord::_startTime = std::clock();

/**
 * @class timeval
 * @brief 
 *
 */
clock_t	&LogRecord::getStartTime()
{
	return (_startTime);
}

/**
 * @brief 
 *
 * @param name 
 * @param level 
 * @param pathname 
 * @param lineno 
 * @param msg 
 * @param args 
 * @param func 
 */
LogRecord::LogRecord(const std::string &name,
					 const e_LogLevel level,
					 const std::string &pathname, 
					 const int lineNo, 
					 const std::string &msg, 
					 const std::vector<std::string> *args, 
					 const std::string &func)
					 : _name(name), 
					 _msg(msg),
					 _args(args ? *args : std::vector<std::string>()),
					 _levelNo(level),
					 _levelName(levelToString(level)),
					 _pathname(pathname),
					 _filename(utils::filenameNoPath(pathname)),
					 _module(utils::filenameNoExt(this->_filename, ".cpp")),
					 _lineNo(lineNo),
					 _funcName(func),
					 _created(utils::nowSec()),
					 _msecs(utils::nowMilli()),
					 _relativeCreated(utils::relativeSec(this->_startTime)),
					 _asctime("") {}

/**
 * @brief 
 */
LogRecord::~LogRecord() {}

/**
 * @brief 
 *
 * @param rhs 
 */
LogRecord::LogRecord(const LogRecord &rhs) 
	: _name(rhs._name), _msg(rhs._msg), _args(rhs._args), _levelNo(rhs._levelNo), 
	_levelName(rhs._levelName), _pathname(rhs._pathname), _filename(rhs._filename),
	_module(rhs._module), _lineNo(rhs._lineNo), _funcName(rhs._funcName),
	_created(rhs._created), _msecs(rhs._msecs), _relativeCreated(rhs._relativeCreated), 
	_asctime(rhs._asctime) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
LogRecord	&LogRecord::operator=(const LogRecord &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_msg = rhs._msg;
		this->_args = rhs._args;
		this->_levelNo = rhs._levelNo;
		this->_levelName = rhs._levelName;
		this->_pathname = rhs._pathname;
		this->_filename = rhs._filename;
		this->_module = rhs._module;
		this->_lineNo = rhs._lineNo;
		this->_funcName = rhs._funcName;
		this->_created = rhs._created;
		this->_msecs = rhs._msecs;
		this->_relativeCreated = rhs._relativeCreated;
		this->_asctime = rhs._asctime;
	}
	return (*this);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::toString() const
{
	std::ostringstream oss;

	oss << "<LogRecord: "
		<< this->_name << ", "
		<< this->_levelNo << ", "
		<< this->_pathname << ", "
		<< this->_lineNo << ", \""
		<< this->_msg << "\">";
	return (oss.str());
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getName() const
{
	return (this->_name);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getMessage() const
{
	if (this->_args.empty())
		return (this->_msg);

	std::string result = this->_msg;

	std::size_t pos = 0;
	std::vector<std::string>::const_iterator it;
	for (it = this->_args.begin(); it != this->_args.end() && (pos = result.find("%s", pos)) != std::string::npos; ++it)
	{
		result.replace(pos, 2, *it);
		pos += it->size();
	}
	return (result);
}

/**
 * @brief 
 *
 * @return 
 */
e_LogLevel	LogRecord::getLevelNo() const
{
	return (this->_levelNo);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getLevelName() const
{
	return (this->_levelName);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getPathname() const
{
	return (this->_pathname);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getFilename() const
{
	return (this->_filename);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getModule() const
{
	return (this->_module);
}

/**
 * @brief 
 *
 * @return 
 */
int	LogRecord::getLineNo() const
{
	return (this->_lineNo);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getFuncName() const
{
	return (this->_funcName);
}

/**
 * @brief 
 *
 * @return 
 */
std::time_t	LogRecord::getCreated() const
{
	return (this->_created);
}

/**
 * @brief 
 *
 * @return 
 */
long	LogRecord::getMsecs() const
{
	return (this->_msecs);
}

/**
 * @brief 
 *
 * @return 
 */
double	LogRecord::getRelativeCreated() const
{
	return (this->_relativeCreated);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	LogRecord::getAsctime() const
{
	return (this->_asctime);
}

/**
 * @brief 
 *
 * @param asctime 
 */
void	LogRecord::setAsctime(const std::string &asctime)
{
	this->_asctime = asctime;
}

} //!logRecord
} //!logging
