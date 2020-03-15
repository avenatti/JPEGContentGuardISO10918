#!/usr/bin/env python2.7


# This script performs gcov dynamic analysis analysis on the djpeg and rdjpgcom 
# executables in libjpeg.


import subprocess
import os
import confgen
import djpg_6b_standalone
import djpg_turbo_standalone
import djpg_moz_standalone
import rdjpgcom_6b_standalone
import rdjpgcom_turbo_standalone
import rdjpgcom_moz_standalone
import guard
import djpg_6b_and_guard
import djpg_turbo_and_guard
import djpg_moz_and_guard
import rdjpgcom_6b_and_guard
import rdjpgcom_turbo_and_guard
import rdjpgcom_moz_and_guard


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning directory ..."
   cmd = ["rm", "-rf", "*.pyc", "baseline", "test1"]
   subprocess.call (cmd)
   print "---> Cleaned."


# Executes a step of sequences to produce the output data.
def Execute ():

   # 1. Clean out an remnants of previous runs.
   Clean ()

   # 2. Create the test configuration files.
   confgen.Generate ()

   # 3. Execute the standalone tests.
   curDir = os.getcwd ()
   baselineDir = os.path.join (curDir, "baseline")
   os.mkdir (baselineDir)
   djpg_6b_standalone.Execute ("baseline");
   djpg_turbo_standalone.Execute ("baseline");
   djpg_moz_standalone.Execute ("baseline");
   rdjpgcom_6b_standalone.Execute ("baseline")
   rdjpgcom_turbo_standalone.Execute ("baseline");
   rdjpgcom_moz_standalone.Execute ("baseline");

   # 4. Loop through each test configuration file.
   curDir = os.getcwd ()
   configDir = os.path.join (curDir, "configs")
   files = os.listdir (configDir)
   for configFile in files:
      pathFile = os.path.join (configDir, configFile)
      name = configFile.replace (".cfg", "")
      testDir = os.path.join (curDir, name)
      os.mkdir (testDir)
  
      # Execute the guard test.
      guard.Execute (name)

      # Execute the djpeg 6b filtered by guard test.
      djpg_6b_and_guard.Execute (name)

      # Execute the djpeg turbo filtered by guard test.
      djpg_turbo_and_guard.Execute (name)

      # Execute the djpeg turbo mozilla filtered by guard test.
      djpg_moz_and_guard.Execute (name)

      # Execute the rdjpgcom 6b filtered by guard test.
      djpgcom_6b_and_guard.Execute (name)

      # Execute the rdjpgcom turbo filtered by guard test.
      rdjpgcom_turbo_and_guard.Execute (name)

      # Execute the rdjpgcom turbo mozilla filtered by guard test.
      rdjpgcom_moz_and_guard.Execute (name)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute.
   Execute ()





