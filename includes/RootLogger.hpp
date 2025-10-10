// TODO: Don't forget to add 42 header !

#ifndef ROOTLOGGER_HPP
#define ROOTLOGGER_HPP

/**
 * @file RootLogger.hpp
 * @brief
 */ 

#include "Logger.hpp"
#include "LogRecord.hpp"

namespace logging
{
namespace logger
{

class RootLogger : public Logger
{
	public:
		RootLogger(const logRecord::e_LogLevel level = logRecord::NOTSET);
		~RootLogger();

		std::string		toString() const;

	private:
		RootLogger(const RootLogger &rhs);
		RootLogger &operator=(RootLogger &rhs);
};

} // !logger
} // !logging

#endif // !ROOTLOGGER_HPP
