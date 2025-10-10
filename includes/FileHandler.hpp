// TODO: Don't forget to add 42 header !

#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

/**
 * @file FileHandler.hpp
 * @brief
 */ 

#include "StreamHandler.hpp"
#include <fstream>

namespace logging
{
namespace handler
{

class FileHandler : public StreamHandler
{
	public:
		explicit FileHandler(const std::string &filename, 
					const std::ios_base::openmode &mode = std::ios_base::app, 
					bool delay = false);
		~FileHandler();

		void			close();
		void			emit(logRecord::LogRecord &record);
		std::string		toString() const;

	private:
		std::string				_baseFilename;
		std::ios_base::openmode	_mode;
		bool					_delay;
		std::ofstream			_fstream;

		FileHandler(const FileHandler &rhs);
		FileHandler &operator=(const FileHandler &rhs);

		void _open();
};

} // !handler
} // !logging

#endif // !FILEHANDLER_HPP
