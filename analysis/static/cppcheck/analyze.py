#!/usr/bin/env python2.7


# This script performs static code analysis on the libjpeg and guard software using
# the opens sourcee cppcheck tool.


import subprocess
import sys
import os
import time


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning directory ..."
   cmd = ["rm", "-rf", "analysis_guard", "analysis_jpeg-6b", "analysis_libjpeg-turbo-2.0.4"]
   subprocess.call (cmd)
   cmd = ["rm", "-rf", "guard", "jpeg-6b", "libjpeg-turbo-2.0.4"]
   subprocess.call (cmd)
   print "---> Cleaned."


# Copy source files.
def CopySourceFiles (srcDir):
   print "---> Copying " + srcDir + " files over ..."
   fileDir = os.path.join ("../../..", srcDir)
   cmd = ["cp", "-r", fileDir, "."]
   subprocess.call (cmd)
   print "---> Finished copying " + srcDir + " files over."


# Analyzes source code.
def Analyze (srcDir, arg1=None):
   print "---> Statically analyzing the " + srcDir + " code ..."

   # Create a dirctory to hold the analysis information.
   curDir = os.getcwd ()
   analysisDir = "analysis_" + srcDir
   cmd = ["mkdir", "-p", analysisDir]
   subprocess.call (cmd)

   # Perform the analysis.
   analyze = os.path.join (curDir, srcDir)
   if (arg1 is not None):
      analyze = os.path.join (analyze, arg1)

   cmd = ["cppcheck", "--xml", "--check-library", "--enable=warning", "-v", analyze]
   p = subprocess.Popen (cmd, stderr=subprocess.PIPE)
   stdout, stderr = p.communicate ()

   # Write out the results.
   fileName = os.path.join (analysisDir, "analysis_result.xml")
   f = open (fileName, "w")
   f.write (stderr)
   f.close ()

   # Generate the html format of the results.
   cmd = ["cppcheck-htmlreport", 
          "--title=" + srcDir + "-static-analysis", 
          "--file=" + fileName,
          "--report-dir=" + analysisDir,
          "--source-dir=" + analyze]
   subprocess.call (cmd)

   # Display the analysis results.
   indexFile = os.path.join (analysisDir, "index.html") 
   time.sleep (1)
   os.system ("firefox -new-tab " + indexFile + " &")

   print "---> Finished statically analyzing the " + srcDir + " code ..."
   print "MWB:  analyze = " + analyze


# Executes a step of sequences to produce the output data.
def Execute ():

   # 1. Clean out an remnants of previous runs.
   Clean ()

   # 2. Copy and anlyze the libjpeg 6b files.
   CopySourceFiles ("jpeg-6b")
   Analyze ("jpeg-6b")

   # 3. Copy and anlyze the libjpeg turbo files.
   CopySourceFiles ("libjpeg-turbo-2.0.4")
   Analyze ("libjpeg-turbo-2.0.4")

   # 4. Copy and anlyze the guard files.
   CopySourceFiles ("guard")
   Analyze ("guard", "src")


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute.
   Execute ()


