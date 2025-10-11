/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemont <pdemont@student.42lausanne.ch>    +#+  +:+       +#+        */
/*   By: blucken <blucken@student.42lausanne.ch>  +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*   Created: 2025/10/11                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileHandler.hpp"
#include "Logging.hpp"
#include "Manager.hpp"
#include "Logger.hpp"
#include "StreamHandler.hpp"
#include "Formatter.hpp"
#include <iostream>

using namespace logging;
using namespace logging::logger;
using namespace logging::logRecord;
using namespace logging::handler;
using namespace logging::formatter;
using namespace logging::manager;

static void testManualConfig();
static void testBasicConfigImplicit();
static void testLogLevels();
static void testForceReset();
static void testBasicConfigErrors();
static void testChildLogger();
static void testDisableLogs();

int main() {
	testManualConfig();
	testBasicConfigImplicit();
	testLogLevels();
	testForceReset();
	testBasicConfigErrors();
	testChildLogger();
	testDisableLogs();
	return 0;
}

static void testManualConfig()
{
	std::cout << "\n===== TEST 1: Manual configuration =====" << std::endl;
	try {
		Manager &manager = Manager::getInstance();
		Logger *logger = manager.getLogger("manual");
		logger->setLevel(DEBUG);

		StreamHandler *consoleHandler = new StreamHandler(std::cout);
		FileHandler *fileHandler = new FileHandler("manual.log");

		Formatter fmt("%(asctime) - %(name) - %(levelname) - %(message) - file: %(filename) - function: %(funcName)() at line: %(lineno)", "%Y-%m-%d %H:%M:%S");
		consoleHandler->setFormatter(fmt);
		fileHandler->setFormatter(fmt);

		logger->addHandler(consoleHandler);
		logger->addHandler(fileHandler);

		DEBUG(logger, "Debug message");
		INFO(logger, "Info message");
		WARNING(logger, "Warning message");
		ERROR(logger, "Error message");
		CRITICAL(logger, "Critical message");

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << "Test 1 failed: " << e.what() << std::endl;
	}
}

static void testBasicConfigImplicit()
{
	std::cout << "\n===== TEST 2: basicConfig implicit =====" << std::endl;
	try {
		ROOT_DEBUG("Debug root message");
		ROOT_INFO("Info root message");
		ROOT_WARNING("Warning root message");
		ROOT_ERROR("Error root message");
		ROOT_CRITICAL("Critical root message");

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << "Test 2 failed: " << e.what() << std::endl;
	}
}

static void testLogLevels()
{
	std::cout << "\n===== TEST 3: Log levels =====" << std::endl;
	try {
		Logger *logger = Manager::getInstance().getLogger("leveltest");
		logger->setLevel(INFO);

		StreamHandler *ch = new StreamHandler(std::cout);
		Formatter fmt("%(levelname): %(message)");
		ch->setFormatter(fmt);
		logger->addHandler(ch);

		DEBUG(logger, "This should NOT appear");
		INFO(logger, "This should appear");
		WARNING(logger, "This should also appear");

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << "Test 3 failed: " << e.what() << std::endl;
	}
}

static void testForceReset()
{
	std::cout << "\n===== TEST 4: basicConfig with force reset =====" << std::endl;
	try {
		basicConfig("forced.log", std::ios::out, std::set<Handler*>(), NULL, "", "%(message)", DEBUG, true);
		ROOT_INFO("This should go ONLY into forced.log");

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << "Test 4 failed: " << e.what() << std::endl;
	}
}

static void testBasicConfigErrors()
{
	std::cout << "\n===== TEST 5: basicConfig errors =====" << std::endl;
	try {
		std::set<Handler *> handlers;
		handlers.insert(new StreamHandler(std::cout));

		try 
		{
			basicConfig("file.log", std::ios::out, handlers, &std::cout, "", "%(message)", DEBUG, false);
		} 
		catch (const std::exception &e) 
		{
			std::cout << "Expected exception: " << e.what() << std::endl;

			std::set<Handler *>::iterator it;
			for (it = handlers.begin(); it != handlers.end(); ++it)
				delete *it;
		}

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << "Test 5 failed: " << e.what() << std::endl;
	}
}

static void testChildLogger()
{
	std::cout << "\n===== TEST 6: Child logger propagation =====" << std::endl;
	try {
		Logger *parent = Manager::getInstance().getLogger("parent");
		Logger *child = Manager::getInstance().getLogger("parent.child");

		StreamHandler *ch = new StreamHandler(std::cout);
		Formatter fmt("[%(name)] %(levelname): %(message)");
		ch->setFormatter(fmt);
		parent->addHandler(ch);

		parent->setLevel(DEBUG);
		child->setLevel(DEBUG);

		INFO(child, "Message from child (should propagate to parent handler)");

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << "Test 6 failed: " << e.what() << std::endl;
	}
}

static void testDisableLogs()
{
	std::cout << "\n===== TEST 7: Disable logs =====" << std::endl;
	try {
		Logger *logger = Manager::getInstance().getLogger("disabletest");
		StreamHandler *ch = new StreamHandler(std::cout);
		logger->addHandler(ch);
		logger->setPropagate(false);

		disable(ERROR);

		WARNING(logger, "This should NOT appear");
		ERROR(logger, "This should NOT appear");
		CRITICAL(logger, "This SHOULD appear");

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << "Test 7 failed: " << e.what() << std::endl;
	}
}

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
