# minitalk

The purpose of this project is to code a small data exchange program using UNIX signals.

Client must communicate a string passed as a parameter to server (referenced by its process ID) which then displays it.

## Installation

* To compile
  * make
* To remove objects:
  * make clean
* To remove objects and binary file (program):
  * make fclean
* To re-compile:
  * make re
 
## Running

  * In terminal #1
    
        ./server
    The Server displays its PID.
  * In terminal #2

        ./client <server PID> <message>
