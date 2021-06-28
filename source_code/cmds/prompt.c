#include "../headers/header.h"
#include "../headers/prompt.h"

int setup()
{
    HOME_DIRECTORY=my_malloc(HOME_DIRECTORY,crwd_sz);
    if(!HOME_DIRECTORY) return 1;
    if(getcwd(HOME_DIRECTORY, crwd_sz)==NULL) return 1;
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
    user = my_malloc(user,user_sz);
    crwd = my_malloc(crwd,crwd_sz);
    host = my_malloc(host,host_sz);
    if(!host || !crwd || !user) return 1;
    user = getlogin();
    if(!user || !getcwd(crwd, crwd_sz) || gethostname(host,host_sz)==-1) return 1;

    int flag = 0,index =0;
    if(strlen(crwd) < strlen(HOME_DIRECTORY)) flag=1;
    else
        for(index=0;index < strlen(HOME_DIRECTORY);index++)
            if(crwd[index]!=HOME_DIRECTORY[index]) flag=1;

    if(!flag)printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m~%s\033[0m> ",user,host,crwd+index);
    else printf("\n<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m> ",user,host,crwd);
    return 0;
}