// TODO: Don't forget to add 42 header !

/**
 * @file Loader.cpp
 * @brief
 */

#include "dirUtils.hpp"
#include "fileUtils.hpp"
#include "Loader.hpp"
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <iostream>

namespace utils
{
namespace loader 
{

/**
 * @brief 
 */
Loader::Loader() {}

/**
 * @brief 
 */
Loader::~Loader() {}

/**
 * @brief 
 *
 * @param dirname 
 */
void	Loader::loadDirectory(const std::string &dirname, const std::string &extension, fileParser parser)
{
	utils::Directory dir(dirname);

	for (utils::DirectoryIterator it = dir.begin(); it != dir.end(); ++it)
	{
		struct dirent *entry = *it;
		if (entry->d_type == DT_REG && utils::hasExtension(entry->d_name, extension))
		{
			std::string filename = dirname + "/" + entry->d_name;
			try
			{
				this->loadFile(filename, parser);
			}
			catch (std::ios_base::failure &e)
			{
				throw std::runtime_error("Unable to open file " + filename + ": " + strerror(errno));
			}
		}
	}
}

/**
 * @brief 
 *
 * @param string 
 */
void	Loader::loadFile(const std::string &filename, fileParser parser)
{
	std::ifstream	ifs;

	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	ifs.open(filename.c_str());

	parser(ifs, filename);
}

} // !loader
} // !utils
