#!/usr/bin/env python2.7


# This script executes a libjpeg throfdbg with lean guard test.


import os
import sys
import utils


# Executes a djpeg test.
# name: string name of test.
def Execute (name):

   # 1. Setup some path variables.
   curDir = os.getcwd ()
   testDir = os.path.join (curDir, name)
   acceptDir = utils.GetLeanAcceptDir ()
   throfdbgDir = os.path.join (testDir, "throfdbg-lean-guard")
   codeDir = os.path.join (throfdbgDir, "throfdbg")

   # 2. Setup test envrionment.
   utils.ThrofdbgSetup (testDir, throfdbgDir)

   # 3. Execute the test.
   utils.RunThrofdbgTest (codeDir, acceptDir)

   # 4. Generate the analysis information.
   utils.GenerateAnalysisData (codeDir, name + "and-throfdbg")

   # 5. Display the analysis information.
   utils.DisplayAnalysisData (codeDir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute
   Execute (sys.argv[1])





