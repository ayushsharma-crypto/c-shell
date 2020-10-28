#include "headers.h"
#include "prompt.h"
#include "runcommands.h"
#include "builtin.h"

int main()
{

    if(getcwd(HOME_DIRECTORY,500) == NULL)
    {
        perror("Home");
        return 0;
    }

    strcpy(HISTORY_PATH,HOME_DIRECTORY);
    strcat(HISTORY_PATH,"/history.txt");


    retrieve_history();
    count_background_task=0;
    signal(SIGCHLD,child_termination_handler);
    signal(SIGINT,c_handler);
    signal(SIGTSTP,z_handler);

    INT_MAIN_PROC_PID=getpid();
    EXIT_STAT=-1;

    while (1)
    {
        foreground_pid=0;
        if(prompt())
        {
            perror("CWD");
            return 0;
        }
        EXIT_STAT=-1;

        char* line = (char*)malloc(500);
        char** args = malloc(sizeof(char*)*10);

        line = read_line_command();

        if((line==NULL) || (strcmp(line,"quit")==0))
        {
            char** tempo = malloc(20*sizeof(char*));
            tempo[0] = "overkill";
            tempo[1] = NULL;
            overkill_cmd(tempo);
            free(tempo);
            exit(0);
        }
        args = parse_line(line,";");
        if(args == NULL)
        {
            return 0;
        }


        // executecommands(args);
        execute(args);
        fflush(stdout);

    }
}
