#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define FALSE 0
#define TRUE 1
#define BUFF 1024

//color codes for output
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"


//get input from stdin, return it as a string
char *get_input(){

}

//breaks the input up into individual commands
char **parse_input(){

}
//processes the input and execute the desired commands
void process_input(){

}


//returns current directory
char *get_dir(){
  char cwd[BUFF];
  getcwd(cwd, sizeof(cwd));
}

//print current directory
void print_dir(){
  char *login = getlogin();
  char cwd[BUFF];
  getcwd(cwd, sizeof(cwd));
  printf(BLUE "%s:" RESET, login);
  printf(GREEN  "%s->\n" RESET, cwd);
}

//change the current directory
void change_dir(char *newdir){
  if(chdir(newdir)){
    puts("Error, directory not found");
  }
}

//clears the terminal
void clear(){
  printf("\033[H\033[J");
}

//returns the input as a string
void echo(){

}

//pauses the terminal until the enter key is pressed
void wait(){

}

//displays a list of commands
void help(){
  puts("Shell commands:");
}

//exit the program
void escape(){
  exit(0);
}
//list environment variable
void environ(){

}

int main(){
  printf("%s->\n", get_dir());
  print_dir();
  change_dir("..");
  print_dir();
  change_dir("./MyShell");
  print_dir();
  //clear();
}
