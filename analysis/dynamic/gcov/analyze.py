#!/usr/bin/env python2.7


# This script ...


import subprocess
import patch
import os


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning directory ..."
   cmd = ["rm", "-rf", "djpeg", "rdjpegcom"]
   subprocess.call (cmd)
   print "---> Cleaned."


# Copy the libjpeg files over.
def CopyLibJpegFiles ():
   print "---> Copying libjpeg fies over ..."
   cmd = ["cp", "-r", "../../../jpeg-6b", "."]
   subprocess.call (cmd)
   cmd = ["mv", "jpeg-6b", "djpeg"]
   subprocess.call (cmd)
   cmd = ["cp", "-r", "../../../jpeg-6b", "."]
   subprocess.call (cmd)
   cmd = ["mv", "jpeg-6b", "rdjpegcom"]
   subprocess.call (cmd)
   print "---> Copied libjpeg files."


# Applies the configure patches to remove optimization and add gcov flags.
def PatchConfigFiles ():
   print "---> Patching confgure files with gcov settings ..."
   pset = patch.fromfile ("djpeg.patch.1")
   pset.apply ()
   pset = patch.fromfile ("rdjpegcom.patch.1")
   pset.apply ()
   print "---> Patched configure files."


# Applies the makefile patches to link in the gcov code.
def PatchMakeFiles ():
   print "---> Patching Makefiles with gcov settings ..."
   pset = patch.fromfile ("djpeg.patch.2")
   pset.apply ()
   pset = patch.fromfile ("rdjpegcom.patch.2")
   pset.apply ()
   print "---> Patched Makefiles."


# Executes a command in the provided sub directory.
# @param[in] sub_dir String of the subdirectory name.
# @param[in] cmd String of the command to execute.
def ExecuteSubDirCommand (sub_dir, cmd):
   print "---> Executing " + cmd + " for " + sub_dir 
   
   # Get the script execution directory.
   script_dir = os.getcwd () 

   # Switch directories.
   new_dir = os.path.join (script_dir, sub_dir) 
   os.chdir (new_dir)

   # Execute the command.
   new_cmd = [cmd]
   subprocess.call (new_cmd)

   # Change back to the script directory.
   os.chdir (script_dir)

   print "---> Executed " + cmd + " for " + sub_dir 


# Executes the configure command to setup the make system.
def ExecuteConfigure ():
   ExecuteSubDirCommand ("djpeg", "./configure")  
   ExecuteSubDirCommand ("rdjpegcom", "./configure")  


# Builds the binary executables.
def BuildExecutables ():
   ExecuteSubDirCommand ("djpeg", "make")  
   ExecuteSubDirCommand ("rdjpegcom", "make")  


###############################################################################
# Script Execution.
###############################################################################

# 1. Clean out an remnants of previous runs.
Clean ()

# 2. Copy over a fresh copy of the libjpeg source code. 
CopyLibJpegFiles ()

# 3. Patch the configure files.
PatchConfigFiles ()

# 4. Execute the configure command.
ExecuteConfigure ()

# 5. Patch the makefiles.
PatchMakeFiles ()

# 6. Build the executables.
BuildExecutables ()







