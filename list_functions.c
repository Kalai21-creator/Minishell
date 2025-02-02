#include "main.h"

int pid_resume = 0;
char *process = NULL;

int add_pid(Slist **head,int pid,const char *input)
{
    
    Slist *new = malloc(sizeof(Slist));

    if(new == NULL)
    {
        return FAILURE;
    }

    new-> input = strdup(input);
    new-> pid = pid;
    new-> next = NULL;

    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    else
    {
        Slist *temp = *head;
        while(temp-> next != NULL)
        {
            temp =  temp-> next;
        }
        temp-> next = new;
        return SUCCESS;
    }
}



int delete_last(Slist **head)
{

   if(*head == NULL)
   {
       pid_resume = 0;
       return FAILURE;
   }
  
   else if((*head)->next == NULL)
   {
       pid_resume = (*head)-> pid;
       process = (*head) -> input;
        free(*head);
        *head = NULL;
        return SUCCESS;
   }
   else if((*head)-> next != NULL)
   {
       Slist *temp = *head;
       Slist *prev = *head;
       while(temp-> next != NULL)
       {
           prev = temp;
           temp = temp-> next;
       }
       pid_resume = temp->pid;
       process = temp -> input;
       
       free(temp);
       prev-> next = NULL;
       return SUCCESS;
   }
}


void print_list(Slist *head)
{
    int i = 1;

	if (head != NULL)
    {

        while(head)
	    {
            if(head-> next == NULL)
            {
            printf("[%d]+ stopped    process: %s          pid: %d\n",i,head->input,head->pid);
            }

            else
            {
            printf("[%d]- stopped    process: %s          pid: %d\n",i,head->input,head->pid);
            }

            head = head -> next;
            i++;
        }

      }

}

