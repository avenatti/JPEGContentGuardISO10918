#!/usr/bin/env python2.7


# This script executes a libjpeg 6b djpeg standalone test.


import os
import sys
import utils


# Executes a djpeg test.
# name: string name of test.
def Execute (name):

   # 1. Setup some path variables.
   sampleDir = utils.GetSampleDir ()
   curDir = os.getcwd ()
   testDir = os.path.join (curDir, name)
   djpegDir = os.path.join (testDir, "djpeg-6b-standalone")
   codeDir = os.path.join (djpegDir, "jpeg-6b")

   # 2. Setup test envrionment.
   utils.Djpeg6bSetup (testDir, djpegDir)

   # 3. Execute the test.
   utils.RunDjpegTest (codeDir, sampleDir)

   # 4. Generate the analysis information.
   utils.GenerateAnalysisData (codeDir, name + "-djpg-6b-standalone")

   # 5. Display the analysis information.
   utils.DisplayAnalysisData (codeDir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute
   Execute (sys.argv[1])





