#ifndef __PROMPT_H
#define __PROMPT_H

int setup();
int built_cmd_setup();
int prompt();
int parse(char* input_line, char* delim_str, char*** token);
void goodbye();
char* my_malloc(char* storage,int size);
#endif