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

struct dirent *GLOBAL_DE;
struct stat SB;
struct background_jobs{
    char* cmd;
    pid_t pid;
};

int count_background_task;
struct background_jobs back_jobs[500]; //Maximum possible 500 background jobs

int foreground_pid;
int INT_MAIN_PROC_PID;

char HOME_DIRECTORY[500];
char HISTORY_PATH[600];

int EXIT_STAT;