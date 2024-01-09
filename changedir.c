#include "headers.h"

void changedir(char * input,char * def, char * prev,char * b,int y)
{
    // printf("%c\n%s\n%s\n%s\n\n",input[2],def,prev,b);
                char args[20][100];
                char s[100];
                int count=0;
                int c=0;
                int array[20];
                for(int i=0;i<4096;i++)
                {
                    if(input[i]=='\n' || input[i]=='\0')
                    {
                        if(count==0)
                            break;
                        c++;
                        array[c-1]=count;
                        count=0;
                        break;
                    }
                    if((input[i]==' ' && count!=0) || (input[i]=='\t' && count!=0))
                    {
                        c++;
                        array[c-1]=count;
                        count=0;
                        continue;
                    }
                    if(input[i]!=' ' && input[i]!='\t')
                    {
                        args[c][count++]=input[i];
                    }
                }
                // printf("%d\n",c);
                if(c==1)
                {
                    chdir(b);
                    printf("%s\n",b);
                }
                for(;y<c;y++)
                {
                    int flag1=0;
                    int x=0;
                    
                    int startflag=0;
                    if(args[y][0]=='/')
                    {
                        if(!chdir(args[y])==0)
                            {perror("chdir");}
                        else
                        {
                            strcpy(prev,def);
                            getcwd(def, 5000);
                        }
                    }
                    else
                    {
                        int chdirflag=1;
                        while(flag1==0)
                        {   
                            int c=0;
                            char st[5000];
                            for(int i=0;i<5000;i++)
                                st[i]='\000';
                            flag1=1;
                            for(;x<array[y];x++)
                            {
                                if(args[y][x]!='/' || startflag==0)
                                {
                                    c++;
                                    st[c-1]=args[y][x];
                                    startflag=1;
                                }
                                else
                                {
                                    flag1=0;
                                    x++;
                                    break;
                                }
                            }
                            if(st[0]=='-' && c==1)
                            {
                                if(!chdir(prev)==0)
                                    {{perror("chdir");chdirflag&=0;}}
                                else
                                {
                                    // strcpy(prev,def);
                                    // getcwd(def, 5000);
                                    chdirflag&=1;
                                }
                            }
                            else if(st[0]=='.' && c==1)
                            {
                                continue;
                            }
                            else if(st[0]=='.' && st[1]=='.' && c==2)
                            {
                                char currentdir[5000];
                                for(int i=0;i<5000;i++)
                                    currentdir[i]='\000';
                                getcwd(currentdir, sizeof(currentdir));
                                int l=-1;
                                for(int i=0;i<5000;i++)
                                {
                                    if(currentdir[i]=='/')
                                        l=i;
                                    if(currentdir[i]=='\n')
                                        break;
                                }
                                if(l==0)
                                    continue;
                                else
                                {
                                    char string[l+1];
                                    for(int i=0;i<l;i++)
                                        string[i]=currentdir[i];
                                    string[l]='\0';
                                    if(strcmp(string,"/home")==0)
                                        continue;
                                    if(!chdir(string)==0)
                                        {
                                            perror("chdir");
                                            chdirflag&=0;
                                        }
                                    else
                                    {
                                        // strcpy(prev,def);
                                        // getcwd(def, 5000);
                                        chdirflag&=1;
                                    }
                                    // printf("%s\n%s\n",currentdir,string);
                                    char current[5000];
                                    getcwd(current, sizeof(current));
                                    // printf("%s\n",current);
                                }
                            }
                            else if(st[0]!='.')
                            {
                                if(st[0]=='/')
                                {
                                    if(!chdir(st)==0)
                                        {perror("chdir");chdirflag&=0;}
                                    else
                                    {
                                        // strcpy(prev,def);
                                        // getcwd(def, 5000);
                                        chdirflag&=1;
                                    }
                                }
                                else if(st[0]=='~' && c==1)
                                {
                                    if(!chdir(b)==0)
                                        {perror("chdir");chdirflag&=0;}
                                    else
                                    {
                                        // strcpy(prev,def);
                                        // getcwd(def, 5000);
                                        chdirflag&=1;
                                    }
                                }
                                else
                                {
                                    char current[5000];
                                    getcwd(current, sizeof(current));
                                    int i;
                                    for(i=0;i<5000;i++)
                                    {
                                        if(current[i]=='\000')
                                        {
                                            current[i]='/';
                                            break;
                                        }
                                    }
                                    for(int j=0;j<c;j++)
                                    {
                                        current[i+j+1]=st[j];
                                    }
                                    current[i+1+c]='\000';
                                    if(!chdir(current)==0)
                                        {perror("chdir");chdirflag&=0;}
                                    else
                                    {
                                        // strcpy(prev,def);
                                        // getcwd(def, 5000);
                                        chdirflag&=1;
                                    }
                                }
                                char current[5000];
                                getcwd(current, sizeof(current));
                                // printf("%s\n",current);
                            }
                        } 
                        if(chdirflag==1)
                        {
                            strcpy(prev,def);
                            getcwd(def, 5000);
                        }
                        else
                        {
                            chdir(def);
                        }
                    }
                    char dummy[5000];
                    for(int i=0;i<5000;i++)
                        dummy[i]='\000';
                    getcwd(dummy,5000);
                    if(args[0][0]=='w' && args[0][1]=='a' && args[0][2]=='r' && args[0][3]=='p')
                        printf("%s\n",dummy); 
                }  
}

