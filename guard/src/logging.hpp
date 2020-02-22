


/// @file logging.hpp
///
/// @brief Definition for logging facilities.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/21/2020 	Initial version.


#ifndef __LOGGING_HPP__
#define __LOGGING_HPP__


#include <iostream>
#include <string>


/// Gets the current time stamp.
/// @return Current time stamp.
std::string GetTimeStamp ();


// Base log call for all logs.
#define LOG(str1, str2) do { std::cout << GetTimeStamp () << str1 << ": " << str2 << std::endl; } while (false)


// Info logging support.
#if defined INFO_LOGGING || defined ALL_LOGGING
#define INFO_LOG(str) do { LOG ("INFO", str); } while (false)
#else
#define INFO_LOG(str) do { } while (false)
#endif


// Error logging support.
#if defined ERROR_LOGGING || defined ALL_LOGGING
#define ERR_LOG(str) do { LOG ("ERROR", str); } while (false)
#else
#define ERR_LOG(str) do { } while (false)
#endif


// Metric logging support.
#if defined METRIC_LOGGING || defined ALL_LOGGING
#define METRIC_LOG(str) do { LOG ("METRIC", str); } while (false)
#else
#define METRIC_LOG(str) do { } while (false)
#endif


// Debug logging support.
#if defined DEBUG_LOGGING || defined ALL_LOGGING
#define DEBUG_LOG(str) do { LOG ("DEBUG", str); } while (false)
#else
#define DEBUG_LOG(str) do { } while (false)
#endif


#endif //__LOGGING_HPP__


