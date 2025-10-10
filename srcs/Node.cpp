// TODO: Don't forget to add 42 header !

/**
 * @file Node.cpp
 * @brief
 */ 

#include "Node.hpp"
#include <string>

namespace logging
{

/**
 * @brief 
 *
 * @param name 
 */
Node::Node(const std::string &name) : _name(name), _parent(NULL) {}

/**
 * @brief 
 */
Node::~Node() {};

/**
 * @brief 
 *
 * @param rhs 
 */
Node::Node(const Node &rhs) : _name(rhs._name), _parent(rhs._parent) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
Node &Node::operator=(const Node &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_parent = rhs._parent;
	}
	return (*this);
}

/**
 * @brief 
 *
 * @return 
 */
const std::string	&Node::getName() const
{
	return (this->_name);
}

/**
 * @brief 
 *
 * @return 
 */
Node	*Node::getParent() const
{
	return (this->_parent);
}

/**
 * @brief 
 *
 * @param parent 
 */
void	Node::setParent(Node *parent)
{
	this->_parent = parent;
}

}
