// TODO: Don't forget to add 42 header !

#ifndef MANAGER_HPP
#define MANAGER_HPP

/**
 * @file Manager.hpp
 * @brief
 */ 

#include "Logger.hpp"
#include "LogRecord.hpp"
#include "PlaceHolder.hpp"
#include <map>

namespace logging
{
namespace manager
{

class Manager
{
	public:
		static	Manager &getInstance(logger::Logger *root = NULL);

		logger::Logger	 				*getRoot();
		void							resetRoot();
		logRecord::e_LogLevel			getDisable() const;
		void							setDisable(const logRecord::e_LogLevel value);
		bool							getEmittedNoHandlerWarning() const;
		void							setEmittedNoHandlerWarning(bool value);
		std::map<std::string, Node *>	&getLoggerMap();

		logger::Logger					*getLogger(const std::string &name);

		void	clearCache();

	private:
		logger::Logger 					*_root;
		logRecord::e_LogLevel			_disable;
		bool							_emittedNoHandlerWarning;
		std::map<std::string, Node *>	_loggerMap;	

		explicit Manager(logger::Logger *root);
		~Manager();

		Manager(const Manager &rhs);
		Manager &operator=(const Manager &rhs);

		void	_fixupParents(logger::Logger *alogger);
		void	_fixupChildren(placeholder::PlaceHolder *ph, logger::Logger *alogger);
};

} // !manager
} // !logging

#endif // !MANAGER_HPP
