#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int cd_cmd(char** param)
{
    // checking for correct format.
    int arg_count = count_param_arg(param),success;
    if(arg_count!=2)
    {
        write(STDERR_FILENO,"Unexpected arguments for`cd` cmd\n",34);
        return 1;
    }

    // getting current working directory to update
    // last working directory if successfully executed.
    char* LWD=my_malloc(LWD,CRWD_SZ);
    if(!LWD) return 1;
    if(getcwd(LWD, CRWD_SZ)==NULL) return 1;

    // logic for `cd` cmd.
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
