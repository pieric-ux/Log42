// TODO: Don't forget to add 42 header !

/**
 * @file Filterer.hpp
 * @brief
 */ 

#include "Filterer.hpp"

namespace logging
{
namespace filterer
{

/**
 * @brief 
 */
Filterer::Filterer() : _filters() {}

/**
 * @brief 
 */
Filterer::~Filterer() {}

/**
 * @brief 
 *
 * @param rhs 
 */
Filterer::Filterer(const Filterer &rhs) : _filters(rhs._filters) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
Filterer	&Filterer::operator=(const Filterer &rhs)
{
	if (this != &rhs)
		this->_filters = rhs._filters;

	return (*this);
}

/**
 * @brief 
 *
 * @param filter 
 */
void	Filterer::addFilter(const filter::Filter &filter)
{
	this->_filters.insert(filter);
}

/**
 * @brief 
 *
 * @param filter 
 */
void	Filterer::removeFilter(const filter::Filter &filter)
{
	this->_filters.erase(filter);
}

/**
 * @brief 
 */
void	Filterer::clearFilters()
{
	this->_filters.clear();
}

/**
 * @brief 
 *
 * @param record 
 * @return 
 */
bool	Filterer::filter(const logRecord::LogRecord &record) const
{
	std::set<filter::Filter>::const_iterator it;
	for (it = this->_filters.begin(); it != this->_filters.end(); ++it)
	{
		if (!it->filter(record))
			return (false);
	}
	return (true);
}

} // !filterer
} // !logging
