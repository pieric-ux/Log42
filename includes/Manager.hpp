/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_HPP
#define MANAGER_HPP

/**
 * @file Manager.hpp
 * @brief Declares the Manager class for managing loggers and logging configuration.
 */ 

#include "Logger.hpp"
#include "LogRecord.hpp"
#include "PlaceHolder.hpp"
#include <map>

namespace log42
{
namespace manager
{

/**
 * @class Manager
 * @brief Singleton class responsible for managing loggers, their hierarchy, 
 * and logging configuration.
 */
class Manager
{
	public:
		static	Manager &getInstance(logger::Logger *root = NULL);

		logger::Logger	 				*getRoot();
		void							resetRoot();
		logRecord::e_LogLevel			getDisable() const;
		void							setDisable(const logRecord::e_LogLevel value);
		bool							getEmittedNoHandlerWarning() const;
		void							setEmittedNoHandlerWarning(bool value);
		std::map<std::string, Node *>	&getLoggerMap();

		logger::Logger					*getLogger(const std::string &name);

		void	clearCache();

	private:
		logger::Logger 					*_root;
		logRecord::e_LogLevel			_disable;
		bool							_emittedNoHandlerWarning;
		std::map<std::string, Node *>	_loggerMap;	

		explicit Manager(logger::Logger *root);
		~Manager();

		Manager(const Manager &rhs);
		Manager &operator=(const Manager &rhs);

		void	_fixupParents(logger::Logger *alogger);
		void	_fixupChildren(placeholder::PlaceHolder *ph, logger::Logger *alogger);
};

} // !manager
} // !log42

#endif // !MANAGER_HPP

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
