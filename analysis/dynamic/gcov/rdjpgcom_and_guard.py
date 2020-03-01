#!/usr/bin/env python2.7


# This script executes a rdjpgcom standalone test.


import os
import sys
import utils


# Executes a rdjpgcom test.
# name: string name of test.
def Execute (name):

   # 1. Setup some path variables.
   configFileName = name + ".cfg"
   curDir = os.getcwd ()
   configDir = os.path.join (curDir, "configs")
   testDir = os.path.join (curDir, name)
   configFile = os.path.join (configDir, configFileName)
   acceptDir = utils.GetAcceptDir (configFile)
   rdjpgcomDir = os.path.join (testDir, "rdjpgcom-guard")
   codeDir = os.path.join (rdjpgcomDir, "jpeg-6b")

   # 2. Setup test envrionment.
   utils.RdjpgcomSetup (testDir, rdjpgcomDir)

   # 3. Execute the test.
   utils.RunRdjpgcomTest (codeDir, acceptDir)

   # 4. Generate the analysis information.
   utils.GenerateAnalysisData (codeDir, name + "-rdjpgcom-and-guard")

   # 5. Display the analysis information.
   utils.DisplayAnalysisData (codeDir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute
   Execute (sys.argv[1])





