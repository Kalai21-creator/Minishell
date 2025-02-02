#include "main.h"


int check_pipe_character(char *input)
{
    char *pipe_pos = strchr(input, '|');

        if(pipe_pos != NULL)
        {
           return 1;
        }
        else
        {
            return 0;
        }
}


void parse_input(char *input, int *argc, char *argv[])
{
    char *token;
    int count = 0;

    token = strtok(input, " \t\n\r");

    while(token != NULL && count < MAX_ARGS - 1)
    {
        argv[count++] = token;
        token = strtok(NULL," \t\n\r");
    }

    argv[count] = NULL;
    *argc = count;
}


void Validate_Arguments(int argc,char *argv[])
{
	// Printing An Error if argc is less than MIN_CLA
	if ( argc < MIN_ARGUMENTS )
	{
		printf("ERROR : Insufficient Arguements!\n");
		printf("USAGE : Command1 <options> '|' Command2 <options> '|' ... Commandn <options>\n");

	}

	// Printing An Error if First & Last Commands are Missing or Given as Pipe "|"
	else if ( !strcmp(argv[0],"|") && !strcmp(argv[argc - 1],"|") )
	{

		printf("ERROR : Invalid Arguements\n");
		printf("USAGE : %s Command1 <options> '|' Command2 <options> '|' ... Commandn <options>\n",argv[1]);

	}

}


//create Pipes Function

void pipe_function(int argc, char *argv[])
{
     char command[MAX_OUTPUT_SIZE] = "";
    for (int i = 0; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }


    FILE *fp;
    char output[MAX_OUTPUT_SIZE];

    // Open command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Read output from the command
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    // Close the pipe
    pclose(fp);
}

