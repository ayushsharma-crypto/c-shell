#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"

int history_setup()
{
    // setting history storage file name and path
    HISTORY.filename = "cmd_history.txt";
    HISTORY.filepath = my_malloc(HISTORY.filepath,strlen(HOME_DIRECTORY) + strlen(HISTORY.filename)+1);
    if(!HISTORY.filepath) 
    {
        perror("HISTORYSETUP");
        return 1;
    }
    strcpy(HISTORY.filepath,HOME_DIRECTORY);
    strcpy(HISTORY.filepath,"/");
    strcpy(HISTORY.filepath,HISTORY.filename);

    // setting default list for command history
    char *buffer = my_malloc(buffer,HISTORY_SZ);
    int fd = open(HISTORY.filepath, O_RDWR| O_CREAT);
    if(!buffer || fd<0 || read(fd,buffer,HISTORY_SZ)<0)
    {
        perror("HISTORYSETUP");
        return 1;
    }
    close(fd);

    // retrieving history if exist!
    char ** HISTORY_TEMP;
    HISTORY.count=parse(buffer,"\n",&HISTORY_TEMP, HISTORY_SZ);
    if(HISTORY.count<0) HISTORY.count=0;
    for(int i=HISTORY.count-1,j=0;i>=0 && j<20;j++,i--)
        HISTORY.list[i]=HISTORY_TEMP[i];

    return 0;
}


int history_add(char* cmd)
{
    if(HISTORY.count && !strcmp(HISTORY.list[HISTORY.count-1],cmd)) return 0;

    // making copy of current cmd.
    char* cmd_copy = my_malloc(cmd_copy,strlen(cmd));
    strcpy(cmd_copy,cmd);

    // Adding cmd to our struct list of history.
    if(HISTORY.count==MAX_HISTORY_CMD)
    {
        free(HISTORY.list[0]);
        for(int i=1;i<HISTORY.count;i++)
            HISTORY.list[i-1]=HISTORY.list[i];
    }
    else HISTORY.count++;
    HISTORY.list[HISTORY.count-1]=cmd_copy;   


    char *buffer = my_malloc(buffer,HISTORY_SZ);
    int fd = open(HISTORY.filepath, O_WRONLY);
    if(!buffer || fd<0)
    {
        perror("HISTORYADD");
        return 1;
    }

    // dumping all history.
    for (int i = 0; i < HISTORY.count; i++)
    {
        write(fd,HISTORY.list[i],strlen(HISTORY.list[i]));
        write(fd,"\n",1);
    }
    close(fd);
    return 0;
}

int history_cmd(char** param){}