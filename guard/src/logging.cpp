


/// @file logging.cpp
///
/// @brief Definition for logging facilities.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/21/2020 	Initial version.


#include "logging.hpp"
#include <chrono>
#include <ctime>


// Name spaces.
using namespace std;


/// Gets the current time stamp.
/// @return Current time stamp.
string GetTimeStamp ()
{
   string result;


   // Get the current time.
   auto curTime = chrono::system_clock::to_time_t (chrono::system_clock::now ());

   // Format it using ctime.
   result = ctime (&curTime);

   // Remove the end of line character that ctime puts on it.
   result.replace (result.size () -1, 1, " ");


   return (result);
}


