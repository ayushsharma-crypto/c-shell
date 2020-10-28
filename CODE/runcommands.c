#include "runcommands.h"
#include "prompt.h"
#include "builtin.h"
#include "headers.h"

void execute(char** args)
{
    int i = -1;
    while(args[++i] != NULL)
    {
        Execute(args[i]);
    }
}

int check_piping(char* cmd)
{
    char *piped_cmd = strstr(cmd, "|");
    return ( (piped_cmd==NULL)?0:1 );
}


int check_redirection(char* cmd)
{
    char *in = strstr(cmd,"<");
    char *out = strstr(cmd,">");

    return ( ( (in==NULL) && (out==NULL) ) ? 0 : 1 );
}



int Execute(char* args)
{
        //checking for piping and redirection
        if(check_piping(args))
        {
            piping(args);
            return 0;
        }
        if(check_redirection(args))
        {
            redirection(args);
            return 0;
        }

        // Allocating memory for copy of the current cmd.
        int cmd_size = strlen(args);
        char* curr_cmd_copy1 = (char*)malloc(cmd_size+5);
        char* curr_cmd_copy2 = (char*)malloc(cmd_size+5);
        if( (curr_cmd_copy1 == NULL) || (curr_cmd_copy2 == NULL) )
        {
            printf("Memory Allocation error\n");
            return -1;
        }

        // Copying the current cmd
        strcpy(curr_cmd_copy1,args);
        strcpy(curr_cmd_copy2,args);

        // Find the first arg of curr_cmd
        char* actual_cmd = strtok(curr_cmd_copy1," \t");


        // Getting Inbuilt cmds
        char** builtin_cmd_array = builtin_cmds();


        // parsing the curr_cmd
        char **parsed_curr_cmd = parse_line(curr_cmd_copy2," \t\r\n");
        if(parsed_curr_cmd == NULL)
        {
            printf("Memory Allocation error\n");
            return -1;
        }

        //Integer flag for Checking for background process or built-in cmd
        int builtin_yn = 0;
        int builtin_ind = -1;
        int background_yn = 0;

        // Checking for background_yn
        int cmd_len = -1;
        while(parsed_curr_cmd[cmd_len+1]!=NULL)
        {
            cmd_len++;
        }
        if( (cmd_len >-1) && (strcmp("&",parsed_curr_cmd[cmd_len])==0) )
        {
            background_yn=1;
            parsed_curr_cmd[cmd_len]=NULL;
        }

        // Checking for the actual cmd in the implemented built-in functions.             
        for(int it=0;it < total_builtin_count();it++)
        {
            if(strcmp(actual_cmd,builtin_cmd_array[it]) == 0)
            {
                builtin_yn = 1;
                builtin_ind = it;
            }
        }

        // Forking the process
        int forkReturn = fork();

        if(forkReturn < 0)  //Fork Error
        {
            perror("Fork Error");
        }
        else if(forkReturn == 0)   //Child Process
        {
            setpgid(0,0);
            // Using execvp for replacing the curr_cmd with the curr_child process
            if(!builtin_yn)
            {
                // if(background_yn)
                // {
                //     setpgid(0,0);
                // }
                int ret = execvp(parsed_curr_cmd[0],parsed_curr_cmd);
                if(ret==-1)
                {
                    perror("Execvp");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS); 
                fflush(stdout);
            }
            else
            {
                // builtin_funcs(builtin_ind,parsed_curr_cmd);
                exit(EXIT_SUCCESS);
            }
            
        }
        else    // Parent process
        {
            int child_status;
            if(builtin_yn==1)
            {
                builtin_funcs(builtin_ind,parsed_curr_cmd);
            }

            else if( (background_yn==0) )
            {
                foreground_pid=forkReturn;
                if(-1 == waitpid(forkReturn,&child_status,WUNTRACED))
                {
                    perror("WaitPid");
                }

                // If ctrl+z was pressed
                if(WIFSTOPPED(child_status))
                {
                    back_jobs[count_background_task].pid = foreground_pid;
                    back_jobs[count_background_task++].cmd = args;
                }
                foreground_pid=0;
            }
            else
            {
                signal(SIGCHLD,child_termination_handler);
                Add_background_proc(forkReturn,args);
            }
        }

    return 0;

}


void c_handler()
{
    if(foreground_pid>0 && foreground_pid!=getpid())
    {
        int ret = kill(foreground_pid,SIGKILL);
        if(ret==-1)
        {
            perror("CTRL_C");
        }
    }
    else{}
}

void z_handler()
{
    if(foreground_pid>0 && foreground_pid!=getpid())
    {
        int ret = kill(foreground_pid,SIGSTOP);
        if(ret==-1)
        {
            perror("CTRL_Z");
        }
    }
}


void child_termination_handler()
{ 
    pid_t pid;
    int status,b_job=-1;
    
    pid = waitpid(-1, &status, WNOHANG);
    if(pid>0)
    {
        for(int i=0;i<count_background_task;i++)
        {
            if(back_jobs[i].pid==pid)
            {
                b_job = i;
                break;
            }
        }

        if(b_job!=-1)
        {
            if(WIFEXITED(status))
            {
                if(WEXITSTATUS(status)==EXIT_SUCCESS)
                {
                    fprintf(stderr, "\n %s with pid %d exited normally \n", back_jobs[b_job].cmd, back_jobs[b_job].pid);
                }
                else
                {
                    fprintf(stderr, "\n %s with pid %d exited abnormally \n", back_jobs[b_job].cmd, back_jobs[b_job].pid);
                }
                
            }

            for(int i=b_job;i<count_background_task-1;i++)
            {
                back_jobs[i].pid=back_jobs[i+1].pid;
                back_jobs[i].cmd=back_jobs[i+1].cmd;
            }
            count_background_task--;
            
        }
    }
}

void Add_background_proc(int forkReturn,char* curr_cmd)
{
    curr_cmd[strlen(curr_cmd)-1]='\0';
    printf("Full command= %s\n",curr_cmd);
    printf("Adding above cmd to background process, process=%d \n",forkReturn);
    back_jobs[count_background_task].cmd = curr_cmd;
    back_jobs[count_background_task++].pid = forkReturn;
}
