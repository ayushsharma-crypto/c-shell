#ifndef __EXECUTION_H
#define __EXECUTION_H

// genral execution layout
int execute(char* input_line);



// built-in cmds function declaration
int count_param_arg(char** param);
int cd_cmd(char** param);
int pwd_cmd(char** param);
int echo_cmd(char** param);


// built-in cmds list
char* BUILTIN_CMD[] = {
    "cd",
    "pwd",
    "echo",
    // "ls",
    // "pinfo",
    // "history",
    // "nightswatch",
    // "setenv",
    // "unsetenv",
    // "jobs",
    // "overkill",
    // "kjob",
    // "fg",
    // "bg"
};

// list of pointer to functions
int (*BUILTIN_FUNC[])(char**)={
    &cd_cmd,
    &pwd_cmd,
    &echo_cmd,
    // &ls_cmd,
    // &pinfo_cmd,
    // &history_cmd,
    // &nightswatch_cmd,
    // &setenv_cmd,
    // &unsetenv_cmd,
    // &jobs_cmd,
    // &overkill_cmd,
    // &kjob_cmd,
    // &fg_cmd,
    // &bg_cmd
};


// background process


#endif