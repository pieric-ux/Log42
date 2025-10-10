// TODO: Don't forget to add 42 header !

#ifndef BUFFERINGFORMATTER_HPP
#define BUFFERINGFORMATTER_HPP

/**
 * @file BufferingFormatter.hpp
 * @brief
 */ 

#include "Formatter.hpp"
#include <vector>

namespace logging
{
namespace formatter
{

class BufferingFormatter
{
	public:
		explicit BufferingFormatter(const Formatter	&linefmt = Formatter());
		~BufferingFormatter();

		BufferingFormatter(const BufferingFormatter &rhs);
		BufferingFormatter &operator=(const BufferingFormatter &rhs);

		std::string	formatHeader(const std::vector<logRecord::LogRecord> &records) const;
		std::string	formatFooter(const std::vector<logRecord::LogRecord> &records) const;

		std::string format(std::vector<logRecord::LogRecord> &records) const;

	private:
		Formatter _linefmt;
};

} // !formatter
} // !logging

#endif // !BUFFERINGFORMATTER
