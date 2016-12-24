// Michael Moore
// Ryan Lee
//Andrew Grossane
//Jacob Porter

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
  cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
  int i = 0;
  cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
  while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
    cmdTokens[i] = strtok(NULL, " ");
  }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
  char c = getchar();
  while (getchar() != '\n');
  return c;
}

// main method - program entry point
int main()
{
  char cmd[81]; // array of chars (a string)
  char* cmdTokens[20]; // array of strings
  int count; // number of times to execute command
  int parallel; // whether to run in parallel or sequentially
  int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)

  while (TRUE) { // main shell input loop

    // begin parsing code - do not modify
    printf("clonsh> ");
    fgets(cmd, sizeof(cmd), stdin);
    if (cmd[0] == '\n') continue;
    readCmdTokens(cmd, cmdTokens);
    do {
      printf("  count> ");
      count = readChar() - '0';
    }
    while (count <= 0 || count > 9);
    printf("  [p]arallel or [s]equential> ");
    parallel = (readChar() == 'p') ? TRUE : FALSE;
    do {
      printf("  timeout> ");
      timeout = readChar() - '0';
    }while (timeout < 0 || timeout > 9);
    // end parsing code
    

    ////////////////////////////////////////////////////////
    //                                                    //
    // TODO: use cmdTokens, count, parallel, and timeout  //
    // to implement the rest of closh                     //
    //                                                    //
    // /////////////////////////////////////////////////////



    pid_t pid1;										//Declare process type
	pid_t pid[9];									//Array of 9 because that is what count can go up to
    int p, processStatus ; 								//Declare variables to use for the "for" loops


    if (parallel)
{
    for (p = 0; p<count; p++)
    	{                             							 // fork = count processes
           pid[p] = fork();                                       // save the pid and fork
           if (pid[p] == 0)
           {                                     // the process to exec the command
               printf("My process id is: %d\n", getpid() );     //Print the process id of the forked processes

             execvp(cmdTokens[0], cmdTokens);					//Executing given command
             printf("The computer can't execute %s\n", cmdTokens[0]);		//If the command is not acceptable, print a message that says so
             exit(1);
           }
         }

         if (timeout != 0)
         {										//if timeout is = 0, do nothing
           sleep(timeout);                                        // sleeps for the duration of timeout
           for (p = 0; p<count; p++)
           {
         kill(pid[p], SIGKILL);                               // kills the forked processes
           }
         }

         while ( (pid1 = waitpid(-1, &processStatus, 0)) > 0 ) {         // Wait for the children to terminate
        	 	 	 	 	 	 	 	 	 	 	 	 	 	 //(uses user value for timeout)
             printf("process %d killed\n", pid1);				//Print that the process was killed, along with its id
         }
       }
    else
    {
          for (p = 0; p<count; p++)
          {                               // for loop to go up to user variable of count
            if ( (pid1 = fork()) == 0)
            {                            // output process id and create new process
                printf("My process id is %d\n", getpid() );
              execvp(cmdTokens[0], cmdTokens);
              printf("Can't execute %s\n", cmdTokens[0]);
              exit(1);
            }
            else
            {                                                  // This is the parent
              if (timeout != 0)
              {
                sleep(timeout);
                kill(pid1, SIGKILL);                                // killing the child process
              }
              if ( (pid1 = waitpid(-1, &processStatus, 0)) > 0 ) {         // waits for the process to terminate
                printf("process %d terminated\n", pid1);
              }
            }
          }
        }
  }
}

