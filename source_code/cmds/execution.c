#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int execute(char* input_line)
{
    // parse for semi-colon separeted commands.
    input_line[strlen(input_line)-1]='\0';
    char **cmd = parse(input_line,";");
    if(!cmd) return 1;
    int i=-1;
    while(cmd[++i]!=NULL)
    {
        // check piping
        // check redirection
        // will check for background & builtiin process

        // Forking the process
        int child_pid = fork();
        if(child_pid < 0)  //Fork Error
        {
            perror("Fork Error");
            return 1;
        }
        else if(child_pid == 0)  // child process
        {
            // Using execvp for replacing the curr_cmd with the curr_child process
            char **parsed_cmd_vector = parse(cmd[i]," \t\r\n");
            if(-1==execvp(parsed_cmd_vector[0],parsed_cmd_vector))
            {
                perror("EXECVP");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else   // parent process
        {
            int child_status;
            if(-1==waitpid(child_pid,&child_status,WUNTRACED))
            {
                perror("WAITPID");
                exit(EXIT_FAILURE);
            }
        }
    }
    free(cmd);
}