#!/usr/bin/env python2.7


# This script performs static code analysis on the libjpeg and guard software using
# the opens sourcee cppcheck tool.


import subprocess
import sys
import os


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning directory ..."
   cmd = ["rm", "-rf", "code", "code_analysis"]
   subprocess.call (cmd)
   print "---> Cleaned."


# Copy the libjpeg files over.
def CopyLibJpegFiles ():
   print "---> Copying libjpeg fies over ..."
   cmd = ["cp", "-r", "../../../jpeg-6b", "."]
   subprocess.call (cmd)
   cmd = ["mv", "jpeg-6b", "code"]
   subprocess.call (cmd)
   print "---> Copied libjpeg files."


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



###############################################################################
# Script Execution.
###############################################################################

# 1. Clean out an remnants of previous runs.
Clean ()

# 2. Copy over a fresh copy of the libjpeg source code. 
CopyLibJpegFiles ()

# 3. Execute the static analysis.
Analyze ()

# 4. Display the analysis information.
os.system ("firefox code_analysis/index.html &")







