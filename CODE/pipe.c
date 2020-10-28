#include "headers.h"
#include "builtin.h"
#include "runcommands.h"
#include "prompt.h"

int piping(char* cmd)
{
    char** piped_element = parse_line(cmd,"|");

    if(piped_element==NULL)
    { return -1; }

    int p_arr[2],fd =0;
    pid_t forkReturn;

    int p_index=-1;
    while(piped_element[++p_index]!=NULL)
    {
        pipe(p_arr);
        forkReturn=fork();
        if(forkReturn<0)
        {
            perror("PIPING FORK");
        }
        else if(forkReturn==0)
        {
            dup2(fd,0);

            if(piped_element[p_index+1]!=NULL)
            {
                dup2(p_arr[1],1);
            }
            close(p_arr[0]);
            Execute(piped_element[p_index]);
            exit(2);
        }
        else
        {
            wait(NULL);
            close(p_arr[1]);
            fd=p_arr[0];
        }
    }
}