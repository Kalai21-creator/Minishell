#include "main.h"

char *internal_cmd[] = {"cd","pwd","exit","fg","bg","jobs",NULL};
int cmd_indx;

int check_command_type(char *input)
{
    //INTERNAL_CMD
    //EXTERNAL_CMD

    int j;
    char cmd[strlen(input) + 1];

    for(j = 0; input[j] != ' ' && input[j] != '\0'; j++)
    {
        cmd[j] = input[j];
    }
    cmd[j] = '\0';



    for( int i = 0; internal_cmd[i] != NULL; i++)
    {
        if(strcmp(cmd,internal_cmd[i]) == 0)
        {
            cmd_indx = i;
            return INTERNAL_CMD;
        }
    }

    return EXTERNAL_CMD;
}






