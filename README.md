# MyShell Program

Programmer: Darrin McAdams
Professor: Dr. J. Payton
Class: CIS 3207-10
Date: 10/17/2018

This program is an implementation of a unix-like shell. It supports basic IO redirection, piping, background execution, and .sh scripts.

built in commands:
 _________________________________________________________________________________________
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


# Functions

## INPUT HANDLER

void parse_input(char *input, char **args) 
    Purpose: uses strtok to break input into a collection of args

void process_input(char **args) 
    purpose: compares first arg to a list of known commands and executes them if found. 
        if command is not found it will send it to external_prog() to try that

## IO REDIRECTION

void check_io(char **args)
    purpose: checks args for redirection commands (>, >>, <). If one is found
        the appropriate flag (input_redir, output_redir, or append_redir) is set to 1.
        That args is then set to NULL and the next arg is then saved as either 
        input_file or output_file as needed.

void redirect(**args)
    purpose: Replaces stdin and stdout replaces with the input_file and output file as needed,
    then passes the args to process_input(), and exits when finished. Does not restore stdin or stdout,
    use fork and have a child process execute this.

## BACKGROUND EXECUTION

void check_background(char **args){
    purpose: loops through args looking for the background execution symbol "&". If found, it sets
        that arg to NULL and and sets the background flag to TRUE.

}

## Piping
    