// TODO: Don't forget to add 42 header !

#ifndef HANDLER_HPP
#define HANDLER_HPP

/**
 * @file Handler.hpp
 * @brief
 */ 

#include "Filterer.hpp"
#include "Formatter.hpp"
#include "LogRecord.hpp"

namespace logging
{
namespace handler
{

class Handler : public filterer::Filterer
{
	public:
		explicit Handler(const logRecord::e_LogLevel level = logRecord::NOTSET);
		virtual ~Handler();

		Handler(const Handler &rhs);
		Handler &operator=(const Handler &rhs);

		const std::string			&getName() const;
		void						setName(const std::string &name);
		logRecord::e_LogLevel		getLevel() const;
		void						setLevel(const logRecord::e_LogLevel level);
		std::string					format(logRecord::LogRecord &record) const;
		virtual void				emit(logRecord::LogRecord &record) = 0;
		bool						handle(logRecord::LogRecord &record);
		const formatter::Formatter	&getFormatter() const;
		void						setFormatter(const formatter::Formatter &fmt);
		virtual void				flush() = 0;
		virtual void				close();
		void						handlerError(const logRecord::LogRecord &record) const;	
		virtual std::string			toString() const;

	protected:
		std::string				_name;
		logRecord::e_LogLevel	_level;
		formatter::Formatter	_formatter;
		bool					_closed;
};

} // !handler
} // !logging
#endif // !HANDLER_HPP
