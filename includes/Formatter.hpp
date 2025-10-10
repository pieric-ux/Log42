// TODO: Don't forget to add 42 header !

#ifndef FORMATTER_HPP
#define FORMATTER_HPP

/**
 * @file Formatter.hpp
 * @brief
 */ 

#include "PercentStyle.hpp"
#include <ctime>

namespace logging
{
namespace formatter
{

class Formatter
{
	public:
		static const std::string	defaultPercentFormat;
		static const std::string	defaultTimeFormat;

		explicit Formatter(const std::string &fmt = defaultPercentFormat, 
			const std::string &datefmt = defaultTimeFormat, 
			bool validate = true,
			const std::map<std::string, std::string> defaults = std::map<std::string, std::string>());
		~Formatter();

		Formatter(const Formatter &rhs);
		Formatter &operator=(const Formatter &rhs);

		bool		useTime() const;
		std::string	formatTime(const logRecord::LogRecord &record, const std::string &datefmt = "") const;
		std::string	formatMessage(const logRecord::LogRecord &record) const;
		std::string	format(logRecord::LogRecord &record) const;


	private:
		static struct std::tm		*(*_converter)(const time_t *);
		style::PercentStyle			_style;
		std::string					_fmt;
		std::string					_datefmt;
};

} // !formatter
} // !logging

#endif // !FORMATTER_HPP
