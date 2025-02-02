#ifndef MAIN_H
#define MAIN_H

#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define INTERNAL_CMD 0
#define EXTERNAL_CMD 1

#define ENDS            2
#define STDIN		0
#define STDOUT	    	1
#define FORK_SUCCESS	0
#define FORK_FAILURE   -1

#define SUCCESS  0
#define FAILURE -1

#define MAX_OUTPUT_SIZE 50
#define MAX_ARGS 20
#define MIN_ARGUMENTS 3

typedef struct node
{
    int pid;
    char *input;
    struct node *next;
}Slist;

int check_command_type(char *input);
int execute_external_command(char *input);
int execute_internal_command(char *input);
int add_pid(Slist **head,int pid,const char *input);
int delete_last(Slist **head);
void print_list(Slist *head);
int check_pipe_character(char *input);
void parse_input(char *input, int *argc, char *argv[]);
void Validate_Arguments(int argc,char *argv[]);
void pipe_function(int argc, char *argv[]);
void bg(int pid_resume,char *process);
void fg(int pid_resume, char *process);

#endif

