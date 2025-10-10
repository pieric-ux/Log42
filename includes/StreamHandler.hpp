// TODO: Don't forget to add 42 header !

#ifndef STREAMHANDLER_HPP
#define STREAMHANDLER_HPP

/**
 * @file Handler.hpp
 * @brief
 */ 

#include "Handler.hpp"
#include <iostream>

namespace logging
{
namespace handler
{

class StreamHandler : public Handler
{
	public:
		explicit StreamHandler(std::ostream &stream = std::cerr);
		virtual ~StreamHandler();

		StreamHandler &operator=(const StreamHandler &rhs);
		StreamHandler(const StreamHandler &rhs);

		void			flush();
		void			emit(logRecord::LogRecord &record);
		std::ostream	&setStream(std::ostream &ost);
		std::string		toString() const;

	protected:
		std::ostream *_stream;

};

} // !handler
} // !logging

#endif // !STREAMHANDLER_HPP
