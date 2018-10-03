# build an executable named myshell
MyShell: myshell.c
	gcc -o myshell myshell.c -lreadline
