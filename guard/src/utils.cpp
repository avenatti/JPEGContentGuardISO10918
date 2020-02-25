


/// @file utils.cpp
///
/// @brief Implementation of various utility support functions.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/20/2020 	Initial version.


#include "utils.hpp"
#include "dirent.h"
#include <cstdlib>


// Name spaces.
using namespace std;


/// Splits a string into separate pieces.
/// @param[in] str String to split up.
/// @param[in] delimiter Delimiter to use for the splitting.
/// @return a vector of split pieces.
vector<string> SplitStr (string& str, string& delimiter)
{
   vector<string> result;
   string::size_type pos = 0;
   string::size_type prev = 0;

   // Walk the string.
   while ((pos = str.find (delimiter, prev)) != string::npos)
   {
      result.push_back (str.substr (prev, pos - prev));
      prev = pos + 1;
   }

   // Capture the last delimiter piece.
   result.push_back (str.substr (prev));

   return (result);
}


/// Gets the files located in a specified directory.
/// @param[in] dir String containing the directory to get files from.
/// @return a vector of files.
vector<string> GetDirFiles (string& dir)
{
   vector<string> result;
   DIR* pDir = nullptr;
   struct dirent* pEnt = nullptr;
   string currentDir = ".";
   string parentDir = "..";


   // Try opening the directory.
   pDir = opendir (dir.c_str ());
   if (pDir != nullptr)
   {
      // Put each file on the result vector.
      do 
      {
         // Get next file.
         pEnt = readdir (pDir);
         if (pEnt != nullptr)
         {
            if ((currentDir.compare (pEnt->d_name) != 0) &&
                (parentDir.compare (pEnt->d_name) != 0))
            {
               result.push_back (dir + "/" + pEnt->d_name);
            }
         }
         
      } while (pEnt != nullptr);
   } 

   return (result);
}


