#!/usr/bin/env python2.7


# This script performs gcov dynamic analysis analysis on the djpeg and rdjpgcom 
# executables in libjpeg.


import subprocess
import os
import confgen
import djpg_standalone
import rdjpgcom_standalone
import guard
import djpg_and_guard
import rdjpgcom_and_guard


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning directory ..."
   cmd = ["rm", "-rf", "*.pyc", "test1"]
   subprocess.call (cmd)
   print "---> Cleaned."


# Executes a step of sequences to produce the output data.
def Execute ():

   # 1. Clean out an remnants of previous runs.
   Clean ()

   # 2. Create the test configuration files.
   confgen.Generate ()

   # 3. Loop through each test configuration file.
   curDir = os.getcwd ()
   configDir = os.path.join (curDir, "configs")
   files = os.listdir (configDir)
   for configFile in files:
      pathFile = os.path.join (configDir, configFile)
      name = configFile.replace (".cfg", "")
      testDir = os.path.join (curDir, name)
      os.mkdir (testDir)
  
      # Execute the djpeg standalone test.
      djpg_standalone.Execute (name)

      # Execute the rdjpgcom standalone test.
      rdjpgcom_standalone.Execute (name)

      # Execute the guard test.
      guard.Execute (name)

      # Execute the djpeg filtered by guard test.
      djpg_and_guard.Execute (name)

      # Execute the rdjpgcom filtered by guard test.
      rdjpgcom_and_guard.Execute (name)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute.
   Execute ()





