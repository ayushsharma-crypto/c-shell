#include "builtin.h"
#include "headers.h"


char* builtin_cmd[] = {
    "cd",
    "pwd",
    "echo",
    "ls",
    "pinfo",
    "history",
    "nightswatch",
    "setenv",
    "unsetenv",
    "jobs",
    "overkill",
    "kjob",
    "fg",
    "bg"
};

char** builtin_cmds()
{
    return builtin_cmd;
}

int total_builtin_count() 
{
    return (sizeof(builtin_cmd) / sizeof(char*));
}

int (*builtin_func[])(char**)={
    &cd_cmd,
    &pwd_cmd,
    &echo_cmd,
    &ls_cmd,
    &pinfo_cmd,
    &history_cmd,
    &nightswatch_cmd,
    &setenv_cmd,
    &unsetenv_cmd,
    &jobs_cmd,
    &overkill_cmd,
    &kjob_cmd,
    &fg_cmd,
    &bg_cmd
};


void builtin_funcs(int index,char** req_para)
{
    (*builtin_func[index])(req_para);
}






int cd_cmd(char** desired_wd)
{
    EXIT_STAT=-1;
    int h=0;
    while(desired_wd[h++]!=NULL)
    {}

    if(h != 3)
    {
        printf("Unexpected arguments for cd command.\n");
        EXIT_STAT=0;
    }
    else
    {
        char tilda[1] = "~";
        char dash[1] = "-";
        if(desired_wd[1][0] == tilda[0]  && strlen(desired_wd[1])==1)
        {
            if(chdir(HOME_DIRECTORY)!=0)
            {
                perror("cd: ~:");
                EXIT_STAT=0;
            }
        }
        else if (desired_wd[1][0] == tilda[0]  && strlen(desired_wd[1])>1)
        {
            char* temp_cwd = (char*)malloc(500);
            if(!temp_cwd)
            {
                printf("Memory Allocation Error\n");
                EXIT_STAT=0;
                return -1;
            }

            getcwd(temp_cwd,500);

            if(chdir(HOME_DIRECTORY)!=0)
            {
                perror("cd: ~:");
                EXIT_STAT=0;
            }
            if(chdir(desired_wd[1]+2)!=0)
            {
                perror("cd: ChangePath: ");
                chdir(temp_cwd);
                EXIT_STAT=0;
            }
            free(temp_cwd);
        }
        else if(desired_wd[1][0]==dash[0]  && strlen(desired_wd[1])==1)
        {
            if(chdir("..")!=0)
            {
                perror("CD - Error");
                EXIT_STAT=0;
            }
            char *tmp = (char*)malloc(100);
            getcwd(tmp,100);
            printf("%s\n",tmp);
        }
        else if(chdir(desired_wd[1])!=0)
        {
            perror("cd: ChagePath: ");
            EXIT_STAT=0;
        }
    }
    if(EXIT_STAT!=0)
    {
        EXIT_STAT=1;
    }
    return 0;    
}

int pwd_cmd(char** pwd_para)
{
    EXIT_STAT=-1;
    int h=0;
    while(pwd_para[h++]!=NULL)
    {}

    char* temp_pwd = (char*)malloc(500*sizeof(char));
    if(!temp_pwd)
    {
        printf("Memory Allocation Error\n");
        EXIT_STAT=0;
        return -1;
    }


    if(getcwd(temp_pwd,500)==NULL)
    {
        perror("PWD");
        EXIT_STAT=0;
        return -1;
    }
    else
    {
        printf("%s\n",temp_pwd);
    }

    if(h > 2)
    {
        printf("Unknown Arguments\n");
        EXIT_STAT=0;
    }
    
    free(temp_pwd);
    if(EXIT_STAT!=0)
    {
        EXIT_STAT=-1;
    }
    return 0;
}

int echo_cmd(char** curr_string)
{
    EXIT_STAT=-1;
    int h=1;
    while(curr_string[h]!=NULL)
    {
        if(curr_string[h+1]==NULL)
        {
            printf("%s\n",curr_string[h]);
        }
        else
        {
            printf("%s ",curr_string[h]);
        }
        h++;        
    }
    EXIT_STAT=1;
    return 0;
}