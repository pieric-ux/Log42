// TODO: Don't forget to add 42 header !

#ifndef LOGGING_HPP
#define LOGGING_HPP

/**
 * @file Logging.hpp
 * @brief
 */ 

#include "Handler.hpp"
#include "Logger.hpp"
#include <fstream>
#include <set>
#include <string>

namespace logging
{

#define ROOT_DEBUG(msg, ...)	ensureRootReady()->debug((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ROOT_INFO(msg, ...)		ensureRootReady()->info((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ROOT_WARNING(msg, ...)	ensureRootReady()->warning((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ROOT_ERROR(msg, ...)	ensureRootReady()->error((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ROOT_CRITICAL(msg, ...)	ensureRootReady()->critical((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ROOT_EXCEPTION(msg, ...)ensureRootReady()->exception((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ROOT_LOG(msg, ...)		ensureRootReady()->log((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

void	basicConfig(
	const std::string &filename = "", 
	const std::ios_base::openmode &fileMode = std::ios_base::app, 
	std::set<handler::Handler *> handlers = std::set<handler::Handler *>(),
	std::ostream *stream = NULL,
	const std::string &datefmt = "",
	const std::string &fmt = "",
	const logRecord::e_LogLevel level = logRecord::NOTSET,
	bool force = false
);

logger::Logger *getLogger(const std::string &name = "");
logger::Logger *ensureRootReady();

void debug(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
void info(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
void warning(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
void error(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
void exception(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
void critical(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);

void log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);

void disable(logRecord::e_LogLevel level = logRecord::CRITICAL);

void shutdown();

} // !logging

#endif // !LOGGING_HPP
