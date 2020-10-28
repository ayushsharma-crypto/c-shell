#include "prompt.h"
#include "headers.h"
#include "builtin.h"


int prompt() 
{
    char *curr_user = (char*)malloc(100*sizeof(char));
    if((!curr_user))
    {
        printf("Memory Allocation Error\n");
        return 1;
    }
    char *curr_host = (char*)malloc(100*sizeof(char));
    if((!curr_host))
    {
        printf("Memory Allocation Error\n");
        return 1;
    }
    char *cwd = (char*)malloc(500*sizeof(char));

    if((!curr_host) || (!curr_user) || (!cwd) )
    {
        printf("Memory Allocation Error\n");
        return 1;
    }


    if(getlogin() == NULL)
    {
        curr_user = "No User";
    }
    else
    {
        curr_user = getlogin();
    }

    int is_host = gethostname(curr_host,100);
    if(is_host == -1)
    {
        curr_host = "No Host";
    }


    if(getcwd(cwd, 500)==NULL)
    {
        return 1;
    }

    int flag = 0,index =0;
    if(strlen(cwd) < strlen(HOME_DIRECTORY))
    {
        flag =1;
    }
    else
    {
        for(index=0;index < strlen(HOME_DIRECTORY);index++)
        {
            if(cwd[index]!=HOME_DIRECTORY[index])
            {
                flag =1;
                break;
            } 
        }
        
    }
    
    
    if(!flag)
    {
        if(EXIT_STAT==1)
        {
            printf("\n:')<\033[1;32m%s@%s\033[0m:\033[1;34m~%s\033[0m> ",curr_user,curr_host,cwd+index);
        }
        else if(EXIT_STAT==0)
        {
            printf("\n:'(<\033[1;32m%s@%s\033[0m:\033[1;34m~%s\033[0m> ",curr_user,curr_host,cwd+index);
        }
        else
        {
            printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m~%s\033[0m> ",curr_user,curr_host,cwd+index);
        }
        
    }
    else
    {
        // printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",curr_user,curr_host,cwd);
        if(EXIT_STAT==1)
        {
            printf("\n:')<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",curr_user,curr_host,cwd);
        }
        else if(EXIT_STAT==0)
        {
            printf("\n:'(<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",curr_user,curr_host,cwd);
        }
        else
        {
            printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",curr_user,curr_host,cwd);
        }
    }

    // free(curr_user);
    // free(curr_host);
    // free(cwd);
    return 0;
    
}


char* read_line_command()
{
    char* line_for_return = NULL;
    ssize_t buff_size = 10;


    if( getline(&line_for_return, &buff_size, stdin) == -1 )
    {
        if(feof(stdin))
        {
            perror("EOF");
            return NULL;
        }
        else
        {
            perror("readline");
            return NULL;
        }  
    }
    
    
    if(strlen(line_for_return)>0)
    {
        line_for_return[strlen(line_for_return)-1]='\0';
    }
    if(strlen(line_for_return)>0)
    {
        add_in_history(line_for_return); //in history.c
    }
    return line_for_return;
}


char** parse_line(char* line_read, char* delim_str)
{
    char* line_read_copy = (char*)malloc(strlen(line_read));
    if(!line_read_copy)
    {
        printf("Memory Allocation error\n");
        return NULL;
    }
    strcpy(line_read_copy,line_read);

    int buff_size = 32;
    char** token_ptr_array = malloc(sizeof(char*)*buff_size);
    if(!token_ptr_array)
    {
        printf("Memory Allocation error\n");
        return NULL;
    }

    int index = 0;

    do
    {
        if(index==0)
        {
            token_ptr_array[index] = strtok(line_read_copy,delim_str);
        }
        else
        {
            token_ptr_array[index] = strtok(NULL,delim_str);
        }
        index++;
        
        if( index >= buff_size )
        {
            buff_size+=32;
            token_ptr_array = realloc(token_ptr_array,buff_size*sizeof(char*));

            if(!token_ptr_array)
            {
                printf("Memory Allocation error\n");
                return NULL;
            }
        }
    }    
    while (token_ptr_array[index-1] != NULL);
    
    return token_ptr_array;
}