#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"

int echo_cmd(char** param)
{
    // printing all arguments as it is.
    int arg_count = count_param_arg(param);
    for(int i=1;i<arg_count;++i) printf("%s ",param[i]);
    return 0;
}

