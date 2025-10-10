// TODO: Don't forget to add 42 header !

#include "Logger.hpp"
#include "LogRecord.hpp"
#include "RootLogger.hpp"

namespace logging
{
namespace logger
{

/**
 * @brief 
 *
 * @param level 
 */
RootLogger::RootLogger(const logRecord::e_LogLevel level) 
	: Logger("root", level) {}

/**
 * @brief 
 */
RootLogger::~RootLogger() {}

/**
 * @brief 
 *
 * @return 
 */
std::string RootLogger::toString() const
{
    return ("<RootLogger " + getName() + " (" + logRecord::levelToString(getEffectiveLevel()) + ")>");
}

} // !logger
} // !logging
