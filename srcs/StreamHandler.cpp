// TODO: Don't forget to add 42 header !

/**
 * @file StreamHandler.hpp
 * @brief
 */ 

#include "StreamHandler.hpp"
#include <iostream>

namespace logging
{
namespace handler
{

/**
 * @brief 
 *
 * @param stream 
 */
StreamHandler::StreamHandler(std::ostream &stream) : Handler(), _stream(&stream) {}

/**
 * @brief 
 */
StreamHandler::~StreamHandler() {}

/**
 * @brief 
 *
 * @param rhs 
 */
StreamHandler::StreamHandler(const StreamHandler &rhs) : Handler(rhs), _stream(rhs._stream) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
StreamHandler	&StreamHandler::operator=(const StreamHandler &rhs)
{
	if (this != &rhs)
	{
		Handler::operator=(rhs);
		this->_stream = rhs._stream;
	}
	return (*this);
}

/**
 * @brief 
 */
void	StreamHandler::flush()
{
	if (this->_stream)
		this->_stream->flush();
}

/**
 * @brief 
 *
 * @param record 
 */
void	StreamHandler::emit(logRecord::LogRecord &record)
{
	try
	{
		std::string msg = this->format(record);
		*this->_stream << msg << "\n";	
		this->flush();
	}
	catch (...)
	{
		this->handlerError(record);
	}
}

/**
 * @brief 
 *
 * @param stream 
 */
std::ostream	&StreamHandler::setStream(std::ostream &stream)
{
	std::ostream	&old = *this->_stream;
	this->flush();
	this->_stream = &stream;
	return (old);
}

/**
 * @brief 
 *
 * @return 
 */
std::string	StreamHandler::toString() const
{
	return ("<StreamHandler (" + logRecord::levelToString(this->_level) + ")>");
}

} //!handler
} //!logging
