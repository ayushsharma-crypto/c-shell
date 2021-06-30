#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <signal.h>

#ifndef __HEADER_H
#define __HEADER_H

#define USER_SZ 100
#define HOST_SZ 100
#define CRWD_SZ 1024
#define STRG_SZ 1024
#define BUFF_SZ 600
#define MAX_ONE_TIME_CMD 600

pid_t SHELL_PID;

char* HOME_DIRECTORY;
char* LAST_WORKING_DIRECTORY;



#define BG_PROC "&"
#define SPACE_PARSE " \t\r\n"
#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RED_BOLD "\033[1;31m"
#define ANSI_GREEN_BOLD "\033[1;32m"
#define ANSI_YELLOW_BOLD "\033[1;33m"
#define ANSI_CYAN_BOLD "\033[1;36m"
#define ANSI_DEFAULT "\033[0m"
#define ANSI_CLEAR "\033[2J\033[1;1H"
#define ANSI_BLUE_BOLD "\033[1;34m"

#endif