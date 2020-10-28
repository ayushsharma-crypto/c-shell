#include "headers.h"
#include "builtin.h"

int pinfo_cmd(char** proc_ID)
{
    int count_args = 0;
    while(proc_ID[count_args++]!= NULL)
    {}

    pid_t proc_pid;

    if(count_args == 2)
    {
        proc_pid = INT_MAIN_PROC_PID;
    }
    else if(count_args ==3)
    {
        proc_pid = atoi(proc_ID[1]);
    }
    else
    {
        printf("Extra Argument\n");
    }

    printf("pid -- %d\n",proc_pid);

    char* proc_path = (char*)malloc(100);
    char* buffer = (char*)malloc(100);

    sprintf(proc_path,"/proc/%d/status",proc_pid);    
    FILE *file = fopen(proc_path,"r");
    if(file == NULL)
    {
        perror("Error while accessing file '/proc/pid/status' ");
    }
    else
    {
        int line_number =0;
        while(fgets(buffer,100,file))
        {
            if(line_number == 2)
            {
                printf("Process Status -- %s",buffer+7);
                break;
            }
            line_number++;
        }
    }

    sprintf(proc_path,"/proc/%d/statm",proc_pid);    
    file = fopen(proc_path,"r");
    if(file == NULL)
    {
        perror("Error while accessing file '/proc/pid/statm' ");
    }
    else
    {
        fgets(buffer,100,file);
        char* memory = strtok(buffer," ");
        long long int mem_val = atoi(memory);
        mem_val *= 4;
        printf("Memory --    %lld KB\n",mem_val);
    }
    
    sprintf(proc_path,"/proc/%d/exe",proc_pid);
    int len = readlink(proc_path,buffer,1000);
    if(len == -1)
    {
        perror("Error while accessing file '/proc/pid/exe' ");
    }
    else
    {
        buffer[len] = '\0';

        int flag = 0,index =0;
        if(strlen(buffer) < strlen(HOME_DIRECTORY))
        {
            flag =1;
        }
        else
        {
            for(index=0;index < strlen(HOME_DIRECTORY);index++)
            {
                if(buffer[index]!=HOME_DIRECTORY[index])
                {
                    flag =1;
                    break;
                } 
            }
            
        }
        if(flag)
        {
            printf("Executable Path --   %s\n", buffer);        
        }
        else
        {
            printf("Executable Path --   ~%s\n",buffer+index);         
        }
    }
    return 0;
}