// TODO: Don't forget to add 42 header !

#ifndef FILTERER_HPP
#define FILTERER_HPP

/**
 * @file Filterer.hpp
 * @brief
 */ 

#include "Filter.hpp"
#include <set>

namespace logging
{
namespace filterer
{

class Filterer
{
	public:
		Filterer();
		virtual ~Filterer();

		Filterer(const Filterer &rhs);
		Filterer &operator=(const Filterer &rhs);

		void			addFilter(const filter::Filter &filter);
		void			removeFilter(const filter::Filter &filter);
		void			clearFilters();

		virtual bool	filter(const logRecord::LogRecord &record) const;

	private:
		std::set<filter::Filter>	_filters;
};

} // !filterer
} // !logging
#endif // !FILTERER_HPP
