README.txt


Overview:
----------
The analysis/dynamic/gcov directory contains support for using gcov to analyze the 
libjbeg and guard software.  It makes independent copies of the libjpeg binaries 
being evaluated, patches them to use gcov support, executes the binaries, and then 
captures the analysis output information. 


Running:
----------
To run the script:
   cd <analysis/dynamic/gcov directory>
   ./analyze.py


General Notes:
----------
The analyze.py script must be ran within the analysis/dynamic/gcov directory.

Patch were created using command:  diff -Naur <new-file> <old-file>

