#include "headers.h"
#include "builtin.h"
#include "prompt.h"
#include "runcommands.h"

// Environment Functions

int setenv_cmd(char** args)
{
    int h=0;
    while(args[h++]!=NULL)
    {}

    if(h==3)
    {
        int ret = setenv(args[1],"\0",1);
        if(ret<0)
        {
            perror("SETENV");
        }
    }
    else if(h==4)
    {
        int ret = setenv(args[1],args[2],1);
        if(ret<0)
        {
            perror("SETENV");
        }
        else
        {
            printf("\n%s is set to %s\n\n",args[1],getenv(args[1]));
        }
        
    }
    else
    {
        write(2,"Error in setenv arguments.",27);
    }
    return 0;
    
}



int unsetenv_cmd(char** args)
{
    int h=0;
    while(args[h++]!=NULL)
    {}

    if(h==3)
    {
        int ret = unsetenv(args[1]);
        if(ret<0)
        {
            perror("UNSETENV");
        }
        else
        {
            printf("\n%s is unset\n\n",args[1]);
        }
        
    }
    else
    {
        write(2,"Error in unsetenv arguments.",27);
    }
    return 0;
    
}

// Function for showing all background jobs

int jobs_cmd(char **args)
{

    int h=0;
    while(args[h++]!=NULL){}
    if(h!=2)
    {
        write(2,"Error in jobs arguments.",25);
        return -1;
    }


    for(int i=0;i<count_background_task;i++)
    {
        char* proc_path = (char*)malloc(100);
        char* buffer = (char*)malloc(100);
        char* status = (char*)malloc(15);

        sprintf(proc_path,"/proc/%d/status",back_jobs[i].pid);    
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
                    status = buffer+10;
                    break;
                }
                line_number++;
            }
        }
        status[strlen(status)-1]='\0';
        
        printf("[%d] %s\b %s [%d]\n",i+1,status,back_jobs[i].cmd,back_jobs[i].pid);
    }
}


// Function to kill all the background process

int overkill_cmd(char **args)
{
    int h=0;
    while(args[h++]!=NULL){}
    if(h!=2)
    {
        write(2,"Error in overkill arguments.",29);
        return -1;
    }

    for(int i =count_background_task-1;i>=0;i--)
    {
        pid_t pid = back_jobs[i].pid;
        int ret= kill(pid,SIGKILL);
        if(ret < 0)
        {
            perror("BackgroundKill");
            return -1;
        }
        else
        {
            back_jobs[i].cmd=NULL;
            back_jobs[i].pid=-1;
            count_background_task--;
        }
    }
}


//Implementing KJOB

int kjob_cmd(char** args)
{
    int h=0;
    while(args[h++]!=NULL){}
    if(h!=4)
    {
        write(2,"Error in KJOB arguments.",29);
        return -1;
    }

    int K_num = atoi(args[1]);
    int K_signal = atoi(args[2]);

    if((K_num > count_background_task) || (K_num <= 0) )
    {
        write(2,"Error No such job\nRun jobs to see running jobs\n",49);
        return -1;
    }
    int ret = kill(back_jobs[K_num-1].pid, K_signal);
    if(ret<0)
    {
        perror("KILL");
    }
    else
    {    
        printf("Signal %d was sent to proc %d\n",K_signal,K_num);
    }
}


// implementing FG and BG

int bg_cmd(char** args)
{
    int h=0;
    while(args[h++]!=NULL){}
    if(h!=3)
    {
        write(2,"Error in bg arguments.",29);
        return -1;
    }
    int K_num = atoi(args[1]);

    if((K_num > count_background_task) || (K_num <= 0) )
    {
        write(2,"Error No such job\nRun jobs to see running jobs\n",49);
        return -1;
    }
    int ret = kill(back_jobs[K_num-1].pid, SIGCONT);
    if(ret<0)
    {
        perror("KILL");
    }
    else
    {    
        printf("Signal %d was sent to proc %d, now Running\n",SIGCONT,K_num);
    }

}


int fg_cmd(char** args)
{
    // printf("Fg=%d and gepid=%d and INT_MAIN_PID=%d\n",foreground_pid,getpid(),INT_MAIN_PROC_PID);

    int h=0;
    while(args[h++]!=NULL){}
    if(h!=3)
    {
        write(2,"Error in fg arguments.",29);
        return -1;
    }
    int K_num = atoi(args[1]);

    if((K_num > count_background_task) || (K_num <= 0) )
    {
        write(2,"Error No such job,Run jobs to see running jobs\n",49);
        return -1;
    }

    int K_pid = back_jobs[K_num-1].pid;
    char *K_cmd = back_jobs[K_num-1].cmd;
    for(int i=K_num-1;i<count_background_task-1;i++)
    {
        back_jobs[i].pid=back_jobs[i+1].pid;
        back_jobs[i].cmd=back_jobs[i+1].cmd;
    }
    count_background_task--;
    foreground_pid=K_pid;

    signal(SIGTTIN,SIG_IGN);
    signal(SIGTTOU,SIG_IGN);
    tcsetpgrp(0,K_pid);
    int ret = kill(K_pid,SIGCONT);
    if(ret<0)
    {
        perror("KILL");
        return -1;
    }
    // printf("Fg=%d and gepid=%d\n",foreground_pid,getpid());



    int stts;
    waitpid(K_pid,&stts,WUNTRACED);
    tcsetpgrp(0,getpgrp());
    signal(SIGTTIN,SIG_DFL);
    signal(SIGTTOU,SIG_DFL);
    if(WIFSTOPPED(stts))
    {
        back_jobs[count_background_task].cmd=K_cmd;
        back_jobs[count_background_task++].pid=K_pid;
    }
    foreground_pid=0;

}

