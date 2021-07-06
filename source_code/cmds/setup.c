#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int setup()
{
    welcome();
 
    // setting up Home Directory Global Variable
    HOME_DIRECTORY=my_malloc(HOME_DIRECTORY,CRWD_SZ);
    if(!HOME_DIRECTORY) return 1;
    if(getcwd(HOME_DIRECTORY, CRWD_SZ)==NULL) return 1;

    // setting up Last Working Directory Global Variable
    LAST_WORKING_DIRECTORY=my_malloc(LAST_WORKING_DIRECTORY,CRWD_SZ);
    if(!LAST_WORKING_DIRECTORY) return 1;
    if(getcwd(LAST_WORKING_DIRECTORY, CRWD_SZ)==NULL) return 1;

    // getting process ID of current shell
    SHELL_PID = getpid();

    // built command setup
    built_cmd_setup();

    // history setup
    if(history_setup()) return 1;

    return 0;
}



void welcome()
{
    // printing welcome lines.
    printf(ANSI_CLEAR);
    printf(ANSI_GREEN_BOLD "\n#####################################\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "##---\t   Welcome to CLI  \t---##\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "#####################################\n\n\n\n"ANSI_DEFAULT);
}

void goodbye()
{
    // program ending lines!
    printf(ANSI_GREEN_BOLD "\n\n\n#############################\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "##---\t   GOODBYE  \t---##\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "#############################\n\n\n\n"ANSI_DEFAULT);
}