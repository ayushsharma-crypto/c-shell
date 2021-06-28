#include "headers/header.h"
#include "headers/prompt.h"


int main()
{
    if(setup())
    {
        perror("SETUP:");
        return 1;
    }

    while(1)
    {
        if(prompt()) 
        {
            perror("PROMPT DISPLAY:");
            return -1;
        }
    }
    return 0;
}