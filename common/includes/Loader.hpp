// TODO: Don't forget to add 42 header !

/**
 * @file Loader.hpp
 * @brief
 */

#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>

namespace utils
{
namespace loader
{

#define DIRNAME "assets"

class Loader
{
	public:
		Loader();
		~Loader();

		typedef void (*fileParser)(std::istream &ifs, const std::string &filename);

		void	loadDirectory(const std::string &dirname, const std::string &extension, fileParser parser);

	private:
		Loader(const Loader &rhs);
		Loader &operator=(const Loader &rhs);

		void	loadFile(const std::string &filename, fileParser parser);
};

} // !loader
} // !utils

#endif // !LOADER_HPP
