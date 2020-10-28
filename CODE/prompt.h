#ifndef __PROMPT_H
#define __PROMPT_H

int prompt();
char* read_line_command();
char** parse_line(char* line_read, char* delim_str);
#endif