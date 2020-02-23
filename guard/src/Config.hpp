


/// @file Config.hpp
///
/// @brief Definition for Configuration class to parse configuration files.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/22/2020 	Initial version.


#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__


#include <string>
#include <vector>


/// Structure that holds parsed configuration settings.
struct Settings
{
   std::string imageDir = "unset";   
   std::string acceptDir = "unset";   
   std::string dropDir = "unset";   
   bool sequentialDctMode = false;
   bool progressiveDctMode = false;
   bool losslessMode = false;
   bool hierarchicalMode = false;
   bool huffmanEncoding = false;
   bool arithmeticEncoding = false;

   
   /// Logs the structure contents.
   /// @return void.
   void Log ();
};


class Config
{
   public:
      
      /// Constructor.
      /// @param[in] configFile Configuration file to parse.
      Config (std::string& configFile);


      /// Destructor.
      ~Config ();


      /// Parses the configuration file.
      /// @return true on success, false otherwise.
      bool Parse ();


      /// Gets the current settings.
      /// @return a copy of the settings.
      Settings GetSettings ();


   private:
   
      std::string m_file;    ///< Config file.
      Settings m_settings;   ///< Parsed config settings.


      /// Constructor (private).
      Config ();


      /// Verifies if a path or file exists.
      /// @param[in] name Path/file to check. 
      /// @return true if exists, false otherwise.
      bool Exists (std::string& name);


      /// Parses a configuration line of text.
      /// @param[in] line Text line to parse.
      /// @return void.
      void ParseLine (std::string& line);


      /// Splits a string into separate pieces.
      /// @param[in] str String to split up.
      /// @param[in] delimiter Delimiter to use for the splitting.
      /// @return a vector of split pieces.
      std::vector<std::string> SplitStr (std::string& str, std::string& delimiter);
};


#endif //__CONFIG_HPP__


