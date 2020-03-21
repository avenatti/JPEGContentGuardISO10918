#!/usr/bin/env python2.7


# This script executes a libjpeg turbo mozilla djpeg with lean guard test .


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
   djpegDir = os.path.join (testDir, "djpeg-moz")
   codeDir = os.path.join (djpegDir, "mozjpeg-3.3.1")

   # 2. Setup test envrionment.
   utils.DjpegMozSetup (testDir, djpegDir)

   # 3. Execute the test.
   utils.RunDjpegTest (codeDir, acceptDir)

   # 4. Generate the analysis information.
   utils.GenerateAnalysisData (codeDir, name + "-and-djpg-mozilla")

   # 5. Display the analysis information.
   utils.DisplayAnalysisData (codeDir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute
   Execute (sys.argv[1])





