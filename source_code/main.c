#include "headers/header.h"
#include "headers/prompt.h"
#include "headers/execution.h"


int main()
{
    if(setup())
    {
        perror("SETUP");
        return 1;
    }

    ssize_t input_sz=0;
    ssize_t buffr_sz=0;
    char* input_line=NULL;

    while(1)
    {
        if(prompt()) 
        {
            perror("PROMPT DISPLAY");
            return 1;
        }

        input_sz=getline(&input_line,&buffr_sz,stdin);
        if(input_sz<=0)
        {
            free(input_line);
            perror("GETLINE");
            break;
        }
        execute(input_line);
    }

    goodbye();
    return 0;
}