#include "main.h"

int pid = 0,j = 1;
extern Slist *head;

void get_command(char *input, char *cmd[])
{
    int i = 0;
    char *token =  strtok(input , " ");
    while( token != NULL)
    {
        cmd[i] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(cmd[i], token);
        token = strtok(NULL, " ");
        i++;
    }
}    


int execute_external_command(char *input)
{
    pid = fork();

    if(pid == 0)
    {
       char *cmd[10] = {NULL};
       get_command(input, cmd);

       // int execvp(const char* filename, const char *argv[]);
        if(execvp(cmd[0],cmd) == -1)
        {
          printf("Command not found\n");
          exit(EXIT_FAILURE);
        }
     }

     else
     {
         //parent process

         int status = 0, exit_status = 0;

     
         while(waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1)
         {
             if(errno == EINTR)
             {
                 continue;
             }

             else 
             {
                 perror("waitpid");
                 exit(EXIT_FAILURE);
             }
         }

          if(WIFEXITED(status))
          {
             exit_status = WEXITSTATUS(status);
             //Normal termination
          //   printf("The child %d terminated normally with code %d\n",pid,exit_status);
             return exit_status;
          }

          else if(WIFSIGNALED(status))
          {
             exit_status = WTERMSIG(status);
          //   printf("The child %d terminated by the signal %d\n",pid,exit_status);
             return 128 + exit_status;
          }

          if(WIFSTOPPED(status))
          {
              exit_status = WSTOPSIG(status);
        
              printf("[%d]+     stopped           %s\n",j,input);
              j++;
              return 128 + exit_status;

          }

          else
          {
             printf("The child %d terminated abnormally\n",pid);
          }
       
      }
}


