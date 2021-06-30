#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int execute(char* input_line)
{
    // parse for semi-colon separated commands.
    input_line[strlen(input_line)-1]='\0';
    char **cmd = parse(input_line,";");
    if(!cmd) return 1;
    int i=-1;

    // running each command separately
    while(cmd[++i]!=NULL)
    {
        // check piping
        // check redirection
        
        // checking for background command
        int bg_proc = 0;
        if(cmd[i][strlen(cmd[i])-1]==BG_PROC) 
        {
            bg_proc=1;
            cmd[i][strlen(cmd[i])-1]='\0';
        }

        char **parsed_cmd_vector = parse(cmd[i],SPACE_PARSE);
        // checking for builtin command
        int builtin_proc=0;

        // forking the process
        int child_pid = fork();
        if(child_pid < 0)  //Fork Error
        {
            perror("FORKERR");
            return 1;
        }
        else if(child_pid == 0)  // child process
        {
            int success_flag=1;
            char* buffer = my_malloc(buffer,BUFF_SZ);
            
            // if command is builtin then run same otherwise use `execvp`
            if(builtin_proc)
            {}
            // using execvp for replacing the curr_cmd with the curr_child process
            else if(-1==execvp(parsed_cmd_vector[0],parsed_cmd_vector))
            {
                perror("EXECVPERR");
                success_flag=0;
            }

            // printing success/failure message on stderr
            if(success_flag) 
                sprintf(buffer,"%s with pid %d exited \033[1;32mnormally.\033[0m\n",parsed_cmd_vector[0],getpid());
            else
                sprintf(buffer,"%s with pid %d exited \033[1;31mAb-normally.\033[0m\n",parsed_cmd_vector[0],getpid());
            
            write(STDERR_FILENO,buffer,BUFF_SZ);
            free(buffer);
            exit(EXIT_SUCCESS);
        }
        else   // parent process
        {
            // if current command is not background
            // then wait for the child to finish.
            if(!bg_proc)
            {
                int child_status;
                if(-1==waitpid(child_pid,&child_status,WUNTRACED))
                {
                    perror("WAITPID");
                    exit(EXIT_FAILURE);
                }
                // check if child ended due to signal
            }
            else
            {
                // handle database for background processes.
            }
        }
    }
    free(cmd);
}