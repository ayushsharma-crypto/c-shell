#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"

char* my_malloc(char* storage,int size)
{
    // allocates memory if possible.
    storage = (char*)malloc(size);
    if(!storage) return NULL;
    else return storage;
}

int prompt() 
{
    // print the user@host for the system, 
    // and current working directory w.r.t home directory.
    char *user, *host, *crwd;
    user = my_malloc(user,USER_SZ);
    crwd = my_malloc(crwd,CRWD_SZ);
    host = my_malloc(host,HOST_SZ);
    
    if(!host || !crwd || !user) return 1;
    user = getlogin();
    if(!user || !getcwd(crwd, CRWD_SZ) || gethostname(host,HOST_SZ)==-1) return 1;

    int flag = 0,index =0;
    if(strlen(crwd) < strlen(HOME_DIRECTORY)) flag=1;
    else
        for(index=0;index < strlen(HOME_DIRECTORY);index++)
            if(crwd[index]!=HOME_DIRECTORY[index]) 
            {
                flag=1;
                break;
            }

    char *print_line;
    print_line = my_malloc(print_line,STRG_SZ);
    print_line = strcpy(print_line,ANSI_RED_BOLD);
    print_line = strcat(print_line,"\n┌[ ");
    print_line = strcat(print_line,user);
    print_line = strcat(print_line," @ ");
    print_line = strcat(print_line,host);
    print_line = strcat(print_line," ] ");
    print_line = strcat(print_line,ANSI_BLUE_BOLD);
    if(flag) print_line = strcat(print_line,crwd);
    else 
    {
        print_line = strcat(print_line,"~");
        print_line = strcat(print_line,crwd+index);
    }
    print_line = strcat(print_line,"\n");
    print_line = strcat(print_line,ANSI_RED_BOLD);
    print_line = strcat(print_line,"│\n");
    print_line = strcat(print_line,"└> ");
    print_line = strcat(print_line,ANSI_DEFAULT);

    write(STDOUT_FILENO,print_line,strlen(print_line)+1);
    free(print_line);
    return 0;
}

int parse(char* input_line, char* delim_str,char*** token)
{
    // parses provided string input_line w.r.t. characters
    // of delim_str and then stores as form of tokens.
    int i=0;
    *token = malloc(sizeof(char*)*MAX_ONE_TIME_CMD);
    if(!(*token)) 
    {
        perror("MEMORY");
        return -1;
    }
    token[0][0] = strtok(input_line,delim_str);
    while (token[0][i]!=NULL)
        token[0][++i]=strtok(NULL,delim_str);
    return i;
}