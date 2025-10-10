// TODO: Don't forget to add 42 header !

#ifndef FILTER_HPP
#define FILTER_HPP

/**
 * @file Filter.hpp
 * @brief
 */ 

#include "LogRecord.hpp"
#include <string>

namespace logging
{
namespace filter
{

class Filter
{
	public:
		explicit Filter(const std::string &name = "");
		~Filter();

		Filter(const Filter &rhs);
		Filter &operator=(const Filter &rhs);

		bool	operator<(const Filter &rhs) const;
		bool	operator==(const Filter &rhs) const;

		bool	filter(const logRecord::LogRecord &record) const;

	private:
		std::string	_name;
		size_t		_len;
};

} // !filter
} // !logging

#endif // !FILTER_HPP
