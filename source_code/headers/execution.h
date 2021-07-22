#ifndef __EXECUTION_H
#define __EXECUTION_H

// genral execution layout
int execute(char* input_line);

// built-in cmds list
char** BUILTIN_CMD;

// list of pointer to functions
int (**BUILTIN_FUNC)(char**);

// setup & helper function for builtin cmds
int built_cmd_setup();
int history_setup();
int history_add(char* cmd);
int count_param_arg(char** param);

// built-in cmds function declaration
int cd_cmd(char** param);
int pwd_cmd(char** param);
int echo_cmd(char** param);
int pinfo_cmd(char** param);
int history_cmd(char** param);
int nightswatch_cmd(char** param);


// background process


#endif