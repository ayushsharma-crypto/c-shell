#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"

int history_setup()
{
    // setting history storage file name and path
    HISTORY_FILE_NAME = "cmd_history.txt";
    HISTORY_FILE_PATH = my_malloc(HISTORY_FILE_PATH,strlen(HOME_DIRECTORY) + strlen(HISTORY_FILE_NAME)+1);
    if(!HISTORY_FILE_PATH) 
    {
        perror("HISTORYSETUP");
        return 1;
    }
    strcpy(HISTORY_FILE_PATH,HOME_DIRECTORY);
    strcpy(HISTORY_FILE_PATH,"/");
    strcpy(HISTORY_FILE_PATH,HISTORY_FILE_NAME);

    // setting default list for command history
    char *buffer = my_malloc(buffer,HISTORY_SZ);
    int fd = open(HISTORY_FILE_PATH, O_RDONLY|O_CREAT, 0600);
    if(!buffer || fd<0 || read(fd,buffer,HISTORY_SZ)<0)
    {
        perror("HISTORYSETUP");
        return 1;
    }
    HISTORY_COUNT=parse(buffer,"\n",&HISTORY, HISTORY_SZ);
    if(HISTORY_COUNT<0) HISTORY_COUNT=0;
    close(fd);

    return 0;
}


int history_add(char* cmd)
{
    int flag=1;
    for(int i=0;i<HISTORY_COUNT;i++)
        if(!strcmp(HISTORY[i],cmd)) 
            flag=0;
    
    if(!flag) return 0;

    char *buffer = my_malloc(buffer,HISTORY_SZ);
    int fd = open(HISTORY_FILE_PATH, O_RDONLY| O_WRONLY);
    if(!buffer || fd<0 || read(fd,buffer,HISTORY_SZ)<0)
    {
        perror("HISTORYSETUP");
        return 1;
    }

    strcpy(HISTORY[HISTORY_COUNT++],cmd);
    if(HISTORY_COUNT>MAX_HISTORY_CMD)
    {
        HISTORY++;
        HISTORY_COUNT--;
    }
    write(fd,"\n",1);
    for (int i = 0; i < HISTORY_COUNT; i++)
    {
        write(fd,HISTORY[i],strlen(HISTORY[i]));
        write(fd,"\n",2);
    }
    

    close(fd);

}

int history_cmd(char** param){}