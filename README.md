  ***SIMPLE SHELL PROJECT***
The goal of this project is to implement a pseudo version of the Unix CLI. When compiled, the local shell interface can take UNIX commands and execute them in similar ways to the default shell.

The main.h file holds all the program's macros and functions.

The main function in the 0-main.c file is the program's entry point.

        ----VARIABLES----
Prompt variable pointer: Holds the string prompt when the terminal is initialised.

buffer pointer: This char pointer holds the command gotten from STDIN (command typed).

buffersize: This variable if tyoe size_t holds the size of the command from STDIN (length of comman typed).

arg[]: Char array used to hold the tokenised arguments. The tokensed arguments are the space seprated arguments (delimiter);

delim:

path: Path pointer variable holds the entire path of the typed executable file.

stringVariable: This variable of type ssize_t is the status of the getline funtction used to get data from STDIN.

Child_ID: This variable of type pid_t hold the child process ID after the fork function is called.

executable: This holds the return status of the execve function. 0 if successful and -1 if unsuccessful.

path_duplicate: This char pointer holds the duplicate of the of the path created with strdup. We make use of a duplicate so as not to alter path string which could lead to errors.

pathToken: This char pointer holds the

delim(":"):

handle_path: This creates memory for the argument and its file path and 2 additional bytes for "/" and "\0"( end of file argument).

buffer:

env: array of environmental variables.

          ----FUNCTIONS-----
_putchar(): This function writes a charatcer to STDOUT

_putstring: This function writes a character sequnces to STDOUT *_getpath: This gets the location of a file based on inputed argument and the argument's path and passes it to to execve for execution.

_builtins: This contains standard built in c commands.

location:

      ----SYSTEM FUNCTIONS-----
isatty(): Only runs if input in from CLI.

getline(): Used to accept user input from CLI.

free(): Used to free up allocated memory.

exit(): Used to quit a program. 0 means successful, non zero if unsuccessful.

strtok(): Used to tokenise a sequnce of characters using a specified delimiter.

fork(): Used to create a child process from a parent process.

execve(): Used to execute UNIX CLI arguments

perror(): Returns the specified error

wait(): waits for the parent function before implementing the child process

strcmp(): compares to strings

getenv(): This helps us get environment variables. It takes a char pointer and returns the value if there's a match else returns NULL.

malloc(): Allocates memory

strlen(): Returns the length of a charcter sequence.

strcpy(): Used to copy content of one variable to another.

access():

In summary, we use the while(1) (while true) to keep the prompt running after every command execution. isatty() helps limit the program to inputs from CLI only. getline() collects data from the CLI. If the argument passed is "ctrl+D", it sets getline() to -1 and exits the program after freeing up the allocated memory for the arguments.

handle_path() which is assigned to path vaaiable gets the cli typed argument

To implement the End Of File (close: ctrl+D) command we made use of the return value of getline (-1). We free buffer to prevent leaks and exit.
