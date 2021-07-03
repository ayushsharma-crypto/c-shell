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
    int arg_count = count_param_arg(param);
    if(arg_count!=2)
    {
        write(STDERR_FILENO,"Unexpected arguments for`cd` cmd\n",34);
        return 1;
    }
    int success;
    if(!strcmp("~",param[1])) 
        success = chdir(HOME_DIRECTORY);
    else if(!strcmp("-",param[1])) 
        success = chdir(LAST_WORKING_DIRECTORY);
    else 
        success = chdir(param[1]);
    if(success!=0)
    {
        perror("CDERR");
        return 1;
    }
    return 0;
}

int pwd_cmd(char** param)
{
    return 0;
}


int echo_cmd(char** param)
{
    return 0;
}
