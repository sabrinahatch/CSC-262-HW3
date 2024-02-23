//----------------------------
// Name: Sabrina Hatch
// Date: Spring 2024
// Class: Operating Systems
// Assignment: Smart Shell
//----------------------------

#include <string.h>    /* for strcpy and strtok */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


/* Include other header files that are needed */

#define MAX_ARGV  10 /* maximum number of command tokens */
#define MAX_CMD   80 /* maximum length of command */
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

//add default user and pass

#define DEFAULT_USER "master_hacker"
#define DEFAULT_PASS "i<3csc262"

// "bells and whistles" added: made the prompts a different color than user input
#define ANSI_COLOR_RED "\x1b[31m" 
#define ANSI_COLOR_RESET "\x1b[0m"

// "bells and whistles" added: created an authentication so that only someone with the right user and password can use the smartshell
int authenticate_user()
{
	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];

	printf(ANSI_COLOR_RED "Enter username: " ANSI_COLOR_RESET);
	fgets(username, sizeof(username), stdin);
	username[strcspn(username, "\n")] = '\0';


	printf(ANSI_COLOR_RED "Enter password: " ANSI_COLOR_RESET);
	fgets(password, sizeof(password), stdin);
	password[strcspn(password, "\n")] = '\0';


	if (strcmp(username, DEFAULT_USER )== 0 && strcmp(password, DEFAULT_PASS)==0)
	{
		return 1; //passed
	}
	else
	{
		return 0; //failed
	}

	
}


void tokenize_cmd (char * cmd, int max, char * argv[])
/* Input:  cmd is the command to be tokenized
 *         max is the maximum number of tokens allowed  
 * Output: argv is the array of tokens (command arguments) 
 */
{
    int num_args = 0;           /* number of arguments (tokens) in cmd */

    if(cmd == NULL) return;     /* nothing to do */

    /* Tokenize the command */
    argv[0] = strtok(cmd, " \n");
    
    while((num_args < max) && (argv[num_args] != NULL))
    {
       num_args++;
       argv[num_args] = strtok(NULL, " \n");
    }
}

void execute_cmd(char * cmd)
{
    char * argv[MAX_ARGV];  /* array of command arguments*/
    char cmd_copy[MAX_CMD]; /* buffer to store local copy of cmd*/

    /* Make a local copy of the command */
    if(cmd == NULL) return; /* nothing to do */
    strcpy(cmd_copy, cmd);

    /* Tokenize the command */
    tokenize_cmd(cmd_copy, MAX_ARGV, argv);

    /* Fork a child to execute the command 
     *   - if execvp fails, print an error message and exit
     */
    /* Parent waits for child to finish execution */
     int ret;
        ret = fork();

        wait(NULL);

        if(ret == 0)
        {
                int ret2 = execvp(cmd_copy, argv);
                if(ret2 == -1)
                {
                        perror("execvp failed");
                        exit(EXIT_FAILURE);
                }
        }
}


int main()
{

	// create char arr to hold user input
	char input[100];
    //  execute_cmd("ps -f");

	// logic/loop for user authentication
     while(1)
     {
	     if(authenticate_user())
	     {
	     	printf(ANSI_COLOR_RED "Login successful!\n" ANSI_COLOR_RESET);
	     	break;
	     }
	     else
	     {
	     	printf(ANSI_COLOR_RED "Login failed. Try again.\n" ANSI_COLOR_RESET);
	     }
     }


	// main loop for taking in commands and executing them
     while(1)
     {
     printf(ANSI_COLOR_RED "myshell$ " ANSI_COLOR_RESET);

     if(fgets(input, sizeof(input), stdin)== NULL)
     {
     	perror(ANSI_COLOR_RED "fgets failed" ANSI_COLOR_RESET);
     	exit(EXIT_FAILURE);
     }

     input[strcspn(input, "\n")] = '\0';
     
	     if (strcmp(input, "quit")==0)
	     {
	     	break;
	     }
		 else if (strcmp(input, "mem")==0)
		 {
		 	execute_cmd("free -m -t");
		 }

		 else if (strcmp(input, "disk") ==0)
		 {
		 	execute_cmd("df -h /dev/sdal1");
		 }
		 else
		 {
		 	execute_cmd(input);
		 }
	   
	     	
	 }
	 
    
     return 0;
}

