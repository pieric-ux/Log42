/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filterer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Filterer.cpp
 * @brief Implements the Filterer class for managing and applying log filters.
 */ 

#include "Filterer.hpp"

namespace logging
{
namespace filterer
{

/**
 * @brief Constructs a Filterer object with an empty set of filters.
 */
Filterer::Filterer() : _filters() {}

/**
 * @brief Destructor for Filterer.
 */
Filterer::~Filterer() {}

/**
 * @brief Copy constructor for Filterer.
 *
 * @param rhs The Filterer to copy.
 */
Filterer::Filterer(const Filterer &rhs) : _filters(rhs._filters) {}

/**
 * @brief Assignment operator for Filterer.
 *
 * @param rhs The Filterer to assign from.
 * @return Reference to this Filterer.
 */
Filterer	&Filterer::operator=(const Filterer &rhs)
{
	if (this != &rhs)
		this->_filters = rhs._filters;

	return (*this);
}

/**
 * @brief Adds a filter to the Filterer.
 *
 * @param filter The filter to add.
 */
void	Filterer::addFilter(const filter::Filter &filter)
{
	this->_filters.insert(filter);
}

/**
 * @brief Removes a filter from the Filterer.
 *
 * @param filter The filter to remove.
 */
void	Filterer::removeFilter(const filter::Filter &filter)
{
	this->_filters.erase(filter);
}

/**
 * @brief Clears all filters from the Filterer.
 */
void	Filterer::clearFilters()
{
	this->_filters.clear();
}

/**
 * @brief Applies all filters to a log record.
 *
 * @param record The log record to filter.
 * @return True if the record passes all filters, false otherwise.
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

/* ************************************************************************** */
/*                                                                            */
/*                                MIT License                                 */
/*                                                                            */
/*   Copyright (c) 2025 Demont Pieric, Lucken Bénédict                        */
/*                                                                            */
/*   Inspired by the Python 'logging' module by Vinay Sajip.                  */
/*   This implementation was rewritten in C++98 and contains no original      */
/*   Python source code.                                                      */
/*                                                                            */
/*   Permission is hereby granted, free of charge, to any person obtaining    */
/*   a copy of this software and associated documentation files (the          */
/*   "Software"), to deal in the Software without restriction, including      */
/*   without limitation the rights to use, copy, modify, merge, publish,      */
/*   distribute, sublicense, and/or sell copies of the Software, and to       */
/*   permit persons to whom the Software is furnished to do so, subject to    */
/*   the following conditions:                                                */
/*                                                                            */
/*   The above copyright notice and this permission notice shall be included  */
/*   in all copies or substantial portions of the Software.                   */
/*                                                                            */
/*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  */
/*   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               */
/*   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   */
/*   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     */
/*   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     */
/*   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        */
/*   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   */
/*                                                                            */
/* ************************************************************************** */
