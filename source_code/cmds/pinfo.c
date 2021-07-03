#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"




int pinfo_cmd(char** param)
{
    // checking for correct format.
    int arg_count = count_param_arg(param);
    pid_t proc_pid;
    if(arg_count == 1) proc_pid = SHELL_PID;
    else if(arg_count ==2) proc_pid = atoi(param[1]);
    else
    {
        write(STDERR_FILENO,"Unexpected arguments for`pinfo` cmd\n",37);
        return 1;
    }

    printf("\npid -- %d\n",proc_pid);


    // accessing process active status
    char* proc_path = (char*)malloc(100);
    char* buffer = (char*)malloc(100);

    sprintf(proc_path,"/proc/%d/status",proc_pid);    
    FILE *file = fopen(proc_path,"r");
    if(!file)
    {
        perror("Error while accessing file '/proc/pid/status' ");
        return 1;
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

    // accessing process memory status
    sprintf(proc_path,"/proc/%d/statm",proc_pid);    
    file = fopen(proc_path,"r");
    if(file == NULL)
    {
        perror("Error while accessing file '/proc/pid/statm' ");
        return 1;
    }
    else
    {
        fgets(buffer,100,file);
        char* memory = strtok(buffer," ");
        long long int mem_val = atoi(memory);
        mem_val *= 4;
        printf("Memory --    %lld KB\n",mem_val);
    }
    
    // accessing process executible path
    sprintf(proc_path,"/proc/%d/exe",proc_pid);
    int len = readlink(proc_path,buffer,1000);
    if(len == -1)
    {
        perror("Error while accessing file '/proc/pid/exe' ");
        return 1;
    }
    else
    {
        buffer[len] = '\0';

        int flag = 0,index =0;
        if(strlen(buffer) < strlen(HOME_DIRECTORY)) flag =1;
        else
            for(index=0;index < strlen(HOME_DIRECTORY);index++)
                if(buffer[index]!=HOME_DIRECTORY[index])
                {
                    flag =1;
                    break;
                }

        if(flag)
            printf("Executable Path --   %s\n", buffer);
        else
            printf("Executable Path --   ~%s\n",buffer+index);
    }

    free(proc_path);
    free(buffer);
    return 0;
}
