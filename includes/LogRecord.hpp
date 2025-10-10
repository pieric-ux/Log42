// TODO: Don't forget to add 42 header !

#ifndef LOGRECORD_HPP
#define LOGRECORD_HPP

/**
 * @file LogRecord.hpp
 * @brief
 */ 

#include <ctime>
#include <string>
#include <vector>

namespace logging
{
namespace logRecord
{

enum e_LogLevel { NOTSET, DEBUG, INFO, WARNING, ERROR, CRITICAL };
std::string levelToString(e_LogLevel level);

class LogRecord
{
	public:
		LogRecord(const std::string &name,
					 const e_LogLevel level,
					 const std::string &pathname, 
					 const int lineno, 
					 const std::string &msg, 
					 const std::vector<std::string> *args, 
					 const std::string &func = "");
		~LogRecord();

		LogRecord(const LogRecord &rhs);
		LogRecord &operator=(const LogRecord &rhs);

		static	clock_t	&getStartTime();

		std::string	toString() const;

		std::string	getName() const;
		std::string	getMessage() const;
		e_LogLevel	getLevelNo() const;
		std::string	getLevelName() const;
		std::string	getPathname() const;
		std::string	getFilename() const;
		std::string	getModule() const;
		int			getLineNo() const;
		std::string	getFuncName() const;
		std::time_t	getCreated() const;
		long		getMsecs() const;
		double		getRelativeCreated() const;
		std::string	getAsctime() const;

		void		setAsctime(const std::string &asctime);

	private:
		static clock_t				_startTime;

		std::string					_name;
		std::string					_msg;
		std::vector<std::string>	_args;
		e_LogLevel					_levelNo;
		std::string					_levelName;
		std::string					_pathname;
		std::string					_filename;
		std::string					_module;
		int							_lineNo;
		std::string					_funcName;
		std::time_t					_created; 
		long						_msecs;
		double						_relativeCreated;
		std::string					_asctime;

};

} // !logRecord
} // !logging
#endif // !LOGRECORD_HPP
