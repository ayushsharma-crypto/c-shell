#include "../headers/header.h"
#include "../headers/prompt.h"

int setup()
{
    // setting up Home Directory Global Variable
    HOME_DIRECTORY=my_malloc(HOME_DIRECTORY,CRWD_SZ);
    if(!HOME_DIRECTORY) return 1;
    if(getcwd(HOME_DIRECTORY, CRWD_SZ)==NULL) return 1;

    // getting process ID of current shell
    SHELL_PID = getpid();

    // printing welcome lines.
    printf(ANSI_CLEAR);
    printf(ANSI_GREEN_BOLD "\n#####################################\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "##---\t   Welcome to CLI  \t---##\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "#####################################\n\n\n\n"ANSI_DEFAULT);

    return 0;
}

void goodbye()
{
    // program ending lines!
    printf(ANSI_GREEN_BOLD "\n\n\n#############################\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "##---\t   GOODBYE  \t---##\n"ANSI_DEFAULT);
    printf(ANSI_GREEN_BOLD "#############################\n\n\n\n"ANSI_DEFAULT);
}


int count_chars (const char* str, char c) {
    // counts the number of occurences of c in str

    size_t len = strlen(str);
    size_t count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

char* my_malloc(char* storage,int size)
{
    // allocates memory if possible.
    storage = (char*)malloc(size);
    if(!storage) return NULL;
    else return storage;
}

int prompt() 
{
    // print the user@host for the system, 
    // and current working directory w.r.t home directory.
    char *user, *host, *crwd;
    user = my_malloc(user,USER_SZ);
    crwd = my_malloc(crwd,CRWD_SZ);
    host = my_malloc(host,HOST_SZ);
    if(!host || !crwd || !user) return 1;
    user = getlogin();
    if(!user || !getcwd(crwd, CRWD_SZ) || gethostname(host,HOST_SZ)==-1) return 1;

    int flag = 0,index =0;
    if(strlen(crwd) < strlen(HOME_DIRECTORY)) flag=1;
    else
        for(index=0;index < strlen(HOME_DIRECTORY);index++)
            if(crwd[index]!=HOME_DIRECTORY[index]) 
            {
                flag=1;
                break;
            }

    char *print_line;
    print_line = my_malloc(print_line,STRG_SZ);
    print_line = strcat(print_line,ANSI_RED_BOLD);
    print_line = strcat(print_line,"┌[ ");
    print_line = strcat(print_line,user);
    print_line = strcat(print_line," @ ");
    print_line = strcat(print_line,host);
    print_line = strcat(print_line," ] ");
    print_line = strcat(print_line,ANSI_BLUE_BOLD);
    if(flag) print_line = strcat(print_line,crwd);
    else 
    {
        print_line = strcat(print_line,"~/");
        print_line = strcat(print_line,crwd+index);
    }
    print_line = strcat(print_line,"\n");
    print_line = strcat(print_line,ANSI_RED_BOLD);
    print_line = strcat(print_line,"│\n");
    print_line = strcat(print_line,"└> ");
    print_line = strcat(print_line,ANSI_DEFAULT);

    printf("%s",print_line);
    return 0;
}

char** parse(char* input_line, char* delim_str)
{
    size_t len_array = count_chars(input_line, delim_str[0]) + 1;
    int i=0;
    char** token = malloc(sizeof(char*)*len_array);
    token[0] = strtok(input_line,delim_str);
    while (token[i]!=NULL)
        token[i++]=strtok(NULL,delim_str);
    return token;
}

int execute(char* input_line)
{
    // parse for semi-colon separeted commands.
    char **cmd = parse(input_line,";");
    int i=0;
    while(cmd[i]!=NULL) printf("%s\n",cmd[i++]);
}