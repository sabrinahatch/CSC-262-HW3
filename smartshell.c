//----------------------------
// Name: Sabrina Hatch
// Date: Spring 2024
// Class: Operating Systems
// Assignment: Smart Shell
//----------------------------

#include <string.h>    /* for strcpy and strtok */
#include <unistd.h>
#include <stdlib.h>


/* Include other header files that are needed */

#define MAX_ARGV  10 /* maximum number of command tokens */
#define MAX_CMD   80 /* maximum length of command */


/*THIS WHOLE CODE CHUNK TAKES CARE OF STEP 1*/
void tokenize_cmd (char * cmd, int max, char * argv[])
/* Input:  cmd is the command to be tokenized
 *         max is the maximum number of tokens allowed  
 * Output: argv is the array of tokens (command arguments) 
 */
{
    int num_args = 0;           /* number of arguments (tokens) in cmd */

	// takes care of 1.1
    if(cmd == NULL) return;     /* nothing to do */

    /* Tokenize the command */
    // this takes care of 1.2
    argv[0] = strtok(cmd, " \n");
    // the above line stores a pointer to an array of chars which is
    // the command to be executed
    
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
}

int main()
{

	// create char arr to hold user input
	char input[100];
    /* Step 1:
     *   Add calls to execute_cmd here to test it out. 
     *   Example: execute_cmd("ps -f");
     *   ... other commands you wish to try here ...
     */

    /*
     * Step 2: 
     *   Add code for your smart shell
     *   Read and process commands in an infinite loop
     *   Exit when the user types "quit" 
     */

     while(1)
     {
     prinf("myshell$ ");
     scanf("%s", input); //reads a single word as input
	     //check to see if the user wants to exit
	     if (strcmp(input, "exit")==0)
	     {
	     	break;
	     }

	     //here i need to process the input

		 // satisfying 2.4
		 if (strcmp(input), "mem")==0)
		 {
		 	
		 }
	   
	     	
	 }
	    
    
     return 0;
}