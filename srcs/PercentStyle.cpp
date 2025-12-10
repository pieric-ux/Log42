/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PercentStyle.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file PercentStyle.cpp
 * @brief Implements the PercentStyle class for percent-style log formatting.
 */ 

#include <common/common.hpp>
#include <log42/PercentStyle.hpp>
#include <iomanip>

using namespace common::core;

namespace log42
{
namespace style
{

/**
 * @brief Default format string for percent-style formatting.
 */
const std::string PercentStyle::defaultFormat = "%(message)";
/**
 * @brief Format string for asctime field.
 */
const std::string PercentStyle::asctimeFormat = "%(asctime)";
/**
 * @brief Search string for asctime field.
 */
const std::string PercentStyle::asctimeSearch = "%(asctime)";

/**
 * @brief Constructs a PercentStyle object.
 *
 * @param fmt The format string to use.
 * @param defaults Default values for format fields.
 */
PercentStyle::PercentStyle(const std::string &fmt, const t_defaults defaults) 
	: _fmt(fmt), _defaults(defaults) 
{}

/**
 * @brief Destructor for PercentStyle.
 */
PercentStyle::~PercentStyle() {}

/**
 * @brief Copy constructor for PercentStyle.
 *
 * @param rhs The PercentStyle to copy.
 */
PercentStyle::PercentStyle(const PercentStyle &rhs) : _fmt(rhs._fmt), _defaults(rhs._defaults) {}

/**
 * @brief Assignment operator for PercentStyle.
 *
 * @param rhs The PercentStyle to assign from.
 * @return Reference to this PercentStyle.
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
 * @brief Gets the format string.
 *
 * @return The format string.
 */
std::string PercentStyle::getFmt() const
{
	return (this->_fmt);
}

/**
 * @brief Checks if time formatting is used in the format string.
 *
 * @return True if asctime is used, false otherwise.
 */
bool PercentStyle::useTime() const
{
	return (this->_fmt.find(asctimeSearch) != std::string::npos);
}

/**
 * @brief Validates the format string to ensure it contains %(message).
 *
 * @throws std::invalid_argument if %(message) is missing.
 */
void PercentStyle::validate() const
{
	if (this->_fmt.find("%(message)") == std::string::npos)
		throw std::invalid_argument("Invalid format: must contain %(message)");
}

/**
 * @brief Formats a log record according to the format string.
 *
 * @param record The log record to format.
 * @return The formatted log message.
 */
std::string	PercentStyle::format(const logRecord::LogRecord &record) const
{
	return (this->_format(record));
}

/**
 * @brief Internal formatting implementation for percent-style formatting.
 *
 * @param record The log record to format.
 * @return The formatted log message.
 */
std::string	PercentStyle::_format(const logRecord::LogRecord &record) const
{
	std::string result = this->_fmt;
	t_defaults defaults(this->_defaults);

	defaults["created"] = utils::toString(record.getCreated());
	defaults["filename"] = record.getFilename();
	defaults["funcName"] = record.getFuncName();
	defaults["levelname"] = record.getLevelName();
	defaults["levelno"] = utils::toString(record.getLevelNo());
	defaults["lineno"] = utils::toString(record.getLineNo());
	defaults["message"] = record.getMessage();
	defaults["module"] = record.getModule();
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(3) << utils::toString(record.getMsecs());
	defaults["msecs"] = oss.str();
	defaults["name"] = record.getName();
	defaults["pathname"] = record.getPathname();
	defaults["relativeCreated"] = utils::toString(record.getRelativeCreated());
	defaults["asctime"] = record.getAsctime();

	t_defaults::iterator it;
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
} // !log42

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
