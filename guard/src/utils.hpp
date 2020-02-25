


/// @file utils.hpp
///
/// @brief Definition of various utility support functions.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/20/2020 	Initial version.


#ifndef __UTILS_HPP__
#define __UTILS_HPP__


#include <vector>
#include <string>


/// Splits a string into separate pieces.
/// @param[in] str String to split up.
/// @param[in] delimiter Delimiter to use for the splitting.
/// @return a vector of split pieces.
std::vector<std::string> SplitStr (std::string& str, std::string& delimiter);


/// Gets the files located in a specified directory.
/// @param[in] dir String containing the directory to get files from.
/// @return a vector of files.
std::vector<std::string> GetDirFiles (std::string& dir);


#endif //__UTILS_HPP__


