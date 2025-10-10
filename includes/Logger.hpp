// TODO: Don't forget to add 42 header !

#ifndef LOGGER_HPP
#define LOGGER_HPP

/**
 * @file Logger.hpp
 * @brief
 */ 

#include "Filterer.hpp"
#include "Handler.hpp"
#include "LogRecord.hpp"
#include "Node.hpp"
#include <set>

namespace logging
{
namespace manager
{
class Manager;
} // !manager
namespace logger
{

#define DEBUG(logger, msg, ...)			(logger)->debug((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define INFO(logger, msg, ...)			(logger)->info((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define WARNING(logger, msg, ...)		(logger)->warning((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define ERROR(logger, msg, ...)			(logger)->error((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define CRITICAL(logger, msg, ...)		(logger)->critical((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define EXCEPTION(logger, msg, ...)		(logger)->exception((msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG(logger, level, msg, ...)	(logger)->log((level), (msg), __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

class Logger : public Node, public  filterer::Filterer
{
	public:
		explicit Logger(const std::string &name, const logRecord::e_LogLevel level = logRecord::NOTSET);
		virtual ~Logger();

		Logger(const Logger &rhs);
		Logger &operator=(const Logger &rhs);

		void setLevel(const logRecord::e_LogLevel level);
		void setPropagate(bool propagate);

		void debug(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
		void info(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
		void warning(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
		void error(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
		void exception(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);
		void critical(const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);

		void log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename = "", int lineNo = 0, const std::string funcName = "", const std::vector<std::string> *args = NULL);

		void handle(logRecord::LogRecord &record);
		void addHandler(handler::Handler *handler);
		void removeHandler(handler::Handler *handler);
		bool hasHandler() const;
		void callHandlers(logRecord::LogRecord &record);
		const std::set<handler::Handler *> &getHandlers() const;

		logRecord::e_LogLevel getEffectiveLevel() const;
		bool isEnabledFor(const logRecord::e_LogLevel level);
		
		Logger *getChild(const std::string &suffix) const;
		std::set<Logger *> getChildren() const;

		virtual std::string	toString() const;
	
		void clearCache();
		void cacheClear();
		
	private:
		logRecord::e_LogLevel					_level;
		bool									_propagate;
		std::set<handler::Handler *>			_handlers;
		bool									_disabled;
		std::map<logRecord::e_LogLevel, bool>	_cache;
		manager::Manager						&_manager;

		void _log(const logRecord::e_LogLevel level, const std::string &msg, const std::vector<std::string> *args,
					const std::string filename, int lineNo, const std::string funcName);
};

} // !logger
} // !logging

#endif // !LOGGER_HPP
