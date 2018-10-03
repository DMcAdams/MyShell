#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<readline/readline.h>

#define FALSE 0
#define TRUE 1
#define BUFF 1024
#define MAX_ARGS 20

//color codes for output
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

/*-----------------
Function Prototypes
-------------------*/
void parse_input(char *input, char *args[MAX_ARGS]);
void process_input(char *input, char *args[MAX_ARGS]);
void check_IO(char *args[MAX_ARGS]);
void check_background(char *args[MAX_ARGS]);
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

//for input/output redirection
int input;
int output;
int append;


//file names for i/o redirection
char *inputFile;
char *outputFile;

/*-----------------
Input Processing
-------------------*/

/*get input from stdin
char * getline(void) {

  //input buffer
  char *input = malloc(BUFF);
  //track size of input
  size_t maxlength = BUFF;
  size_t length = BUFF;
  //used to read each character
  int c;

  //loop through
  while(TRUE) {
    c = fgetc(stdin);
    //if not enough memory for buffer
    if (--length = 0){
        //reset length
        length = maxlength;
        //double max length
        maxlength *=2;
        //realloc
        realloc(input, maxlength);
    }

    //if end of input
    if(c == '\0'){
      break;
    }
    
  }

}
*/
//breaks the input up into individual commands
void parse_input(char *input, char *args[MAX_ARGS]){
  int i = 0;

  args[i] = strtok(input, " \n\t");
  while (args[i] != NULL){
    args[++i] = strtok(NULL, " \n\t");
  }

}


//processes the input and execute the desired commands
void process_input(char *input, char *args[MAX_ARGS]){
  //change directory command
  if (!strcmp(args[0], "cd") || !strcmp(args[0], "chdir")) {
    change_dir(args[1]);
  }

  //clear command
  else if (!strcmp(args[0], "clear") || !strcmp(args[0], "clr")) {
    clear();
  }

  //exit command
  else if (!strcmp(args[0], "exit") || !strcmp(args[0], "quit") ) {
    escape();
  }

  //list command
  else if (!strcmp(args[0], "ls") || !strcmp(args[0], "dir")) {
    list_dir();
  }

  //else run external program
  else {
    external_prog(args);
  }
}

//check for I/O redirection commands in input
void check_IO(char *args[MAX_ARGS]){
  //reset global variables
  input = FALSE;
  output = FALSE;
  append = FALSE;

  //loop through args untill empty or I/O redirection found
  int i = 0;
  while (args[i] != NULL){

    //if output redirection ">"
    if (!strcmp(args[i], ">")){
      puts("Output Redirection");
      output = TRUE;
      outputFile = args[i+1];
    }

    //if output append ">>"
    if(!strcmp(args[i], ">>")){
      puts("Append");
      append = TRUE;
      outputFile = args[i+1];
    }

    //if input redirection "<"
    if (!strcmp(args[i], "<")){
      puts("Input Redirection");
      output = TRUE;
      inputFile = args[i+1];
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
    if (!strcmp(args[i], "&")){
      background = 1;
      puts("Background execution");
      break;
    }
    i++;
  }
}

/*-----------------
Built-In commands
(cd, clr, ls, ect.)
-------------------*/

//returns current directory
char *get_dir(){
  //holds string containing directory
  char cwd[BUFF];
  //copy current directory into string
  getcwd(cwd, sizeof(cwd));
}

//print current directory
void print_dir(){
  char *login = getlogin();
  char cwd[BUFF];
  getcwd(cwd, sizeof(cwd));
  printf(BLUE "%s:" RESET, login);
  printf(GREEN "%s" RESET, cwd);
  //printf(" ");
}

//change the current directory
void change_dir(char *newdir){
  //change current directory to input string
  if(chdir(newdir)){
    //if change_dir() failed
    puts("Error, directory not found");
  }
}

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
void echo(){

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
  puts("a");
  //get the main command
  char *temp = *args;
  //move to rest of args
  //args++;
  pid_t pid;
  int status;

  puts("b");
  //fork
  if (pid = fork() < 0){
    //error if failed
    puts("Error: fork failed");
    return;
  }//endif
  //if child
  else if (pid == 0){
    //try to run command
    puts("cd");
    if (execvp(args[0], args) < 0){
      //error message if failed
      puts("Error: Command not recognised");
    }
  }//end elseif
  //if parent
  else{
    puts("d");
    //if background execution not enabled
    if (!background){
      while (wait(&status) != pid);
    }//end if
  } //end else
}

//displays a list of commands
void help(){
  puts("Shell commands:");
}

//pauses the terminal until the enter key is pressed
void pause_cmd(){
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



void piping(){

}

void redirect(){

}

int main(){
  //test();
  while (TRUE){
    //puts("1");
    char *input;
    print_dir();
    input = readline("$");
    //puts("2");
    //char *args[MAX_ARGS];
    //puts("3");
    //parse_input(input, args);
    //puts("4");
    //check_IO(args);
    //puts("5");
    //check_background(args);
    //puts("6");
    //process_input(input, args);
    //puts("7");
    printf("Input: %s\n", input);
    free(input);
    //args[1] = NULL;
  }
}
