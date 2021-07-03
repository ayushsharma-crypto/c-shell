#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int count_param_arg(char** param)
{
    int count=-1;
    while(param[++count]!=NULL);
    return count;
}

int cd_cmd(char** param)
{
    int arg_count = count_param_arg(param),success;
    if(arg_count!=2)
    {
        write(STDERR_FILENO,"Unexpected arguments for`cd` cmd\n",34);
        return 1;
    }

    char* LWD=my_malloc(LWD,CRWD_SZ);
    if(!LWD) return 1;
    if(getcwd(LWD, CRWD_SZ)==NULL) return 1;

    if(!strcmp("~",param[1])) 
        success = chdir(HOME_DIRECTORY);
    else if(!strcmp("-",param[1])) 
        success = chdir(LAST_WORKING_DIRECTORY);
    else 
    {
        char * temp = my_malloc(temp,CRWD_SZ);
        if(!temp) return 1;
        strcpy(temp,"");
        if(param[1][0]=='~')
            strcpy(temp,HOME_DIRECTORY);
        temp = strcat(temp,param[1]);
        success = chdir(temp);
        free(temp);
    }
    if(success!=0)
    {
        perror("CDERR");
        return 1;
    }
    LAST_WORKING_DIRECTORY=LWD;
    return 0;
}

int pwd_cmd(char** param)
{
    int arg_count = count_param_arg(param);
    if(arg_count!=1)
    {
        write(STDERR_FILENO,"Unexpected arguments for`pwd` cmd\n",35);
        return 1;
    }
    char *crwd;
    crwd = my_malloc(crwd,CRWD_SZ);
    if(!getcwd(crwd, CRWD_SZ))
    {
        perror("CDERR");
        return 1;
    }
    else printf("%s",crwd);
    free(crwd);
    return 0;
}


int echo_cmd(char** param)
{
    int arg_count = count_param_arg(param);
    for(int i=1;i<arg_count;++i) printf("%s ",param[i]);
    return 0;
}
