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

char *get_dir();
void print_dir();
void change_dir(char *newdir);
void list_dir();
void clear();

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

  if (strcmp(args[0], "cd") == 0) {
    change_dir(args[1]);
  }
  if (strcmp(args[0], "clear") == 0) {
    clear();
  }
  if (strcmp(args[0], "ls") == 0) {
    list_dir();
  }
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
  printf(GREEN  "%s->" RESET, cwd);
}

//change the current directory
void change_dir(char *newdir){
  if(chdir(newdir)){
    puts("Error, directory not found");
  }
}

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
}

void piping(){

}

void redirect(){

}

int main(){
  //test();
  while (1){
  print_dir();
  char *input = malloc(sizeof(char)*BUFF);
  get_input(input);
  //printf("%s \n", input);
  char *args[BUFF];
  char input1[] = "the quick brown Fox";
  parse_input(input, args);
  for (int i = 0; i < MAX_ARGS; i++){
    if (args[i] == NULL)
      break;
    //printf("%s\n", args[i]);
  }
  process_input(input, args);
  free(input);
}


}
