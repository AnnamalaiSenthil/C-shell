#include "headers.h"


int prompt(char * dir,int n,int time)
{
    if (1) 
    {
        char tim[20];
        for(int i=0;i<20;i++)
            tim[i]='\000';
        if(time>=2)
        {
            snprintf(tim,20," sleep : %ds",time);
        }
        char buffer[5000];
        for(int i=0;i<n;i++)
        {
            buffer[i]=dir[i];
        }
        char host_name[256];
        if (gethostname(host_name, sizeof(host_name)) == 0) 
        {
            
            char *user_name = getlogin();
            if (user_name != NULL) 
            {
                // Actual Code
                
                char currentdir[5000];
                getcwd(currentdir, sizeof(currentdir));
                if(strcmp(currentdir,buffer)==0)
                {
                    // printf("Hello World\n");
                    printf("<%s@%s:~%s> ",user_name,host_name,tim);
                }
                else
                {
                    // int l=0;
                    // for(int i=0;i<5000;i++)
                    // {
                    //     if(buffer[i]=='\0')
                    //     {
                    //         l=i-1;
                    //         break;
                    //     }
                    // }
                    int bufferlen=n;
                    int l=0;
                    for(int i=0;i<5000;i++)
                    {
                        if(currentdir[i]=='\n')
                        {
                            l=i;
                            break;
                        }
                    }
                    if(l<bufferlen)
                        printf("<%s@%s:%s%s> ",user_name,host_name,currentdir,tim);
                    else
                    {
                        int flag=0;
                        for(int i=0;i<n;i++)
                            if(currentdir[i]!=buffer[i])
                                flag=1;
                        if(flag==0)
                        {
                            printf("<%s@%s:~%s",user_name,host_name,tim);
                            for(int i=bufferlen;i<l;i++)
                                printf("%c",currentdir[i]);
                            printf("> ");
                        }
                        else
                            printf("<%s@%s:%s%s> ",user_name,host_name,currentdir,tim);
                    }
                }
            } 
            else 
            {
                perror("getlogin");
                return 1;
            }
        } 
        else 
        {
            perror("gethostname");
            return 1;
        }
    } 
    else 
    {
        perror("getcwd");
        return 1;
    }
}


