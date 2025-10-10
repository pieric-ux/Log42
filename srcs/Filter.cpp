// TODO: Don't forget to add 42 header !

/**
 * @file Filter.hpp
 * @brief
 */ 

#include "Filter.hpp"

namespace logging
{
namespace filter
{

/**
 * @brief 
 *
 * @param name 
 */
Filter::Filter(const std::string &name) : _name(name), _len(name.length()) {}

/**
 * @brief 
 */
Filter::~Filter() {}

/**
 * @brief 
 *
 * @param rhs 
 */
Filter::Filter(const Filter &rhs) : _name(rhs._name), _len(rhs._len) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
Filter	&Filter::operator=(const Filter &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_len = rhs._len;
	}
	return (*this);
}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
bool	Filter::operator<(const Filter &rhs) const
{
	return (this->_name < rhs._name);
}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
bool	Filter::operator==(const Filter &rhs) const
{
	return (this->_name == rhs._name && this->_len == rhs._len);
}

/**
 * @brief 
 *
 * @param record 
 * @return 
 */
bool	Filter::filter(const logRecord::LogRecord &record) const
{
	if (this->_len == 0)
		return (true);
	
	const std::string name = record.getName();
	
	if (this->_name == name)
		return (true);
	if (name.compare(0, this->_len, this->_name) != 0)
		return (false);
	return (name.size() > this->_len && name[this->_len] == '.');
}

} // !filter
} // !logging
