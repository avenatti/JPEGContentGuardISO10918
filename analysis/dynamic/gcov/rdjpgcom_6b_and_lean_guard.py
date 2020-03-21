#!/usr/bin/env python2.7


# This script executes a libjpeg 6b rdjpgcom test with the lean guard.


import os
import sys
import utils


# Executes a rdjpgcom test.
# name: string name of test.
def Execute (name):

   # 1. Setup some path variables.
   curDir = os.getcwd ()
   testDir = os.path.join (curDir, name)
   acceptDir = utils.GetLeanAcceptDir ()
   rdjpgcomDir = os.path.join (testDir, "rdjpgcom-6b-lean-guard")
   codeDir = os.path.join (rdjpgcomDir, "jpeg-6b")

   # 2. Setup test envrionment.
   utils.RdjpgcomSetup (testDir, rdjpgcomDir)

   # 3. Execute the test.
   utils.RunRdjpgcomTest (codeDir, acceptDir)

   # 4. Generate the analysis information.
   utils.GenerateAnalysisData (codeDir, name + "-and-rdjpgcom-6b")

   # 5. Display the analysis information.
   utils.DisplayAnalysisData (codeDir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute
   Execute (sys.argv[1])





