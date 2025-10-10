// TODO: Don't forget to add 42 header !

/**
 * @file PercentStyle.hpp
 * @brief
 */ 

#ifndef PERCENTSTYLE_HPP
#define PERCENTSTYLE_HPP

#include "LogRecord.hpp"
#include <map>
#include <string>

namespace logging
{
namespace style
{

class PercentStyle
{
	public:
		static const std::string	defaultFormat;
		static const std::string	asctimeFormat;
		static const std::string	asctimeSearch;

		explicit PercentStyle(const std::string &fmt = defaultFormat,
			const std::map<std::string, std::string> defaults = std::map<std::string, std::string>());
		virtual ~PercentStyle();

		PercentStyle(const PercentStyle &rhs);
		PercentStyle &operator=(const PercentStyle &rhs);

		std::string getFmt() const;

		bool				useTime() const;
		virtual void		validate() const;
		virtual std::string			format(const logRecord::LogRecord &record) const;
	
	protected:
		virtual std::string	_format(const logRecord::LogRecord &record) const;

	private:
		std::string							_fmt;
		std::map<std::string, std::string>	_defaults;
};

} // !style
} // !logging

#endif // !PERCENTSTYLE_HPP
