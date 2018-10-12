#include<dirent.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/wait.h>

#include<readline/readline.h>
#include<readline/history.h>

#define FALSE 0
#define TRUE 1
#define BUFF 1024
#define MAX_ARGS 20

/*-----------------
Output Color Codes
-------------------*/
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

/*-----------------
Function Prototypes
-------------------*/
void parse_input(char *input, char *args[MAX_ARGS]);
void process_input(char *args[MAX_ARGS]);
void check_IO(char *args[MAX_ARGS]);
void check_background(char *args[MAX_ARGS]);
void check_pipes(char *args[MAX_ARGS]);
char *get_dir();
void print_dir();
void change_dir(char *newdir);
void list_dir();
void clear();
void echo();
void escape();
void external_prog(char **args);
void help();
void pause_cmd();

/*-----------------
Global Variables
-------------------*/

//for background execution
int background;
int status;

//for pipes
int piped;
char **args2;

//for input/output redirection
int input_redir;
int output_redir;
int append_redir;

//file names for i/o redirection
char *input_file;
char *output_file;

/*-----------------
Input Processing
-------------------*/

//breaks the input up into individual commands
void parse_input(char *input, char *args[MAX_ARGS]){

  args[0] = strtok(input, " \n\t");
  for (int i = 1; i < MAX_ARGS-1; i++){
    args[i] = strtok(NULL, " \n\t");
    if (args[i] == NULL)
      return;
  }
}


//processes the input and execute the desired commands
void process_input(char *args[MAX_ARGS]){
  //change directory command
  if (!strcmp(args[0], "cd") || !strcmp(args[0], "chdir")) {
    change_dir(args[1]);
  }

  //clear command
  else if (!strcmp(args[0], "clear") || !strcmp(args[0], "clr")) {
    clear();
  }
  //echo command
  else if (!strcmp(args[0], "echo")) {
    echo(args);
  }
  //exit command
  else if (!strcmp(args[0], "exit") || !strcmp(args[0], "quit") ) {
    escape();
  }

  //list command
  else if (!strcmp(args[0], "ls") || !strcmp(args[0], "dir")) {
    list_dir();
  }
  //pause 
  else if (!strcmp(args[0], "pause")) {
    pause_cmd();
  }
  //else run external program
  else {
    external_prog(args);
  }
}

//check for I/O redirection commands in input
void check_IO(char **args){
  //reset global variables
  input_redir = FALSE;
  output_redir = FALSE;
  append_redir = FALSE;

  //used to move around args
  char **temp = args;
  //loop through args untill empty or I/O redirection found
  while (*args != NULL){

    //if output redirection ">"
    if (!strcmp(args[i], ">")){
      puts("Output Redirection");
      output_redir = TRUE;
      output_file = args[i+1];
    }

    //if output append ">>"
    if(!strcmp(args[i], ">>")){
      puts("Append");
      append_redir = TRUE;
      output_file = args[i+1];
    }

    //if input redirection "<"
    if (!strcmp(args[i], "<")){
      puts("Input Redirection");
      output_redir = TRUE;
      input_file = args[i+1];
    }
  i++;
  }
}

//also checks for background execution command in input "&"
void check_background(char *args[MAX_ARGS]){
  //reset global variable to default state
  background = FALSE;

  //loop through args until "&" is found, or end of args
  int i = 0;
  while (args[i] != NULL){
    //if background char is found
    if (strcmp(args[i], "&") == 0){
      background = TRUE ;
      args[i] = NULL;
      puts("Background execution");
      break;
    }
    i++;
  }
}
//check for any piping commands
void check_pipes(char *args[MAX_ARGS]){
  //reset piped value
  piped = FALSE;
  args2 = args;

  //loop until pipe command "|" or end of args found
  while (*args2 != NULL){
    //if pipe command found
    if (strcmp(*args2, "|") == 0){
      //set piped to true
      piped = TRUE;
      //set "|" to null, seperates args and args2
      *args2 = NULL;
      //move args2 to next argument
      args2++;
      //exit function
      return;
    }
    //next arg
    args2++;
  }  


}
/*-----------------
Helper Functions
-------------------*/


//returns current directory
char *get_dir(){
  //holds string containing directory
  char cwd[BUFF];
  //copy current directory into string
  getcwd(cwd, sizeof(cwd));
  //get user's login
  char *login = getlogin();
  //used for formating
  char *temp1 = malloc(sizeof(char)* 2 * BUFF);
  char *temp2 = malloc(sizeof(char)*BUFF);
  //add color to strings
  sprintf(temp1, GREEN "%s:" RESET , login);
  sprintf(temp2, BLUE "%s>" RESET, cwd);
  //combine strings
  strcat(temp1, temp2);
  //return string
  return temp1;
}

//print current directory
void print_dir(){
  //char *login = getlogin();
  //char cwd[BUFF];
  //getcwd(cwd, sizeof(cwd));
  //printf(BLUE "%s:" RESET, login);
  //printf(GREEN "%s" RESET, cwd);
}

//change the current directory
void change_dir(char *newdir){
  //change current directory to input string
  if(chdir(newdir)){
    //if change_dir() failed
    puts("Error, directory not found");
  }
}

/*-----------------
Built-In commands
(cd, clr, ls, ect.)
-------------------*/

//list contentents of the directory
void list_dir(){
  char *temp = NULL;
  //holds size
  int size = 2;
  //holds all elements in dir as a string
  char *buffer = malloc(sizeof(char)*size);
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d){
    while ((dir = readdir(d)) != NULL){
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
}

//clears the terminal
void clear(){
  printf("\033[H\033[J");
}

//returns the input as a string
void echo(char **args){
  //skip "echo" part of command
  args++;
  
  //make sure there is text to output
  if (args!= NULL){
    //print first arg
    printf("%s", *args);
    //move to next arg
    args++;

    //loop until end of args
    while (*args != NULL){
      //print current arg
      printf(" %s", *args);
      //move to next arg
      args++;
    }
  }
  //new line
  puts("");
}

//exit the program
void escape(){
  exit(0);
}

//list environment variable
void environ(){
  

}

//handles execution of external programs
void external_prog(char **args){
  //get the main command
  char *temp = *args;
  //move to rest of args
  int status;
  //fork
  pid_t pid = fork();

  if (pid < 0){
    //error if failed
    puts("Error: fork failed");
    return;
  }
  //if child
  else if (pid == 0){
    //try to run command
    if (execvp(args[0], args) < 0){
      //error message if failed
      puts("Error: Command not recognised");
    }
    //child exits
    exit(0);
  }
  //else parent
  else{
    //if background execution not enabled
    if (background != TRUE){
      //wait for child to finish
      waitpid(pid, &status, 0);
    }
    return;
  }
}

//displays a list of commands
void help(){
  puts("Shell commands:");
}

//pauses the terminal until the enter key is pressed
void pause_cmd(){
  char *temp = readline("Please press enter:");
  free (temp);
}

void test(){
  //testing clear
  puts("Blah blag b\nlah lalala You should\n't \tsee\nany of \t\t\t\tthis\n stuff");
  clear();

  //testing get_dir, print_dir, and change_dir
  printf("%s->\n", get_dir());
  print_dir();
  change_dir("..");
  printf("%s->\n", get_dir());
  print_dir();
  change_dir("./MyShell");
  printf("%s->\n", get_dir());
  print_dir();

  char *args[BUFF];
  char input1[] = "the quick & brown > Fox";
  parse_input(input1, args);
  for (int i = 0; i < MAX_ARGS; i++){
    if (args[i] == NULL)
      break;
    printf("%s\n", args[i]);
  }
  check_IO(args);
  check_background(args);

  while(1){
    char *input = readline("->");
    printf("%s\n", input);
    free(input);
  }

  exit(0);
}



void piping(char **args){
  //pipe file descriptors
  int pfds[2];

  //create pipe
  if ( pipe(pfds) == 0 ) {
    //fork 
    pid_t pid = fork();
    //if fork failed
    if (pid < 0){
      puts("Error: Fork failed");
      exit(1);
    }
    //else if child
    else if ( pid == 0 ) {

      // close stdout
      close(1);
      //use pipe's write end as stdout
      dup2( pfds[1], 1 );
      //close read end of pipe
      close( pfds[0] );
      //execute command
      process_input(args);
      //kill child
      exit(0);
    }
    //else parent
    else {
      //close stdin
      close(0);
      //use pipe's read end as stdin
      dup2( pfds[0], 0 );
      //close write end of pipe
      close( pfds[1] );
      //execute  command
      process_input(args2);
      //kill parent
      exit(0);
    }
  }
}


void redirect(char **args){
  //if input redirection
  if (input_redir == TRUE){
    //open input file
    int in = open(input_file,O_RDONLY);
    //replace stdin with input file
    dup2(in,STDIN_FILENO);
    //close file
    close(in);
  }

  //if output redirection
  if (output_redir == TRUE){
    //open output file
    int out = open(output_file,O_WRONLY|O_CREAT,0666); // Should also be symbolic values for access rights
    //replace stdout with output file
    dup2(out,STDOUT_FILENO);
    //close output file
    close(out);
    //execute args
  }

  //if appending output redirection
  else if (append_redir == TRUE){
    //open output file in append mode
    int out = open(output_file, O_WRONLY|O_APPEND|O_CREAT,0666); // Should also be symbolic values for access rights
    //replace stdout with output file
    dup2(out,STDOUT_FILENO);
    //close output file
    close(out);
    //execute args

  }
  //run commands
  process_input(args);
}

int main(){
  //test();
  while (TRUE){
    //holds input
    char *input;
    char *args[MAX_ARGS];
    //print out terminal promt;
    //get prompt string
    char *prompt = get_dir();
    //get input
    input = readline(prompt);
    add_history(input);
    //parse the input
    parse_input(input, args);
    //check for IO redirection
    check_IO(args);
    //check for background execution
    check_background(args);
    //check for pipe commands
    check_pipes(args);
    
    //if pipe command was detected
    if (piped == TRUE){
      //fork
      pid_t pipe_pid = fork();
      //if fork failed
      if (pipe_pid < 0){
        puts("fork failed");
        exit(0);
      }
      //if child
      else if (pipe_pid == 0){
        //run piped commands
        piping(args);
      } 
      //else parent
      else{
        //wait for child to finish
        waitpid(pipe_pid, &status, 0);
      }
    }//end if

    //if I/O redirection was found
    else if (input_redir == TRUE || output_redir == TRUE || append_redir == TRUE){
      //fork
      pid_t io_pid = fork();
      //if fork failed
      if (io_pid < 0){
        puts("fork failed");
        exit(0);
      }
      //if child
      else if (io_pid == 0){
        //run piped commands
        redirect(args);
        //kill child process
        exit(0);
      } 
      //else parent
      else{
        //wait for child to finish
        waitpid(io_pid, &status, 0);
      }
    }
    //else no pipe command
    else
      //just run args
      process_input(args);
    //cleanup
    free(input);
    free(prompt);
  }
}
