// TODO: Don't forget to add 42 header !

#ifndef NODE_HPP
#define NODE_HPP

/**
 * @file Node.hpp
 * @brief
 */ 

#include <string>

namespace logging
{

class Node
{
	public:
		explicit Node(const std::string &name);
		virtual ~Node();

		Node(const Node &rhs);
		Node &operator=(const Node &rhs);

		const std::string	&getName() const;
		Node			*getParent() const;
		void				setParent(Node *Parent);

		virtual std::string toString() const = 0;

	protected:
		std::string _name;
		Node		*_parent;
		
};

} //!logging

#endif // !NODE_HPP
