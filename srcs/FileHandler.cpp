// TODO: Don't forget to add 42 header !

#include "FileHandler.hpp"
#include <fstream>
#include <string>

namespace logging 
{
namespace handler
{

/**
 * @brief 
 *
 * @param filename 
 * @param mode 
 * @param delay 
 * @param errors 
 */
FileHandler::FileHandler(const std::string &filename, 
						 const std::ios_base::openmode &mode, 
						 bool delay) 
	: StreamHandler(), _baseFilename(filename), _mode(mode), _delay(delay), _fstream()
{
	if (!this->_delay)
	{
		this->_open();
		this->_stream = &this->_fstream;
	}
	else
		this->_stream = NULL;

}

/**
 * @brief 
 */
FileHandler::~FileHandler() 
{
	this->close();
}

/**
 * @brief 
 */
void	FileHandler::close()
{
	if (this->_stream)
	{
		this->flush();
		this->_fstream.close();
		this->_stream = NULL;
	}
	this->_closed = true;
}

/**
 * @brief 
 */
void	FileHandler::_open()
{
	if (this->_fstream.is_open())
		return ;
	this->_fstream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	this->_fstream.open(this->_baseFilename.c_str(), this->_mode);
}

/**
 * @brief 
 *
 * @param record 
 */
void	FileHandler::emit(logRecord::LogRecord &record)
{
	if (!this->_stream)
	{
		if (this->_mode != std::ios_base::out || !this->_closed)
		{
			this->_open();
			this->_stream = &this->_fstream;
		}
	}
	if (this->_stream)
		StreamHandler::emit(record);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	FileHandler::toString() const
{
	return ("<FileHandler (" + logRecord::levelToString(this->_level) + ")>");
}

} // !handler
} // !logging
