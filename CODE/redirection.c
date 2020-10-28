
#include "headers.h"
#include "builtin.h"
#include "runcommands.h"
#include "prompt.h"

void redirection(char* cmd)
{
    int flag_custm_inpt = ( ( NULL==strstr(cmd,"<") ) ? 0 : 1); 
    int flag_custm_outpt = ( ( NULL==strstr(cmd,">>") ) ? 0 : 2);
    
    if(flag_custm_outpt==0)
    {
        flag_custm_outpt = ( ( NULL==strstr(cmd,">") ) ? 0 : 1);
    }

    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);

    char *input_ptr;
    char *input_file;
    char *output_ptr;
    char *output_file;

    output_ptr=&cmd[0];
    if(flag_custm_outpt)
    {
        output_ptr=strtok(cmd,">");
        output_file=strtok(NULL,">");
        output_file=strtok(output_file," \t");

        if(output_file==NULL)
        {
            write(2,"Error No output file provided\n",31);
            return;
        }
    }

    input_ptr=output_ptr;
    if(flag_custm_inpt)
    {
        // printf("a= %s\n",input_file);
        input_ptr=strtok(input_ptr,"<");
        // printf("b= %s\n",input_file);
        input_file=strtok(NULL,"<");
        // printf("c= %s\n",input_file);
        input_file=strtok(input_file," \t");
        // printf("d= %s\n",input_file);

        if(input_file == NULL)
        {
            write(2,"Error No Input file provided\n",30);
            return;
        }

        struct stat sb;
        if( !( ( stat(input_file,&sb)==0 ) && ( !S_ISDIR(sb.st_mode) ) ) )
        {
            write(2,"Error Input File doesnot exist\n",32);
            return;
        }
    }


    char **input_arg = parse_line(input_ptr," \t");

    pid_t forkReturn = fork();
    int status;
    if(forkReturn<0)
    {
        perror("REDIRECTION FORK");
        return;
    }
    else if(forkReturn>0)
    {
        while(wait(&status)!= forkReturn);
    }
    else
    {
        if(flag_custm_inpt)
        {
            int in_fd = open(input_file,O_RDONLY);
            if(in_fd < 0)
            {
                perror("Input file");
                return;
            }
            dup2(in_fd,0);
            close(in_fd);
        }
        if(flag_custm_outpt)
        {
            int out_fd;
            if(flag_custm_outpt==2)
            {
                out_fd=open(output_file,O_WRONLY | O_CREAT | O_APPEND,0644);
            }
            else
            {
                out_fd=open(output_file,O_WRONLY | O_CREAT | O_TRUNC,0644);
            }
            dup2(out_fd,1);
            close(out_fd);            
        }


        if (execvp(input_arg[0], input_arg) < 0) 
        {     
            perror("Command not found");
            exit(EXIT_FAILURE);
        }


        dup2(saved_stdin, 0);
        close(saved_stdin);
        
        dup2(saved_stdout, 1);
        close(saved_stdout);
    }
}
