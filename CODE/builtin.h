#ifndef __BUILTIN_H
#define __BUILTIN_H


int total_builtin_count();
char** builtin_cmds();
void builtin_funcs();



int cd_cmd(char** desired_wd);
int pwd_cmd(char** pwd_para);
int echo_cmd(char** curr_string);
int pinfo_cmd(char** proc_ID);

int setenv_cmd(char** args);
int unsetenv_cmd(char** args);
int jobs_cmd(char **args);
int overkill_cmd(char **args);
int kjob_cmd(char** args);
int fg_cmd(char** args);
int bg_cmd(char** args);

int ls_cmd(char** curr_ls);

void ls_display(int flag_l,int flag_a,char** direc_ptr);
void ls_single_display(int flag_l,int flag_a,char* dir);
void descriptive_display(int flag_l,char* direc_ptr);

void get_file_permission(char* permissions);
void get_file_username(char* username);
void get_file_groupname(char* groupname);
void get_file_time(char* timedisplay);


char* command_history[20];
int stored_cmd_size;
void retrieve_history();
int history_cmd(char** proc_ID);
void add_in_history(char* cmd_line);

int nightswatch_cmd(char** args);
void interrupt();
void newborn();
int check_keydown();

#endif