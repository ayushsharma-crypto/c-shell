#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"

int built_cmd_setup()
{
    // built-in cmds list
    char* BUILTIN_CMD_TEMP[] = {
        "cd",
        "pwd",
        "echo",
        // "ls",
        "pinfo",
        "history",
        // "nightswatch",
        // "setenv",
        // "unsetenv",
        // "jobs",
        // "overkill",
        // "kjob",
        // "fg",
        // "bg",
        NULL
    };
    int total_builtin_cmd = sizeof(BUILTIN_CMD_TEMP)/8;
    BUILTIN_CMD = malloc(total_builtin_cmd*8);
    for(int i=0;i<total_builtin_cmd;i++)
        BUILTIN_CMD[i] = BUILTIN_CMD_TEMP[i];

    // list of pointer to functions
    int (*BUILTIN_FUNC_TEMP[])(char**)={
        &cd_cmd,
        &pwd_cmd,
        &echo_cmd,
        // &ls_cmd,
        &pinfo_cmd,
        &history_cmd,
        // &nightswatch_cmd,
        // &setenv_cmd,
        // &unsetenv_cmd,
        // &jobs_cmd,
        // &overkill_cmd,
        // &kjob_cmd,
        // &fg_cmd,
        // &bg_cmd,
        NULL
    };

    int total_builtin_func = sizeof(BUILTIN_FUNC_TEMP)/8;
    BUILTIN_FUNC = malloc(sizeof(BUILTIN_FUNC_TEMP));
    for(int i=0;i<total_builtin_func;i++)
        BUILTIN_FUNC[i] = BUILTIN_FUNC_TEMP[i];

    return 0;
}
