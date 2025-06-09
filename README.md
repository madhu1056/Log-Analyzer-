**The Log-Analyzer project:** 
a C++ application that parses and analyzes large-scale log files (e.g., system logs, server logs) using multithreading to improve performance. 
It should support filtering, pattern detection (e.g., regex), and basic metrics like error counts, request rates, etc.

How to use:

Save the code as LogAnalyzer.cpp or what ever the name which suits the functionality.

Create a file logfile.txt in the same directory.
the logfile.txt should consists of some data like below:
      INFO Server started
      ERROR Disk not found
      INFO Request served
      ERROR Disk not found
      ERROR Connection timeout
      ERROR Disk not found

Run the LogAnalyzer.cpp file and the expected output should be something like below:
Error Summary:
ERROR Disk not found: 3
ERROR Connection timeout: 1
