// TODO: Don't forget to add 42 header !

#ifndef PLACEHOLDER_HPP
#define PLACEHOLDER_HPP

/**
 * @file PlaceHolder.hpp
 * @brief
 */ 

#include "Node.hpp"
#include <set>

namespace logging
{
namespace placeholder
{

class PlaceHolder : public Node
{
	public:
		explicit PlaceHolder(Node *alogger);
		~PlaceHolder();

		PlaceHolder(const PlaceHolder &rhs);
		PlaceHolder &operator=(const PlaceHolder &rhs);

		void append(Node *alogger);
		const std::set<Node *> &getLoggerSet() const;

		std::string toString() const;

	private:
		std::set<Node*> _loggerSet;
};

} // !placeholder
} // !logging

#endif // !PLACEHOLDER_HPP
