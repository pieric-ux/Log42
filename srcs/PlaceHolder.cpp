// TODO: Don't forget to add 42 header !

/**
 * @file PlaceHolder.cpp
 * @brief
 */ 

#include "Node.hpp"
#include "PlaceHolder.hpp"

namespace logging
{
namespace placeholder
{

/**
 * @brief 
 *
 * @param alogger 
 */
PlaceHolder::PlaceHolder(Node *alogger) : Node(alogger ? alogger->getName() : ""), _loggerSet()
{
	if (alogger)
		this->_loggerSet.insert(alogger);
};

/**
 * @brief 
 */
PlaceHolder::~PlaceHolder() {}

/**
 * @brief 
 *
 * @param rhs 
 */
PlaceHolder::PlaceHolder(const PlaceHolder &rhs) : Node(rhs), _loggerSet(rhs._loggerSet) {}

/**
 * @brief 
 *
 * @param rhs 
 * @return 
 */
PlaceHolder &PlaceHolder::operator=(const PlaceHolder &rhs) 
{
	if (this != &rhs)
	{
		Node::operator=(rhs);
		this->_loggerSet = rhs._loggerSet;
	}
	return (*this);
}

/**
 * @brief 
 *
 * @param alogger 
 */
void	PlaceHolder::append(Node *alogger)
{
	if (alogger)
		this->_loggerSet.insert(alogger);
}

/**
 * @brief 
 *
 * @return 
 */
const std::set<Node *> &PlaceHolder::getLoggerSet() const
{
	return (this->_loggerSet);
}


/**
 * @brief 
 *
 * @return 
 */
std::string PlaceHolder::toString() const
{
    return ("<PlaceHolder " + getName());
}

} // !placeholder
} // !logging
