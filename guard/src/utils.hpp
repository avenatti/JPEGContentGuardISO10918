


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
#include <sys/stat.h>


/// Splits a string into separate pieces.
/// @param[in] str String to split up.
/// @param[in] delimiter Delimiter to use for the splitting.
/// @return a vector of split pieces.
std::vector<std::string> SplitStr (std::string& str, std::string& delimiter);


/// Gets the files located in a specified directory.
/// @param[in] dir String containing the directory to get files from.
/// @return a vector of files.
std::vector<std::string> GetDirFiles (std::string& dir);


/// Verifies if a path or file exists.
/// @param[in] name Path/file to check. 
/// @return true if exists, false otherwise.
bool Exists (std::string& name);


/// Creates a directory if it doesn't already exist.
/// @param[in] dir Directory to create.
/// @return void.
void CreateDir (std::string& dir);


/// Looks for the expected first marker in jpeg file.
/// @param[in] name File name.
/// @return size of the file.
int GetFileSize (std::string& name);


#endif //__UTILS_HPP__


