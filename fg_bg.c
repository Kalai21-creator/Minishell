#include "main.h"

int k = 1;

void fg(int pid_resume, char *process)
{
    int status;
 
          if(pid_resume > 0)
          {
               kill(pid_resume,SIGCONT);
 
               int parent_pid = waitpid(pid_resume,&status,0);
 
               if (WIFEXITED(status))
               {
                  printf("%s\n",process);
                  process = NULL;
               }
           }
 
           else
           {
              printf("fg: current: no such job\n");
           }
}


void bg(int pid_resume,char *process)
{
    if(pid_resume > 0)
    {
        if (kill(pid_resume, SIGCONT) == -1) {
                    perror("kill");
                }
        printf("[%d]+ %s &\n",k,process);
    }

    else
    {
        printf("bg: current: no such job\n");
    }
}


