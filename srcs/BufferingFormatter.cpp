// TODO: Don't forget to add 42 header !

/**
 * @file BufferingFormatter.cpp
 * @brief
 */ 

#include "BufferingFormatter.hpp"
#include <sstream>

namespace logging
{
namespace formatter
{

/**
 * @brief 
 *
 * @param linefmt 
 */
BufferingFormatter::BufferingFormatter(const Formatter &linefmt) : _linefmt(linefmt) {}

/**
 * @brief 
 */
BufferingFormatter::~BufferingFormatter() {}

/**
 * @brief 
 *
 * @param rhs 
 */
BufferingFormatter::BufferingFormatter(const BufferingFormatter &rhs) : _linefmt(rhs._linefmt) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
BufferingFormatter	&BufferingFormatter::operator=(const BufferingFormatter &rhs)
{
	if (this != &rhs)
		this->_linefmt = rhs._linefmt;
	return (*this);
}

/**
 * @brief 
 *
 * @param records 
 */
std::string	BufferingFormatter::formatHeader(const std::vector<logRecord::LogRecord> &records) const
{
	(void)records;
	return "";
}

/**
 * @brief 
 *
 * @param records 
 */
std::string	BufferingFormatter::formatFooter(const std::vector<logRecord::LogRecord> &records) const
{
	(void)records;
	return "";
}

/**
 * @brief 
 *
 * @param records 
 */
std::string	BufferingFormatter::format(std::vector<logRecord::LogRecord> &records) const
{
	std::ostringstream	oss;
	oss << "";
	if (!records.empty())
	{
		oss << this->formatHeader(records);
		
		std::vector<logRecord::LogRecord>::iterator it;
		for (it = records.begin(); it != records.end(); ++it)
			oss << this->_linefmt.format(*it) << "\n";
		oss << this->formatFooter(records);

	}
	return (oss.str());
}

} //!formatter
} // !logging
