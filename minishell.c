#include "main.h"

char prompt[50] = "minishell$";
int i = 1;

extern char *process;
char input[50];
int exit_status = 0;
extern int pid;
int argc;
char *argv[MAX_ARGS];

Slist *head = NULL;

void signal_handler(int signum)
{
    //check is there any foreground process running
    if(pid > 0)
    {
        if(signum == SIGINT)
        {
            kill(pid,SIGINT);
            exit_status = 128 + SIGINT;    
        }

        else if(signum == SIGTSTP)
        {
          add_pid(&head,pid,input);
           
            //send SIGTSTP signal to the child process
            kill(pid,SIGTSTP); 
            exit_status = 128 + SIGTSTP;
        } 
    }
    printf("\n");
}

void sigchld_handler(int signum) {
    int status;
    pid_t pid;

   while( pid = waitpid(-1, &status, WNOHANG) > 0)
    {
        if (WIFEXITED(status)) {
                      printf("\n[%d]+ Done\t %s\n",i,process);
                      printf("\033[1;32m%s \033[0m",prompt);
                      fflush(stdout);
                      
        } 
    }
}

int main()
{
    int ret = 0;
    char *cwd = get_current_dir_name();

    //SIGINT, SIGTSTP

    struct sigaction act,oldact;
    act.sa_handler = signal_handler;
    sigaction(SIGINT,&act,&oldact);
    sigaction(SIGTSTP,&act,&oldact);


    while(1)
    {
        printf("\033[1;32m%s \033[0m",prompt);
        fgets(input,50,stdin);

        input[strlen(input) -1] = '\0';

        if(*input == '\0')
        {
            continue;
        }

        else if(check_pipe_character(input) == 1)
        {
              parse_input(input,&argc,argv);
              Validate_Arguments(argc,argv);

              pipe_function(argc,argv);
        }

        else if(!(strcmp(input, "echo $?")))
        {
            printf("%d\n",exit_status);
            exit_status = 0;
        }
          
        else if(!(strcmp(input, "echo $$")))
        {
            printf("%d\n",getpid());
        }

        else if(!(strcmp(input, "echo $SHELL")))
        {
            printf("%s\n",cwd); //current directory path
        }

        else if(strncmp("PS1=", input,4) == 0) 
        {
              //copy the prompt to the prompt array
              strcpy(prompt,input + 4);
        }

        else if( (ret = check_command_type(input)) == EXTERNAL_CMD)
        {
            exit_status = execute_external_command(input);
        }
        
        else if(ret  == INTERNAL_CMD)
        {
            act.sa_handler = sigchld_handler;
            sigemptyset(&act.sa_mask);
            act.sa_flags = SA_RESTART;
            sigaction(SIGCHLD,&act,&oldact);

            exit_status = execute_internal_command(input);
        }

        memset(input,0,50);
    }      
}

