// TODO: Don't forget to add 42 header !

/**
 * @file PercentStyle.cpp
 * @brief
 */ 

#include "PercentStyle.hpp"
#include "stringUtils.hpp"

namespace logging
{
namespace style
{

const std::string PercentStyle::defaultFormat = "%(message)";
const std::string PercentStyle::asctimeFormat = "%(asctime)";
const std::string PercentStyle::asctimeSearch = "%(asctime)";

/**
 * @brief 
 *
 * @param fmt 
 * @param defaults 
 */
PercentStyle::PercentStyle(const std::string &fmt, const std::map<std::string, std::string> defaults) 
	: _fmt(fmt), _defaults(defaults) 
{}

/**
 * @brief 
 */
PercentStyle::~PercentStyle() {}

/**
 * @brief 
 *
 * @param rhs 
 */
PercentStyle::PercentStyle(const PercentStyle &rhs) : _fmt(rhs._fmt), _defaults(rhs._defaults) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
PercentStyle &PercentStyle::operator=(const PercentStyle &rhs)
{
	if (this != &rhs)
	{
		this->_fmt = rhs._fmt;
		this->_defaults = rhs._defaults;
	}
	return (*this);
}

/**
 * @brief 
 */
std::string PercentStyle::getFmt() const
{
	return (this->_fmt);
}

/**
 * @brief 
 *
 * @return 
 */
bool PercentStyle::useTime() const
{
	return (this->_fmt.find(asctimeSearch) != std::string::npos);
}

/**
 * @brief 
 */
void PercentStyle::validate() const
{
	if (this->_fmt.find("%(message)") == std::string::npos)
		throw std::invalid_argument("Invalid format: must contain %(message)");
}

/**
 * @brief 
 *
 * @param record 
 */
std::string	PercentStyle::format(const logRecord::LogRecord &record) const
{
	return (this->_format(record));
}

/**
 * @brief 
 *
 * @param record 
 */
std::string	PercentStyle::_format(const logRecord::LogRecord &record) const
{
	std::string result = this->_fmt;
	std::map<std::string, std::string> defaults(this->_defaults);

	defaults["created"] = utils::toString(record.getCreated());
	defaults["filename"] = record.getFilename();
	defaults["funcName"] = record.getFuncName();
	defaults["levelname"] = record.getLevelName();
	defaults["levelno"] = utils::toString(record.getLevelNo());
	defaults["lineno"] = utils::toString(record.getLineNo());
	defaults["message"] = record.getMessage();
	defaults["module"] = record.getModule();
	defaults["msecs"] = utils::toString(record.getMsecs());
	defaults["name"] = record.getName();
	defaults["pathname"] = record.getPathname();
	defaults["relativeCreated"] = utils::toString(record.getRelativeCreated());
	defaults["asctime"] = record.getAsctime();

	std::map<std::string, std::string>::iterator it;
	for (it = defaults.begin(); it != defaults.end(); ++it)
	{
		std::string placeholder = "%(" + it->first + ")";
		std::size_t pos = 0;
		while ((pos = result.find(placeholder, pos)) != std::string::npos)
		{
			result.replace(pos, placeholder.length(), it->second);
			pos += it->second.length();
		}
	}
	return (result);
}

} // !style
} // !logging
