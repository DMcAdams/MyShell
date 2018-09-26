#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
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

//function prototypes
void get_input(char *input);
void parse_input(char *input, char *args[MAX_ARGS]);
void process_input(char *input, char *args[MAX_ARGS]);
char *get_dir();
void print_dir();
void change_dir(char *newdir);
void list_dir();
void clear();
void echo();
void escape();
void help();
void wait();

//global variables
//for input/output redirection
int input;
int output;
int append;

//file names for i/o redirection
char *inputFile;
char *outputFile;

//get input from stdin, return it as a string
void get_input(char *input){
  fgets(input, BUFF-1, stdin);
}

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
  if (!strcmp(args[0], "clear") || !strcmp(args[0], "clr")) {
    clear();
  }
  //exit command
  if (!strcmp(args[0], "exit") || !strcmp(args[0], "quit") ) {
    escape();
  }
  //list command
  if (!strcmp(args[0], "ls") || !strcmp(args[0], "dir")) {
    list_dir();
  }

}


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
  printf(GREEN  "%s->" RESET, cwd);
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
//check for I/O redirection commands in input
void check_IO(char *args[MAX_ARGS]){
  //reset global variables
  input = 0;
  output = 0;
  append = 0;

  //loop through args untill empty or I/O redirection found
  int i = 0;
  while (args[i] != NULL){
    //if output redirection
    if (!strcmp(args[i], ">")){
      puts("Output Redirection");
    }
    //if input redirection
    if (!strcmp(args[i], "<")){
      puts("Input Redirection");
    }
    //if output append
    if(!strcmp(args[i], ">>")){
      puts("Append");
    }
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

//displays a list of commands
void help(){
  puts("Shell commands:");
}

//pauses the terminal until the enter key is pressed
void wait(){

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
  char input1[] = "the quick brown Fox";
  parse_input(input1, args);
  for (int i = 0; i < MAX_ARGS; i++){
    if (args[i] == NULL)
      break;
    printf("%s\n", args[i]);
  }
}

void piping(){

}

void redirect(){

}

int main(){
  //test();
  while (1){
    print_dir();
    char input[BUFF]; // = malloc(sizeof(char)*BUFF);
    char *args[MAX_ARGS];
    get_input(input);
    parse_input(input, args);
    process_input(input, args);
  }


}
