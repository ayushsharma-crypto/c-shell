#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int execute(char* input_line)
{
    // parse for semi-colon separated commands.
    input_line[strlen(input_line)-1]='\0';
    char **cmd;
    int arg_count = parse(input_line,";",&cmd);
    if(arg_count<=0) return 1;
    int i=-1;

    // running each command separately
    while(cmd[++i]!=NULL)
    {
        // check piping
        // check redirection

        // parsing the current command w.r.t spaces
        char **parsed_cmd_vector;
        int arg_count = parse(cmd[i],SPACE_PARSE, &parsed_cmd_vector);
        if(arg_count<=0) continue;

        // checking for background command
        int bg_proc = 0;
        if(!strcmp(parsed_cmd_vector[arg_count-1],BG_PROC) || 
            parsed_cmd_vector[arg_count-1][strlen(parsed_cmd_vector[arg_count-1])-1]==BG_PROC[0]
        ) 
        {
            bg_proc=1;
            parsed_cmd_vector[--arg_count]=NULL;
        }


        // checking for builtin command
        int builtin_proc_index=-1;
        for(int i=0;i<sizeof(BUILTIN_CMD)/8;i++)
        {
            if(!strcmp(BUILTIN_CMD[i],parsed_cmd_vector[0]))
            {
                builtin_proc_index=i;
                break;
            }
        }

        // forking the process
        int child_pid = fork();
        if(child_pid < 0)  //Fork Error
        {
            perror("FORKERR");
            return 1;
        }
        else if(child_pid == 0)  // child process
        {
            if(builtin_proc_index>=0) exit(EXIT_SUCCESS);
            // using execvp for replacing the curr_cmd 
            // with the curr_child process
            if(-1==execvp(parsed_cmd_vector[0],parsed_cmd_vector))
            {
                perror("EXECVPERR");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else   // parent process
        {
            if(builtin_proc_index>=0)
            {
                if(-1==(*BUILTIN_FUNC[builtin_proc_index])(parsed_cmd_vector))
                {
                    perror("BUILTINERR");
                    exit(EXIT_FAILURE);            
                }
            }
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
                // handle database for background processes & printing on copletio/stopping/killed etc.
            }
        }
    }
    free(cmd);
}