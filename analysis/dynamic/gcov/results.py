#!/usr/bin/env python2.7


# This script extracts the gcov results, placing it in a csv formatted file.


import subprocess
import os


# Some magic number definitions.
TEST_NAME_LINE = 31
HIT_SLOCS_LINE = 34
TOTAL_SLOCS_LINE = 35
COVERAGE_PERCENT_LINE = 36
DATE_LINE = 40


# Cleans the eviornment (directory) for a fresh run.
def Clean ():
   print "---> Cleaning results directory ..."
   cmd = ["rm", "-rf", "results"]
   subprocess.call (cmd)
   print "---> Cleaned results directory."


# Finds all index.html files directly located under the gcov_analysis directory 
# within each test directory.
def GetResultsFileList ():
   result = []
   curDir = os.getcwd ()
   cmd = ["find" , curDir, "-name", "index.html"]
   files = subprocess.check_output (cmd)
   for htmlFile in files.splitlines ():
      if (htmlFile.find ("gcov_analysis/index.html") > 0):
         result.append (htmlFile)
   return (result)


# Extracts the value from an html line.
def ExtractHtmlTagValue (line):
   startPos = line.find ('>') + 1
   endPos = line.find ('<', startPos)
   return (line[startPos:endPos])


# Extracts gcov results from a file, formatting with a csv layout.
def ExtractCsv (fileName):
   result = ""
 
   # Loop through each line in the file.
   with open (fileName) as file_in:
      number = 0
      for line in file_in:
         number += 1

         # Extract specific html tagged lines of text.
         if ((number == TEST_NAME_LINE) or
             (number == HIT_SLOCS_LINE) or
             (number == TOTAL_SLOCS_LINE) or
             (number == COVERAGE_PERCENT_LINE) or
             (number == DATE_LINE)):
            result += ExtractHtmlTagValue (line)
            result += ", "

   return (result)


# Executes a set of sequences to produce csv formated gcov data results.
def Execute ():

   # Clean up any previous runs.
   Clean ()

   # Make a new results directory.
   print "---> Preparing ..."
   curDir = os.getcwd ()
   newDir = os.path.join (curDir, "results")
   os.mkdir (newDir)
   print "---> Finished preparing"

   # Get a list of all the gcov files containing the parsed lcov results.
   print "---> Identifying available results."
   files = GetResultsFileList ()

   # Open a file for writing results to.
   print "---> Extracting csv formatted results ..."
   resultsFile = os.path.join (newDir, "results.csv")
   with open (resultsFile, 'a') as outFile:

      # Loop through each html file, extracting the csv formatted result info.
      for htmlFile in files:

         # Get the csv formatted result info.
         csvLine = ExtractCsv (htmlFile)
         csvLine += "\n"

         # Write it out to the results file.
         outFile.write (csvLine)

   print "---> Finised extracting csv formatted results."

   # Display the results with libre calc.
   os.system ("libreoffice --calc results/results.csv --infilter='CSV:44,34,0,1,4/2/1' &")

   
###############################################################################
# Script Execution.
###############################################################################

if __name__ == '__main__':

   # Execute.
   Execute ()





