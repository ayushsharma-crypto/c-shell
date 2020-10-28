/* Assuming history.txt file is present. */

#include "headers.h"
#include "prompt.h"
#include "builtin.h"


void retrieve_history()
{
    int fd = open(HISTORY_PATH,O_RDONLY );
    if(fd < 0)
    {
        perror("History File Access Issue");
        return;
    }

    char *buffer = (char*)malloc(1000);
    int szr = read(fd,buffer,1000);

    char* temp = strtok(buffer,"\n");
    while(temp!=NULL && (stored_cmd_size<20))
    {
        command_history[stored_cmd_size++]=temp;
        // printf("%d\n",stored_cmd_size);

        // printf("History=> %s\n",command_history[stored_cmd_size-1]);

        temp = strtok(NULL,"\n");
    }

    close(fd);
}


void add_in_history(char* cmd_line)
{
    int fd = open(HISTORY_PATH,O_RDONLY | O_WRONLY);
    if(fd < 0)
    {
        perror("History File Access Issue");
        return;
    }

    if(stored_cmd_size == 0)
    {
        command_history[stored_cmd_size++]=cmd_line;
        command_history[stored_cmd_size]=NULL;
    }
    else if(stored_cmd_size < 20)
    {
        if(strcmp(cmd_line,command_history[stored_cmd_size-1])==0)
        {
            close(fd);
            return;
        }
        else
        {
            command_history[stored_cmd_size++]=cmd_line;
        }
    }
    else if(stored_cmd_size == 20)
    {
        if(strcmp(cmd_line,command_history[stored_cmd_size-1])==0)
        {
            close(fd);
            return;
        }
        else
        {
            for(int x=0;x<stored_cmd_size-1;x++)
            {
                command_history[x]=command_history[x+1];
            }
            command_history[stored_cmd_size-1]=cmd_line;
        }
    }


    for(int x=0;x<stored_cmd_size;x++)
    {
        write(fd,command_history[x],strlen(command_history[x]));
        write(fd,"\n",1);
    }
    close(fd);
    return;
}



int history_cmd(char** history_args)
{
    int count_show_cmd = 10;
    if(history_args[1]!=NULL)
    {
        count_show_cmd = atoi(history_args[1]);
    }

    if(count_show_cmd>stored_cmd_size)
    {
        count_show_cmd=stored_cmd_size;
    }

    for(int i=stored_cmd_size-count_show_cmd;i<stored_cmd_size;i++)
    {
        printf("%s\n",command_history[i]);
    }

    
    return 0;
}
