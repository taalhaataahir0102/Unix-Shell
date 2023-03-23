/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LINE 80 /* 80 chars per line, per command */


void trim(char * str)
{
    
    int index = 0;
    int i = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }
    if(index != 0)
    {
        while(str[i + index] != '\0')
        {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0';
    }
    
    int index1 = -1;
    int i1 = 0;
    while(str[i1] != '\0')
    {
        if(str[i1] != ' ' && str[i1] != '\t' && str[i1] != '\n')
        {
            index1= i1;
        }
        i1++;
    }
    
}


struct Node
{
	char data[80];
	struct Node *next;
};
struct Node *last = NULL;
void insertAtFront(char d[])
{
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    if (last == NULL){
        memcpy(temp->data, d, sizeof temp->data);
        temp->next = temp;
        last = temp;
    }
    else{
        memcpy(temp->data, d, sizeof temp->data);
        temp->next = last->next;
        last->next = temp;
    }
}

void viewList()
{
    if (last == NULL)
        printf("No History\n");
    else {
        struct Node* temp;
        temp = last->next;
        do {
            printf("%s\n", temp->data);
            temp = temp->next;
        } while (temp != last->next);
    }
}

int countNodes()
{
    int result = 0;
    struct Node* temp;
    if(last == NULL){
    	return result;
    }
    else{
    	temp = last->next;
    	do {
            result++;
            temp = temp->next;
           }while(temp != last->next);
    }
    return result;
}

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
    int should_run = 1;
    char input_string[80];
    char *token;
    char *temp_args[MAX_LINE / 2 + 1];
    char firstfour[80];

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);
        
        fgets(input_string,MAX_LINE/2+1,stdin);
        input_string[strlen(input_string)-1]='\0';
        if (strlen(input_string) > 4){
        	memcpy(firstfour, input_string , 4);
        }
        
        if(strlen(input_string) > 4 && !strcmp("hist", firstfour)){
        	int number;
        	char *t;
        	t = strtok(input_string,"-");
        	t = strtok(NULL,"-");
        	number = atoi(t);
        	if (number > countNodes() || number <1){
        		printf("No History found\n");
        	}
        	else{
        		struct Node* temp;
        		temp = last;
        		for(int i=0; i<number; i++){
        			temp = temp->next;
        		}
        		printf("%s\n",temp->data);
        		memcpy(input_string, temp->data, sizeof input_string);
        	}
        		
        }
        
        else if (strlen(input_string) == 4 && !strcmp("hist", input_string)){
        	viewList();
        }
        
        else if (!strcmp("!!", input_string)){
        	memcpy(input_string, last->next->data, sizeof input_string);
        }
        
        else{
        	insertAtFront(input_string);
        }
        
        token = strtok(input_string,"&");
	int index = 0;
        while(token != NULL)
        {
                temp_args[index] = token;
                token = strtok(NULL,"&");
                index++;
        }
        
        for(int i=0; i<index; i++){
        	trim(temp_args[i]);
        	char ch = '\0';
        	strncat(temp_args[i], &ch, 1);
        	token = strtok(temp_args[i]," ");
        	int new_index = 0;
        	while(token != NULL)
        	{
                	args[new_index] = token;
                	token = strtok(NULL," ");
                	new_index++;
        	}
        	args[new_index] = NULL;
        	int rc = fork();
        	if (rc < 0){
         		printf("fork failed\n");
        	}
        	else if (rc == 0){
        		execvp(args[0],args);
        	}
        	else{
        		wait(NULL);
        	}
        } 
    }
    
    return 0;
}
