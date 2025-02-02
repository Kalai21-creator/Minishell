#include "main.h"

extern int cmd_indx,pid_resume;
extern char *process;
extern Slist *head;

int execute_internal_command(char *input)
{
    //cd,pwd,fg,bg,jobs
    //1.cd-> chdir() - pass the path
    //2.pwd-> get_current_dir_name()

    switch(cmd_indx)
    {
        case 0: //cd
            if(chdir(input + 3) == -1)
              return errno;
            break;

       case 1: //pwd
            printf("%s\n",get_current_dir_name());
            break;

       case 2: //exit
            exit(EXIT_SUCCESS);
            break;

       case 3: //fg
            delete_last(&head);
            fg(pid_resume,process);
            break;

       case 4: //bg
            delete_last(&head);
            bg(pid_resume,process);
            break;

       case 5: //jobs
            print_list(head);
            break;
    }
}

