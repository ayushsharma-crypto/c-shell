#ifndef __RUNCOMMANDS_H
#define __RUNCOMMANDS_H

// int executecommands(char** args);
void execute(char** args);
int Execute(char* args);
void child_termination_handler();
void c_handler();
void z_handler();
int check_piping(char* cmd);
int check_redirection(char* cmd);

int piping(char* cmd);
void redirection(char* cmd);

void Add_background_proc(int forkReturn,char* curr_cmd);
#endif