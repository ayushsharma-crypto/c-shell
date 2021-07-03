#ifndef __PROMPT_H
#define __PROMPT_H

int setup();
int prompt();
int parse(char* input_line, char* delim_str, char*** token, int allocate_mem);
void goodbye();
void welcome();
char* my_malloc(char* storage,int size);
#endif