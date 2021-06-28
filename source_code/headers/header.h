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

#define user_sz 100
#define host_sz 100
#define crwd_sz 500

char* HOME_DIRECTORY;

#endif