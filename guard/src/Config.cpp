


/// @file Config.cpp
///
/// @brief Implementation for Configuration class to parse configuration files.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/22/2020 	Initial version.


#include "Config.hpp"
#include "logging.hpp"
#include "utils.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <experimental/filesystem>


// Name spaces.
using namespace std;
namespace fs = std::experimental::filesystem;


/// Constructor.
/// @param[in] configFile Configuration file to parse.
Config::Config (std::string& configFile)
 : m_file (configFile)
{

}


/// Constructor (private).
Config::Config ()
{

}


/// Destructor.
Config::~Config ()
{

}


/// Parses the configuration file.
/// @return true on success, false otherwise.
bool Config::Parse ()
{
   bool result = false;
   string line;


   // Verify the config file exists.
   if (fs::exists (m_file) == true)
   {
      INFO_LOG ("Parsing configuration file \"" << m_file << "\".");
      result = true;

      // Open the file as a string stream.
      ifstream infile (m_file.c_str ());


      // Read in one line at a time and parse it.
      while (getline (infile, line))
         ParseLine (line);

      // Ensure the image directory exists.
      if (fs::exists (m_settings.imageDir) == false)
      {
         ERR_LOG ("Image directory \"" << m_settings.imageDir << "\" doesn't exist");
         result = false;
      }
   }
   else
      ERR_LOG ("Configuration (" << m_file << ") doesn't exist.");

   return (result);
}


/// Parses a configuration line of text.
/// @param[in] line Text line to parse.
/// @return void.
void Config::ParseLine (string& line)
{
   vector<string> tuples;
   string equalDelimiter = "=";

   
   // Prepare the string for tuple splitting.
   line.erase (remove (line.begin (), line.end (), ' '), line.end ());
   line.erase (remove (line.begin (), line.end (), '\t'), line.end ());

   // Split the line up into tuples.
   tuples = SplitStr (line, equalDelimiter);

   // Ensure there are exactly 2 tuples.
   if (tuples.size () == 2)
   {
      if (tuples[0].compare ("image-dir") == 0)
      {
         m_settings.imageDir = tuples[1]; 
      }
      else if (tuples[0].compare ("accept-dir") == 0)
      {
         m_settings.acceptDir= tuples[1]; 
      }
      else if (tuples[0].compare ("drop-dir") == 0)
      {
         m_settings.dropDir = tuples[1]; 
      }
      else if (tuples[0].compare ("sequential-dct-mode") == 0)
      {
         if (tuples[1].compare ("enable") == 0) 
            m_settings.sequentialDctMode = true;
      }
      else if (tuples[0].compare ("progressive-dct-mode") == 0)
      {
         if (tuples[1].compare ("enable") == 0) 
            m_settings.progressiveDctMode = true;
      }
      else if (tuples[0].compare ("lossless-mode") == 0)
      {
         if (tuples[1].compare ("enable") == 0) 
            m_settings.losslessMode = true;
      }
      else if (tuples[0].compare ("hierarchical-mode") == 0)
      {
         if (tuples[1].compare ("enable") == 0) 
            m_settings.hierarchicalMode = true;
      }
      else if (tuples[0].compare ("huffman-encoding") == 0)
      {
         if (tuples[1].compare ("enable") == 0) 
            m_settings.huffmanEncoding = true;
      }
      else if (tuples[0].compare ("arithmetic-encoding") == 0)
      {
         if (tuples[1].compare ("enable") == 0) 
            m_settings.arithmeticEncoding = true;
      }
   }
   else
   {
      ERR_LOG ("Invalid config line \"" << line << "\".");
      ERR_LOG ("Size = " << tuples.size ());
   }
}


/// Gets the current settings.
/// @return a copy of the settings.
Settings Config::GetSettings ()
{
   return (m_settings);
}


/// Logs the structure contents.
/// @return void.
void Settings::Log ()
{
   DEBUG_LOG ("Configuration settings:");
   DEBUG_LOG ("  imageDir = " << imageDir);
   DEBUG_LOG ("  acceptDir = " << acceptDir);
   DEBUG_LOG ("  dropDir = " << dropDir);
   DEBUG_LOG ("  sequentialDctMode = " << sequentialDctMode);
   DEBUG_LOG ("  progressiveDctMode = " << progressiveDctMode);
   DEBUG_LOG ("  losslessMode = " << losslessMode);
   DEBUG_LOG ("  hierarchicalMode = " << hierarchicalMode);
   DEBUG_LOG ("  huffmanEncoding = " << huffmanEncoding);
   DEBUG_LOG ("  arithmeticEncoding = " << arithmeticEncoding);
}



