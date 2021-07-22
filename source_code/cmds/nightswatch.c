#include "../headers/header.h"
#include "../headers/prompt.h"
#include "../headers/execution.h"


int nightswatch_cmd(char** args)
{
    if(args[1]==NULL)
    {
        printf("incorrect number of argument\n");
        return -1;
    }
    
    if(strcmp(args[1],"-n")!=0)
    {
        printf("Flag required -n as first argument\n");
        return -1;
    }
    int delay_tm = atoi(args[2]);
    if(delay_tm == 0)
    {
        printf("Please keep atleat 1 sec timer\n");
        return -1;
    }

    int process_type;
    char newb[9] = "newborn";
    char intrpt[9] = "interrupt";

    int i = -1;
    while(args[3][++i]!=(char)(17))
    {}
    args[3][i]='\0';

    if(strcmp(args[3],intrpt)==0)
    {
        process_type = 1;
    }
    else if (strcmp(args[3],newb)==0)
    {
        process_type = 0;
    }
    else
    {
        printf("Argument can be either interrupt or newborn\n");
        return -1;
    }
    time_t begin = time(NULL);
    int count =0;
    
    int flag_I = 0,flag_N= 0;

    while( 1 )
    {
        time_t curr_tm = time(NULL);

        if( ((curr_tm-begin)/delay_tm )> count )
        {
            count++;
            if(process_type)
            {
                interrupt(flag_I);
                flag_I =1;
            }
            else
            {
                newborn(flag_N);
                flag_N =1;
            }
            
        }
        if(((check_keydown()) && (getchar() == 'q') ))
        {
            break;
        }
    }
    
}

void interrupt(int flag)
{
    char* path = (char*)malloc(20);
    sprintf(path,"/proc/interrupts");
    FILE* file = fopen(path,"r");
    if(file!=NULL)
    {
        char* buffer = (char*)malloc(150);
        int line_number =0;
        while(fgets(buffer,150,file))
        {
            buffer[95]='\0';
            if(line_number == 0 && (flag==0))
            {
                printf("%s\n",buffer+6);
            }
            else if(line_number == 2)
            {
                printf("%s\n",buffer+6);
                break;
            }
            line_number++;
        }
    }
    else
    {
        perror("Error while accessing file '/proc/interrupts' ");
    }
    free(path);
}

void newborn(int flag)
{
    char* path = (char*)malloc(20);
    sprintf(path,"/proc/loadavg");
    int fd = open(path,O_RDONLY);
    if(fd < 0)
    {
        perror("Error while accessing file '/proc/loadavg' ");
        free(path);
        return;
    }

    if(flag==0)
    {
        printf("Newborn :\n");
    }

    char* buff = (char*)malloc(64);
    int szr = read(fd,buff,74);
    int index = szr-1;
    while(buff[index]!=' ')
    {
        index--;
    }
    printf("%s",buff+index);
    free(path);

}

int check_keydown()
{
    struct termios o_at, n_at;
    int for_ret;

    int check_key;
    check_key = tcgetattr(0, &o_at);
    if(check_key == -1)
    {
        perror("Keydown Problem");
    }
    else if (check_key == 0)
    {
        n_at = o_at;
        int temp = ~(ICANON | ECHO);
        temp = n_at.c_lflag & temp;
        n_at.c_lflag = temp;

        tcsetattr(0, TCSANOW, &n_at);
        ioctl(0, FIONREAD, &for_ret);
        tcsetattr(0, TCSANOW, &o_at);

        if(for_ret <= 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
        
    }
    return 0;
}