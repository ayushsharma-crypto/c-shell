#include "../headers/header.h"
#include "../headers/prompt.h"

int setup()
{
    HOME_DIRECTORY=my_malloc(HOME_DIRECTORY,CRWD_SZ);
    if(!HOME_DIRECTORY) return 1;
    if(getcwd(HOME_DIRECTORY, CRWD_SZ)==NULL) return 1;

    SHELL_PID = getpid();

    printf(ANSI_CLEAR);
    printf(ANSI_GREEN_BOLD "\n#####################################\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "##---\t   Welcome to CLI  \t---##\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "#####################################\n\n\n\n"ANSI_DEFAULT);

    return 0;
}

char* my_malloc(char* storage,int size)
{
    storage = (char*)malloc(size);
    if(!storage) return NULL;
    else return storage;
}

int prompt() 
{
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
    print_line = strcat(print_line,ANSI_RED_BOLD);
    print_line = strcat(print_line,"┌[ ");
    print_line = strcat(print_line,user);
    print_line = strcat(print_line," @ ");
    print_line = strcat(print_line,host);
    print_line = strcat(print_line," ] ");
    print_line = strcat(print_line,ANSI_BLUE_BOLD);
    if(flag) print_line = strcat(print_line,crwd);
    else 
    {
        print_line = strcat(print_line,"~/");
        print_line = strcat(print_line,crwd+index);
    }
    print_line = strcat(print_line,"\n");
    print_line = strcat(print_line,ANSI_RED_BOLD);
    print_line = strcat(print_line,"│\n");
    print_line = strcat(print_line,"└> ");
    print_line = strcat(print_line,ANSI_DEFAULT);

    printf("%s",print_line);
    return 0;
}

