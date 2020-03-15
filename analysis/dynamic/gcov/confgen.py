#!/usr/bin/env python2.7


# This script generates test configurations.


import subprocess
import os


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning directory ..."
   cmd = ["rm", "-rf", "configs"]
   subprocess.call (cmd)
   print "---> Cleaned."


# Prepares for the creation of configurations.
def Prepare ():
   print "---> Preparing."
   curPath = os.getcwd ()
   newDir = os.path.join (curPath, "configs")
   os.mkdir (newDir)
   print "---> Finished preparing."


# Gets the config string for a feature boolean value.
def EnableDisable (boolVal):
    result = "disable \n"

    if (boolVal == True):
       result = "enable \n"

    return (result)


# Creates a single test configuration.  The args specify what is enabled.
# name = name of the test
# args:
#    sdm  // sequential-dct-mode
#    pdm  // progressive-dct-mode
#    lm   // lossless-mode
#    hm   // hierarchical-mode
#    he   // huffman-encoding
#    ae   // arithmetic-encoding
def CreateTest (name, *args):

   # Get the config settings.
   sdm = ("sdm" in args)
   pdm = ("pdm" in args)
   lm = ("lm" in args)
   hm = ("hm" in args)
   he = ("he" in args)
   ae = ("ae" in args)

   # Get the image directories.
   curPath = os.getcwd ()
   os.chdir ("../../../samples")
   sampleDir = os.getcwd ()
   os.chdir (curPath)

   acceptDir = os.path.join (curPath, name + "/guard/accept")
   dropDir = os.path.join (curPath, name + "/guard/drop")

   # Write out the settings.
   fileName = "configs/" + name + ".cfg"
   config = open (fileName, "a")
   config.write ("image-dir = " + sampleDir + "\n")
   config.write ("accept-dir = " + acceptDir + "\n")
   config.write ("drop-dir = " + dropDir + "\n")
   config.write ("sequential-dct-mode = " + EnableDisable (sdm))
   config.write ("progressive-dct-mode = " + EnableDisable (pdm))
   config.write ("lossless-mode = " + EnableDisable (lm))
   config.write ("hierarchical-mode = " + EnableDisable (hm))
   config.write ("huffman-encoding = " + EnableDisable (he))
   config.write ("arithmetic-encoding = " + EnableDisable (ae))
   config.close ()
   

# Generates the test configurations.
def Generate ():

   # 1. Clean out an remnants of previous runs.
   Clean ()

   # 2. Create the configuration directory.
   Prepare ()

   # 3. Create the individual tests.
   CreateTest ("test1", "sdm", "he", "ae")
   CreateTest ("test2", "sdm", "he")
   CreateTest ("test3", "sdm", "ae")
   CreateTest ("test4", "pdm", "he", "ae")
   CreateTest ("test5", "pdm", "he")
   CreateTest ("test6", "pdm", "ae")
   CreateTest ("test7", "lm", "he")


###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Generate the configurations.
   Generate ()





