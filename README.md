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
| pause          | Pauses the shell until the enter key is pressed.                      |
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

void check_pipes(char **args)
    purpose: loops through args looping for a pipe command "|". If found, it sets that arg to NULL,
        sets the piped flag to TRUE, and sets the next arg as the start of args2.

void piping(char **args)
    purpose: forks, then uses dupe2 to pipe the output from the child into the input of the parent.
        the child executes args while the parent uses the global variable args2. Both exit on finish,
        so use another fork before calling.

## Batch and Scripts

void batch_commands(char **args) 
    purpose: works like the main shell_loop(), but focuses on one-off commmands instead of an endless loop.
        checks for things like redirection and piping, then executes the commands

int check_script(char *arg)
    purpose: Checks a string to see if it ends in ".sh". Returns true if it does, or false otherwise.

void run_script(char *arg)
    purpose: Takes an arg that ends in ".sh" and attempts to open it. If successfull, it runs all commands 
        in the script file line by line until it reaches the end of the file. 

## External Execution

void external_prog(char **args)
    purpose: forks, and then has the child process attempts to run the args through the system's execvp() function, 
        then exits. The parent process waits until the child process finishes, unless background exection is enabled.

## Helper Functions

char *get_prompt()
    purpose: Uses getcwd() and getlogin() to retrieve user info and the current directory. It combines them into a single
        prompt for readline, along with special color codes for the terminal.

char *get_dir()
    purpose: Like get_prompt(), but skips the color codes and only gets the current directory.

## Internal Commands

void change_dir(char *newdir)
    purpose: takes and string and uses chdir() to try to change the current working directory.

void list_dir(char **args)
    purpose: Lists the files in the current directory. Excludes files beggining with '.' unless args[2] = "-a"

void clear();
    purpose: Uses an escape code to clear the terminal's output.

void echo(char **args)
    purpose: Skips the first arg ("echo"), and then prints out every other arg with a space between them.

void environ();
    purpose: Displays the value of the PATH system variable.

void escape();
    purpose: Kills the current process. Used to exit the shell during regular use.

void help();
    purpose: Prints out a helpful message.

void pause_cmd();
    purpose: pauses the shell untill the enter key is presses.

## Main

void shell_loop()
    purpose: Follows an endless loop of fetch->parse->execute for user input. Input is obtained using the
        readline library, and then goes through the rest of the functions to determine what to do with it.

int main(int argc, char **argv)
    purpose: The starting point for the shell. If additional args are supplied at launch it sends them off to batch_commands().
        Otherwise, it startes the shell_loop().
