#!/usr/bin/env python2.7


# This is the high level analysis script generates all the analysis information for
# the libjpeg and guard software.


import dynamic.gcov.analyze
import static.cppcheck.analyze
import os
import subprocess


# Executes the dynamic gcov analsyis.
def ExecuteGcov ():
   
   # Get the script execution directory.
   script_dir = os.getcwd () 

   # Switch directories.
   new_dir = os.path.join (script_dir, "dynamic/gcov") 
   os.chdir (new_dir)

   # Execute the gcov analysis script.
   dynamic.gcov.analyze.Execute ()

   # Change back to the script directory.
   os.chdir (script_dir)


# Executes the static cppcheck analsyis.
def ExecuteCppcheck ():
   
   # Get the script execution directory.
   script_dir = os.getcwd () 

   # Switch directories.
   new_dir = os.path.join (script_dir, "static/cppcheck") 
   os.chdir (new_dir)

   # Execute the gcov analysis script.
   static.cppcheck.analyze.Execute ()

   # Change back to the script directory.
   os.chdir (script_dir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Generate the gcov analysis.
   ExecuteGcov ()

   # Generate the cppcheck analysis.
   ExecuteCppcheck ()





