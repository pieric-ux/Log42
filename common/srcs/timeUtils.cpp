/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file timeUtils.cpp
 * @brief Implementation of utility functions for time and date operations.
 */ 

#include "sys/time.h"
#include <ctime>
#include <cstring>

namespace utils
{

/**
 * @brief Returns the current time as seconds since the epoch.
 *
 * @return Current time in seconds.
 */
std::time_t	nowSec()
{
	return (std::time(NULL));
}

/**
 * @brief Returns the current time as milliseconds since the epoch.
 *
 * @return Current time in milliseconds.
 */
long	nowMilli()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000);
}

/**
 * @brief Calculates the elapsed time in seconds since a given start time.
 *
 * @param startTime The starting clock tick.
 * @return Elapsed time in seconds as a double.
 */
double	relativeSec(const clock_t &startTime)
{
	return ((static_cast<double>(std::clock()) - startTime) / CLOCKS_PER_SEC);
}

} // !utils

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
