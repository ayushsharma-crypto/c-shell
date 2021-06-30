#ifndef __PROMPT_H
#define __PROMPT_H

int setup();
int prompt();
void goodbye();
char* my_malloc(char* storage,int size);
char** parse(char* input_line, char* delim_str);

#endif