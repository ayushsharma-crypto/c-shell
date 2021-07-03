#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int pwd_cmd(char** param)
{
    // checking for correct format.
    int arg_count = count_param_arg(param);
    if(arg_count!=1)
    {
        write(STDERR_FILENO,"Unexpected arguments for`pwd` cmd\n",35);
        return 1;
    }

    // printing current working directory w.r.t root directory.
    char *crwd;
    crwd = my_malloc(crwd,CRWD_SZ);
    if(!getcwd(crwd, CRWD_SZ))
    {
        perror("CDERR");
        return 1;
    }
    else printf("%s\n",crwd);
    free(crwd);
    return 0;
}