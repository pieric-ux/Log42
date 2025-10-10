// TODO: Don't forget to add 42 header !

/**
 * @file timeUtils.cpp
 * @brief
 */ 

#include "sys/time.h"
#include <ctime>
#include <cstring>

namespace utils
{

/**
 * @brief 
 *
 * @return 
 */
std::time_t	nowSec()
{
	return (std::time(NULL));
}

/**
 * @brief 
 *
 * @return 
 */
long	nowMilli()
{
	struct timeval tv; // TODO: forbidden function

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000);
}

/**
 * @brief 
 *
 * @param startTime 
 * @return 
 */
double	relativeSec(const clock_t &startTime)
{
	return ((static_cast<double>(std::clock()) - startTime) / CLOCKS_PER_SEC);
}

} // !utils
