# c-shell
GOTOSH : GOT's Shell


To run the code :-
                    Run command make followed by clear then ./a.out



Assignment2:


File structure:-
                     ./headers.h
                     ./builtin.h
                     ./prompt.h
                     ./runcommands.h
                     ./main.c
                     ./builtin.c
                     ./ls.c
                     ./pinfo.c
                     ./history.c
                     ./prompt.c
                     ./nightswatch.c
                     ./runcommands.c
                     ./README.MD
                     ./history.txt



Decription :
                    The interactive shell program poses
                    the following features :

                    -> Prompt display
                                
                         <ayushsharma@ayush-sharma:~>
                         i.e.
                         <USER@Hostname:~> for your PC.

                    -> Handles few builtin commands can
                        (i)   cd  
                        (ii)  pwd
                        (iii) echo
                        (iv)  ls
                        (v)   pinfo
                        (vi)  history
                        (vii) nightswatch [prototype of original watch command]
                    
                    -> Home Directory i.e. ~ , will be the 
                       directory from which "GOTOSH" is invoked.

                    -> Supports a semi-colon separated list of commands

                    -> cd command mimics ubuntu shell (BASH) command 'cd'.

                    -> pwd command mimics ubuntu shell (BASH) command 'pwd'.

                    -> echo just print the string passed as an argument,
                       but before the semi-colon(if used).
                       Multi-line strings and environmental variables are not
                       handled.

                    -> ls command mimics ubuntu shell (BASH) command 'history'
                       and handles multiple flags with multiple directories.

                    -> pinfo command displays Process state, Virtual memory 
                       size and executible path of process whose process ID 
                       passed as an argument otherwise it will show the same
                       for shell execution process.

                    -> history command mimics ubuntu shell (BASH) command 'history'.
                       But stores at max 20 commands as a history , which get
                       stored in history.txt file.

                    -> nightswatch command just displays a line output 
                       to stdout once in every time interval that was 
                       specified using -n.It executes the command until
                       the 'q' key is pressed.

                       If 'interrupt' used as an argument-
                       That line is basically number of times the CPU(s)
                       has(ve) been interrupted by the keyboard controller
                       (i8042 with ​IRQ 1​).

                       If 'newborn' used as an argument-
                       That line is the PID of the process that was most 
                       recently created on the system.




Assumptions while making GOTOSH( GOT's SHELL ):-

                    -> 'cd' command : (None, same as requirement pdf.)

                    -> 'pwd' command : (None, same as requirement pdf.)

                    -> 'echo' command : (None, same as requirement pdf.)

                    -> 'ls' command : if any of the flag (-l, -la, -al) 
                                      exist as an argument then files and
                                      directories data displayes in long format
                                      otherwise only their names get listed.

                                      long format-

                                . <Directory>:
                                -rw-rw-r--    1 ayushsharma ayushsharma         1441  8 10  2:59 runcommands.c
                                -rw-rw-r--    1 ayushsharma ayushsharma         4609  8 10 21:50 README.MD
                                -rw-r--r--    1 ayushsharma ayushsharma         2842  8 10 16:39 prompt.c
                                -rwxrwxr-x    1 ayushsharma ayushsharma        54936  8 10 21:50 a.out
                                -rw-r--r--    1 ayushsharma ayushsharma           91  8 10 17:29 makefile

                                (permission) (Hardlink) (username) (groupname) (size) (Last modification month) (Last modification Date) (Last Modification time or year) (Name)

                                      short format-

                                . <Directory>:
                                runcommands.c
                                README.MD
                                prompt.c
                                a.out
                                makefile



                    -> 'pinfo' command : Memory size display unit is 1KB.

                    -> 'history' command : Assumption is history.txt file exist already.

                    -> 'nightswatch' command : You have to wait for time-interval
                                               u have passed as an argument for first 
                                               line to appear. 


Libraries Used :-
                * <stdio.h>
                * <stdlib.h>
                * <unistd.h>
                * <string.h>
                * <fcntl.h>
                * <errno.h>
                * <sys/types.h>
                * <dirent.h>
                * <sys/stat.h>
                * <pwd.h>
                * <time.h>
                * <termios.h>
                * <sys/ioctl.h>



Assignment 3:



Properties :

                 (1) Quit command is not implemeted as function.
                 (2) All Specifications has been completed as required.


Conventions :

                 (1) For background process,which exits a line gets printed on CLI defining their termination. One has to press enter for next prompt to be visible.
                     Also it doesn't matter to press enter as the printed line will not affect your next command output which you were typing.

                 (2) Foregroud process which converted to Background process using CTRL+Z will get deleted from background process array only when shell will get closed.

                 (3) Background process which get killed by command kjob , for them no termination line will get printed on CLI.

                 (4) Builtin commands cannot be not background process.


