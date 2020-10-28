#include "headers.h"
#include "builtin.h"




int ls_cmd(char** curr_ls)
{
    char** direc_ptr = malloc(32*sizeof(char*));
    if(!direc_ptr)
    {
        printf("Memory Allocation Error\n");
        return 0;
    }

    int flag_l= 0, flag_a= 0,direc_count=0,buf_size = 32;
    char dash[1] = "-";
    int h =0 ;
    while (curr_ls[++h] != NULL)
    {
        if(curr_ls[h][0] == dash[0])            //flag
        {
            if(strcmp("-l",curr_ls[h]) == 0 && flag_l == 0)
            {
                flag_l = 1;
            }
            if(strcmp("-a",curr_ls[h]) == 0 && flag_a == 0)
            {
                flag_a = 1;
            }
            if(strcmp("-la",curr_ls[h]) == 0 && (flag_l == 0 || flag_a == 0))
            {
                flag_l =1;
                flag_a =1;
            }
            if(strcmp("-al",curr_ls[h]) == 0 && (flag_l == 0 || flag_a == 0))
            {
                flag_l =1;
                flag_a =1;
            }
        }
        else                                    //directory
        {
            direc_ptr[direc_count++] = curr_ls[h];
            if(direc_count >= buf_size)
            {
                buf_size+=32;
                char** direc_ptr = realloc(direc_ptr,buf_size*sizeof(char*));
                if(!direc_ptr)
                {
                    printf("Memory Allocation Error\nToo much directory\n");
                    return -1;
                }
            }
        }       
    }
    direc_ptr[direc_count]=NULL;

    ls_display(flag_l,flag_a,direc_ptr);

    return 0;
}






void ls_display(int flag_l,int flag_a,char** direc_ptr)
{
    int h = -1;
    char tilda[1] = "~";
    while(direc_ptr[++h]!=NULL)
    {
        if(direc_ptr[h][0] == tilda[0] )
        {
            if(strcmp(direc_ptr[h],"~")==0)
            {
                ls_single_display(flag_l,flag_a,HOME_DIRECTORY);
            }
            else
            {
                char* temp = (char*)malloc(500);
                if(!temp)
                {
                    printf("Memory Allocation Error\n");
                    return ;
                }

                strcpy(temp,HOME_DIRECTORY);
                ls_single_display(flag_l,flag_a,strcat(temp,direc_ptr[h]+1));
                free(temp);
            }
        }
        else
        {
            ls_single_display(flag_l,flag_a,direc_ptr[h]);
        }
    }
    if(h==0)
    {
        char* currentdirec = (char*)malloc(1);
        currentdirec[0] = '.';
        currentdirec[1] = '\0';
        ls_single_display(flag_l,flag_a,currentdirec);
        free(currentdirec);
    }
}






void ls_single_display(int flag_l,int flag_a,char* direc_ptr)
{      

    printf("%s :\n",direc_ptr);

    DIR* dir = opendir(direc_ptr);
    if(dir != NULL)
    {
        struct dirent *de;
        while ((de = readdir(dir)) != NULL)
        {
            if(!flag_a)
            {
                char dot[1] = ".";
                if(de->d_name[0]==dot[0])
                {
                    continue;
                }
                else
                {
                    GLOBAL_DE = de;
                    descriptive_display(flag_l,direc_ptr);
                }
            }
            else
            {
                GLOBAL_DE = de;
                descriptive_display(flag_l,direc_ptr);
            }
            
        }
        
        closedir(dir);
    }
    else
    {
        perror("Directory");
    }
    printf("\n");
}








void descriptive_display(int flag_l,char* direc_ptr)
{
    char* filename = (char*)malloc(300);
    if(!filename)
    {
        printf("Memory Allocation Error\n");
        return;
    }

    strcpy(filename,GLOBAL_DE->d_name);


    if(!flag_l)
    {
        printf("%s\n",filename);
    }
    else
    {
        struct stat sb;
        char permissions[11],username[300],groupname[300],timedisplay[50];
        char* fullpath = (char*)malloc(strlen(direc_ptr)+strlen(filename)+50);
        if(!fullpath)
        {
            printf("Memory Allocation Error\n");
            return;
        }
        

        fullpath = strcpy(fullpath,direc_ptr);        
        fullpath = strcat(fullpath,"/");
        strcat(fullpath,filename);



        if(stat(fullpath, &sb) == -1){
			perror("filename");
			return;
		}

        SB = sb;
        get_file_permission(permissions);
        get_file_username(username);
        get_file_groupname(groupname);
        get_file_time(timedisplay);


        int sz = (int)sb.st_size;
       
        printf("%s %*d %s %s %*d %s %s\n",permissions,4, (int)sb.st_nlink, username, groupname,12, sz, timedisplay, filename);
    }

    free(filename);   
}










void get_file_permission(char* permissions)
{
    for(int i=0;i<10;i++)
    { 
        permissions[i]='-'; 
    }

    if( (SB.st_mode & S_IFMT) == S_IFDIR )
    {
        permissions[0]='d';
    }

    if(SB.st_mode & S_IRUSR)
    {
        permissions[1]='r';
    }
    if(SB.st_mode & S_IWUSR)
    {
        permissions[2]='w';
    }
    if(SB.st_mode & S_IXUSR)
    {
        permissions[3]='x';
    }
    
    if(SB.st_mode & S_IRGRP)
    {
        permissions[4]='r';
    }
    if(SB.st_mode & S_IWGRP)
    {
        permissions[5]='w';
    }
    if(SB.st_mode & S_IXGRP)
    {
        permissions[6]='x';
    }
    
    if(SB.st_mode & S_IROTH)
    {
        permissions[7]='r';
    }
    if(SB.st_mode & S_IWOTH)
    {
        permissions[8]='w';
    }
    if(SB.st_mode & S_IXOTH)
    {
        permissions[9]='x';
    }
    

    permissions[10] = '\0';
}


void get_file_username(char* username)
{
    struct passwd *usernm;
    usernm = getpwuid(SB.st_uid);
    strncpy(username,usernm->pw_name,300);
}


void get_file_groupname(char* groupname)
{
    struct passwd *groupnm;
    groupnm = getpwuid(SB.st_gid);
    strncpy(groupname,groupnm->pw_name,300);
}


void get_file_time(char* timedisplay)
{
    time_t s;
    s = time(NULL);
    int curr_year = localtime(&s)->tm_year;

    struct tm *tmstamp = localtime((time_t*)&SB.st_mtim);
    if(tmstamp->tm_year < curr_year)
    {
        sprintf(timedisplay,"%*d %*d %*d",2,tmstamp->tm_mon,2,tmstamp->tm_mday,5,tmstamp->tm_year);
    }
    else
    {
        if(tmstamp->tm_min < 10)
        {
            sprintf(timedisplay,"%*d %*d %*d:0%*d",2,tmstamp->tm_mon,2,tmstamp->tm_mday,2,tmstamp->tm_hour,1,tmstamp->tm_min);
        }
        else
        {
            sprintf(timedisplay,"%*d %*d %*d:%*d",2,tmstamp->tm_mon,2,tmstamp->tm_mday,2,tmstamp->tm_hour,2,tmstamp->tm_min);
        }
    }
    
}

