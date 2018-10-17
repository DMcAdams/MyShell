# MyShell

Programmer: Darrin McAdams
Professor: Dr. J. Payton
Class: CIS 3207-10
Date: 10/17/2018

This program is an implementation of a unix-like shell. It supports basic IO redirection, piping, background execution, and .sh scripts.

built in commands:

|   Command      |                       Purpose                                          |
|_________________________________________________________________________________________|
| cd, chdir      | Changes current directory                                              |
|-----------------------------------------------------------------------------------------|
| clear, clr     | Clears the terminal                                                    |
|-----------------------------------------------------------------------------------------|
| echo           | Prints out the rest of the args                                        |
|-----------------------------------------------------------------------------------------|
| environ        | Prints out the current environment variables                           |
|-----------------------------------------------------------------------------------------|
| exit, quit     | Exit the shell                                                         |
|-----------------------------------------------------------------------------------------|
| ls, dir        | Outputs the contents of the current directory. Files beginning with "."|
|                |    hidden unless the "-a" arg is used                                  |
|-----------------------------------------------------------------------------------------|
| pause          | Pauses the shell untill the enter key is pressed.                      |
|-----------------------------------------------------------------------------------------|
| f1 | f2        | Pipes the output from f1 into f2                                       |
|-----------------------------------------------------------------------------------------|
| f < input      | Redirects f's input to input                                           |
|-----------------------------------------------------------------------------------------|
| f > output     | Redirects f's output to output                                         |
|-----------------------------------------------------------------------------------------|
| f >> output    | Appends f's output to output                                           |
|-----------------------------------------------------------------------------------------|
| script.sh      | Will attempt to find a .sh file named script, and execute it's commands|
|_________________________________________________________________________________________|

The shell will attempt to launch all other commands using the exec function.

