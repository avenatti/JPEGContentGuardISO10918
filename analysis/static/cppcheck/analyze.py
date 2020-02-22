#!/usr/bin/env python2.7


# This script performs static code analysis on the libjpeg and guard software using
# the opens sourcee cppcheck tool.


import subprocess
import sys
import os


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning directory ..."
   cmd = ["rm", "-rf", "code", "code_analysis", "guard_code"]
   subprocess.call (cmd)
   print "---> Cleaned."


# Copy the libjpeg files over.
def CopyLibJpegFiles ():
   print "---> Copying libjpeg files over ..."
   cmd = ["cp", "-r", "../../../jpeg-6b", "."]
   subprocess.call (cmd)
   cmd = ["mv", "jpeg-6b", "code"]
   subprocess.call (cmd)
   print "---> Copied libjpeg files."


# Copy the guard files over.
def CopyGuardFiles ():
   print "---> Copying guard files over ..."
   cmd = ["cp", "-r", "../../../guard", "."]
   subprocess.call (cmd)
   print "---> Copied guard files."


# Perform static analysis of the code.
def Analyze ():
   print "---> Statically analyzing the code."

   # Create a dirctory to hold the analysis information.
   cmd = ["mkdir", "-p", "code_analysis"]
   subprocess.call (cmd)

   # Perform the analysis.
   cmd = ["cppcheck", "--xml", "--check-library", "--enable=warning", "-v", "code"]
   p = subprocess.Popen (cmd, stderr=subprocess.PIPE)
   stdout, stderr = p.communicate ()

   # Write out the results.
   f = open ("code_analysis/analysis_results.xml", "w")
   f.write (stderr)
   f.close ()

   # Generate the html format of the results.
   cmd = ["cppcheck-htmlreport", 
          "--title=libjpeg-static-analysis", 
          "--file=code_analysis/analysis_results.xml", 
          "--report-dir=code_analysis", 
          "--source-dir=code"]
   subprocess.call (cmd)

   print "---> Finished statically analyzing the code."


# Perform static analysis of the guard code.
def AnalyzeGuard ():
   print "---> Statically analyzing the guard code."

   # Create a dirctory to hold the analysis information.
   cmd = ["mkdir", "-p", "code_analysis_guard"]
   subprocess.call (cmd)

   # Perform the analysis.
   cmd = ["cppcheck", "--xml", "--check-library", "--enable=warning", "-v", "guard/src"]
   p = subprocess.Popen (cmd, stderr=subprocess.PIPE)
   stdout, stderr = p.communicate ()

   # Write out the results.
   f = open ("code_analysis_guard/analysis_results.xml", "w")
   f.write (stderr)
   f.close ()

   # Generate the html format of the results.
   cmd = ["cppcheck-htmlreport", 
          "--title=guard-static-analysis", 
          "--file=code_analysis_guard/analysis_results.xml", 
          "--report-dir=code_analysis_guard", 
          "--source-dir=guard"]
   subprocess.call (cmd)

   print "---> Finished statically analyzing the guard code."


# Executes a step of sequences to produce the output data.
def Execute ():

   # 1. Clean out an remnants of previous runs.
   Clean ()

   # 2. Copy over a fresh copy of the libjpeg source code. 
   #CopyLibJpegFiles ()

   # 3. Execute the static analysis.
   #Analyze ()

   # 4. Display the analysis information.
   #os.system ("firefox -new-tab code_analysis/index.html &")

   # 5. Copy over a fresh copy of the guard source code.
   CopyGuardFiles ()

   # 6. Copy over a fresh copy of the guard source code.
   AnalyzeGuard ()

   # 7. Display the guard analysis information.
   os.system ("firefox -new-tab code_analysis_guard/index.html &")


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute.
   Execute ()








