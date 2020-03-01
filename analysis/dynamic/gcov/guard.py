#!/usr/bin/env python2.7


# This script executes a guard test.


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
   guardDir = os.path.join (testDir, "guard")
   executable = os.path.join (guardDir, "build/bin/guard")
   configFileName = name + ".cfg"
   configDir = os.path.join (curDir, "configs")
   testDir = os.path.join (curDir, name)
   configFile = os.path.join (configDir, configFileName)

   # 2. Setup test envrionment.
   utils.GuardSetup (testDir, guardDir)

   # 3. Execute the test.
   utils.RunGuardTest (executable, configFile)

   # 4. Generate the analysis information.
   utils.GenerateAnalysisData (guardDir, name + "-guard")

   # 5. Display the analysis information.
   utils.DisplayAnalysisData (guardDir)


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute
   Execute (sys.argv[1])





