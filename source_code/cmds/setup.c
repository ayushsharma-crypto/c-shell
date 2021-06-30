#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"

int setup()
{
    // setting up Home Directory Global Variable
    HOME_DIRECTORY=my_malloc(HOME_DIRECTORY,CRWD_SZ);
    if(!HOME_DIRECTORY) return 1;
    if(getcwd(HOME_DIRECTORY, CRWD_SZ)==NULL) return 1;

    // getting process ID of current shell
    SHELL_PID = getpid();

    // printing welcome lines.
    printf(ANSI_CLEAR);
    printf(ANSI_GREEN_BOLD "\n#####################################\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "##---\t   Welcome to CLI  \t---##\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "#####################################\n\n\n\n"ANSI_DEFAULT);

    return 0;
}

void goodbye()
{
    // program ending lines!
    printf(ANSI_GREEN_BOLD "\n\n\n#############################\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "##---\t   GOODBYE  \t---##\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "#############################\n\n\n\n"ANSI_DEFAULT);
}