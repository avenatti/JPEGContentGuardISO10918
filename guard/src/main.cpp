


/// @file main.cpp
///
/// @brief JPEG content guard for ISO 10918.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson	2/8/2020 	Initial version.


#include "logging.hpp"
#include "utils.hpp"
#include "Config.hpp"
#include "Gauntlet.hpp"
#include "Metrics.hpp"
#include <vector>
#include <experimental/filesystem>


// Name spaces.
using namespace std;
namespace fs = std::experimental::filesystem;


/// Logs the calling command line arguments.
/// @param[in] argc Standard C++ argc, which is the number of argv items.
/// @param[in] argv Standard C++ argv, which is the provided command line arguments.
/// @return void.
void LogCommandLineArgs (int argc, char* argv[])
{
   string cmdLine = "Command Line Arguments: ";


   // Buld the command line string.
   for (int i = 0; i < argc; i++)
   {
      cmdLine += argv[i];
      cmdLine += " ";
   }

   // Log the arguments.
   INFO_LOG (cmdLine);
}


/// Parses the application provided command line arguments.
/// @param[in] argc Standard C++ argc, which is the number of argv items.
/// @param[in] argv Standard C++ argv, which is the provided command line arguments.
/// @param[out] config Will hold the configuration file path/name.
/// @return true on succes, false otherwise.
bool ParseCommandLineArgs (int argc, char* argv[], string& config)
{
   bool result = false;


   // Expected number for arguments?
   if (argc == 3)
   {
      // Loop through the arguments.
      for (int i = 0; i < argc; i++)
      {
         string cmd = argv[i];


         if (cmd.compare ("--cfg") == 0)
         {
            config = argv[(i + 1)]; 
            i++;
         }
      }
   }

   // Did we get what was expected?
   if (config.length () > 0)
      result = true;

   return (result);
}


/// Entry point for the guard application.
/// Usage:  guard --cfg <file_name>.
/// @param[in] argc Standard C++ argc, which is the number of argv items.
/// @param[in] arvg Standard C++ argv, which is the provided command line arguments.
/// @return ???
int main (int argc, char* argv[])
{
   string configFile;
   Settings settings;
   vector<string> files;


   // Log startup info.
   LogCommandLineArgs (argc, argv);
   INFO_LOG ("Starting Guard.");

   // Parse the command line arguments.
   if (ParseCommandLineArgs (argc, argv, configFile) == true)
   {
      // Parse the configuration.
      Config config (configFile);
      if (config.Parse () == true)
      {
         // Get the settings.
         settings = config.GetSettings ();
         settings.Log ();

         // Create the accept and drop directories.
         if (fs::exists (settings.acceptDir) == false)
            fs::create_directory (settings.acceptDir);

         if (fs::exists (settings.dropDir) == false)
            fs::create_directory (settings.dropDir);

         // Allocate and initialize the gauntlet.
         Gauntlet gauntlet (settings);

         // Get a list of jpeg image files to process.
         files = GetDirFiles (settings.imageDir);

         // Run each file through the gauntlet.
         for (int i = 0; i < files.size (); i++)
         {
            bool accept = gauntlet.Run (files[i]);  

            // Copy file to either the accept for drop directories.
            if (accept == true)
               fs::copy (files[i], settings.acceptDir, fs::copy_options::overwrite_existing);     
            else
               fs::copy (files[i], settings.dropDir, fs::copy_options::overwrite_existing);     
         }

         // Log the final metric information.
         Metrics metrics = gauntlet.GetMetrics ();
         metrics.Log ();
      }
   }
   else
   {
      ERR_LOG  ("Invalid calling arguments.");
      ERR_LOG  ("Usage:  guard --cfg <file_name>");
   } 
   
   INFO_LOG ("Exiting Guard.");
}






