#!/usr/bin/env python2.7


# This script executes a lean guard test.


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
   guardDir = os.path.join (testDir, "lean-guard")
   acceptDir = os.path.join (guardDir, "accept")
   dropDir = os.path.join (guardDir, "drop")
   executable = os.path.join (guardDir, "build/bin/lean-guard")

   # 2. Setup test envrionment.
   utils.LeanGuardSetup (testDir, guardDir)

   # 3. Execute the test for each image.
   images = os.listdir (sampleDir)
   for image in images:
      fullPath = os.path.join (sampleDir, image)
      utils.RunLeanGuardTest (executable, fullPath, acceptDir, dropDir)

   # 4. Generate the analysis information.
   utils.GenerateAnalysisData (guardDir, name + "-lean-guard-")

   # 5. Display the analysis information.
   utils.DisplayAnalysisData (guardDir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute
   Execute (sys.argv[1])





