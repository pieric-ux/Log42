// TODO: Don't forget to add 42 header !

/**
 * @file Logging.cpp
 * @brief
 */ 

#include "FileHandler.hpp"
#include "Logging.hpp"
#include "Manager.hpp"
#include "StreamHandler.hpp"
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>

namespace logging
{

/**
 * @brief 
 *
 * @param filename 
 * @param fileMode 
 * @param handlers 
 * @param stream 
 * @param datefmt 
 * @param fmt 
 * @param level 
 * @param force 
 */
void	basicConfig(
	const std::string &filename, 
	const std::ios_base::openmode &fileMode, 
	std::set<handler::Handler *> handlers,
	std::ostream *stream,
	const std::string &datefmt,
	const std::string &fmt,
	const logRecord::e_LogLevel level,
	bool force)
{
	logger::Logger &root = *manager::Manager::getInstance().getRoot();

	if (force)
	{
		std::set<handler::Handler *> rootHandlers = root.getHandlers();
		std::set<handler::Handler *>::iterator it;
		for (it = rootHandlers.begin(); it != rootHandlers.end(); ++it)
		{
			handler::FileHandler *fileHandler = dynamic_cast<handler::FileHandler *>(*it);
			if (fileHandler)
				fileHandler->close();
			root.removeHandler(*it);
			delete *it;
		}
		rootHandlers.clear();
	}

	if (root.getHandlers().empty())
	{
		if (!handlers.empty())
		{
			if (stream || !filename.empty())
				throw std::invalid_argument("'stream' or 'filename' sould not be specified together with 'handlers'");
		}
		else
		{
			if (stream && !filename.empty())
				throw std::invalid_argument("'stream' and 'filename' sould not be specified together");

			if (!filename.empty())
				handlers.insert(new handler::FileHandler(filename, fileMode));
			else
			{
				if (stream)
					handlers.insert(new handler::StreamHandler(*stream));
				else
					handlers.insert(new handler::StreamHandler());
			}
		}
	}

	formatter::Formatter formatter (fmt, datefmt);

	std::set<handler::Handler *>::iterator it;
	for (it = handlers.begin(); it != handlers.end(); ++it)
	{
		handler::Handler *h = *it;
		h->setFormatter(formatter);
		root.addHandler(h);
	}
	
	if (level != logRecord::NOTSET)
		root.setLevel(level);
}

/**
 * @brief 
 *
 * @param name 
 * @return 
 */
logger::Logger* getLogger(const std::string &name)
{
    manager::Manager &manager = manager::Manager::getInstance();
    if (name.empty() || name == manager.getRoot()->getName())
        return manager.getRoot();
    return manager.getLogger(name);
}

/**
 * @brief 
 *
 * @return 
 */
logger::Logger *ensureRootReady()
{
    manager::Manager &manager = manager::Manager::getInstance();
    logger::Logger *root = manager.getRoot();
    if (root->getHandlers().empty())
        basicConfig();
    return root;
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
void	debug(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
    ensureRootReady()->debug(msg, filename, lineNo, funcName, args);
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
void	info(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
    ensureRootReady()->info(msg, filename, lineNo, funcName, args);
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
void	warning(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
    ensureRootReady()->warning(msg, filename, lineNo, funcName, args);
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
void	error(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
    ensureRootReady()->error(msg, filename, lineNo, funcName, args);
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
void	exception(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
    ensureRootReady()->error(msg, filename, lineNo, funcName, args);
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
void	critical(const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
    ensureRootReady()->critical(msg, filename, lineNo, funcName, args);
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
void	log(const logRecord::e_LogLevel level, const std::string &msg, const std::string filename, int lineNo, const std::string funcName, const std::vector<std::string> *args)
{
    ensureRootReady()->log(level, msg, filename, lineNo, funcName, args);
}

/**
 * @brief 
 *
 * @param level 
 */
void disable(logRecord::e_LogLevel level)
{
    manager::Manager::getInstance().setDisable(level);
    manager::Manager::getInstance().clearCache();
}

/**
 * @brief 
 */
void shutdown()
{
	manager::Manager &manager = manager::Manager::getInstance();

	std::map<std::string, Node *> &loggers = manager.getLoggerMap();
	
	std::map<std::string, Node *>::iterator lIt;
	for (lIt = loggers.begin(); lIt != loggers.end(); ++lIt)
	{
		logger::Logger *logger = dynamic_cast<logger::Logger *>(lIt->second);
		if (logger)
		{
			std::set<handler::Handler *> handlers = logger->getHandlers();

			std::set<handler::Handler *>::iterator hIt;
			for (hIt = handlers.begin(); hIt != handlers.end(); ++hIt)
			{
				handler::Handler *handler = *hIt;
				if (handler)
				{
					try
					{
						handler->flush();
						handler->close();
					}
					catch (...) {}

					delete handler;
				}
			}
			handlers.clear();
			delete logger;
		}
	}
    loggers.clear();
	manager.resetRoot();
}

} // !logging
