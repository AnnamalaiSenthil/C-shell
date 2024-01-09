#include "headers.h"


int read_line(const char *filename, const char *search, char *result, size_t result_size) 
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search)) {
            fclose(file);
            strncpy(result, line + strlen(search), result_size);
            return 0;
        }
    }

    fclose(file);
    return -1;
}

int countTokens(const char *str, const char *delimiters) 
{
    int count = 0;
    char *copy = strdup(str); // Create a copy to avoid modifying the original

    char *token = strtok(copy, delimiters);
    while (token != NULL) {
        count++;
        token = strtok(NULL, delimiters);
    }

    free(copy); // Free the memory allocated for the copy
    return count;
}


void peekfn(char *input,char *def,char *prev,char *b)
{
                char prevbackup[5000];
                strcpy(prevbackup,prev);
                char args[20][5000];
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
                int num=0;
                int q=1;
                while(q<c && args[q][0]=='-')
                {
                    for(int j=0;j<array[q];j++)
                    {
                        if(args[q][j]=='a')
                            num|=2;
                        else if(args[q][j]=='l')
                            num|=1;
                    }
                    q++;
                }
                // printf("%d\n",num);
                

                char z[5000];
                getcwd(z,5000);
                if(q!=c)
                    changedir(input,def,prev,b,c-1);
                char current[5000];
                for(int i=0;i<5000;i++)
                    current[i]='\000';
                getcwd(current,5000);
                // DIR *dir = opendir(current);
                // if (dir == NULL) 
                // {
                //     perror("opendir");
                // }
                struct dirent **entry;
                const char *dir_path = ".";
                int entry_count = scandir(dir_path, &entry, NULL, alphasort);
                for(int i=0;i<entry_count;i++)
                {
                    if (num<=1 && entry[i]->d_name[0] == '.')
                        continue;
                    char path[6000];
                    snprintf(path, sizeof(path), "%s/%s", current, entry[i]->d_name);

                    struct stat fileStat;
                    if (stat(path, &fileStat) == -1) {
                        perror("stat");
                        continue;
                    }
                    if(num%2==1)
                    {
                        printf("%s", (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                        printf("%c%c%c%c%c%c%c%c%c%c ",
                            (fileStat.st_mode & S_IRUSR) ? 'r' : '-',
                            (fileStat.st_mode & S_IWUSR) ? 'w' : '-',
                            (fileStat.st_mode & S_IXUSR) ? 'x' : '-',
                            (fileStat.st_mode & S_IRGRP) ? 'r' : '-',
                            (fileStat.st_mode & S_IWGRP) ? 'w' : '-',
                            (fileStat.st_mode & S_IXGRP) ? 'x' : '-',
                            (fileStat.st_mode & S_IROTH) ? 'r' : '-',
                            (fileStat.st_mode & S_IWOTH) ? 'w' : '-',
                            (fileStat.st_mode & S_IXOTH) ? 'x' : '-',
                            (S_ISDIR(fileStat.st_mode) && (fileStat.st_mode & S_ISVTX)) ? 't' : '-'
                        );

                        struct passwd *user = getpwuid(fileStat.st_uid);
                        struct group *group = getgrgid(fileStat.st_gid);

                        printf("%s %s ", (user != NULL) ? user->pw_name : "unknown", (group != NULL) ? group->gr_name : "unknown");
                        printf("%8lld ", (long long)fileStat.st_size);

                        char date[80];
                        strftime(date, sizeof(date), "%b %d %H:%M", localtime(&fileStat.st_mtime));
                        printf("%s ", date);
                    }
                    if(S_ISDIR(fileStat.st_mode))
                        printf("\033[34m""%s\n""\033[0m", entry[i]->d_name);
                    else if(fileStat.st_mode & S_IXOTH)
                        printf("\033[32m""%s\n""\033[0m", entry[i]->d_name);
                    else
                        printf("%s\n", entry[i]->d_name);
                }
                // closedir(dir);
                chdir(z);
                strcpy(prev,prevbackup);
}

void proclore(char * input,char * def,char* prev, char * b)
{
                char args[20][5000];
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
                if(c==1)
                {
                    pid_t pgid = getpgid(getpid());
                    char exe_path[1024];
                    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
                    if (len != -1) {
                        exe_path[len] = '\0';
                    } else {
                        perror("readlink");
                        // return 1;
                    }
                    char vm_usage_str[64];
                    if (read_line("/proc/self/status", "VmRSS:", vm_usage_str, sizeof(vm_usage_str)) == -1) {
                        perror("read_line");
                        // return 1;
                    }
                    unsigned long vm_usage = strtoul(vm_usage_str, NULL, 10);
                    char proc_status[8];
                    if (read_line("/proc/self/status", "State:", proc_status, sizeof(proc_status)) == -1) {
                        perror("read_line");
                        // return 1;
                    }
                    FILE *status_file = fopen("/proc/self/status", "r");
                    char line[256];
                    char process_status = '\0';  // Initialize with null character

                    while (fgets(line, sizeof(line), status_file)) {
                        if (strncmp(line, "State:", 6) == 0) {
                            process_status = line[7];  // Extract the status character
                            break;
                        }
                    }
                    char newpath[256];
                    newpath[0]='~';
                    int counter=1;
                    int flag=0;
                    for(int i=0;i<256;i++)
                    {
                        if(b[i]=='\0')
                            flag=1;
                        if(exe_path[i]=='\0' && b[i]!='\0')
                        {
                            strcpy(newpath,exe_path);
                            break;
                        }
                        if(flag==1)
                        {
                            if(exe_path[i]!='\0')
                                newpath[counter++]=exe_path[i];
                            else
                                break;
                        }
                    }
                    newpath[counter]='\0';
                    fclose(status_file);
                    printf("pid : %d\n",getpid());
                    printf("process Status : %c", process_status);
                    if(getpgid(getpid())==tcgetpgrp(STDIN_FILENO))
                        printf("+\n");
                    else
                        printf("\n");
                    printf("Process Group : %d\n", pgid);
                    printf("Virtual Memory : %lu \n", vm_usage);
                    printf("Executable Path: %s\n", newpath);
                }
                else
                {
                    int num=atoi(args[1]);
                    // printf("%d",num);
                    char proc_path[256];
                    snprintf(proc_path, sizeof(proc_path), "/proc/%d/", num);
                    // FILE *pgroup_file = fopen(strcat(proc_path, "exe"), "r");
                    strcat(proc_path, "exe");
                    // fclose(pgroup_file);
                    char status_path[256];
                    snprintf(status_path, sizeof(status_path), "/proc/%d/status", num);

                    FILE *status_file = fopen(status_path, "r");
                    if(status_file==NULL)
                    {
                        perror("fopen");
                        return ;
                    }
                    char line[256];
                    char process_status = ' ';
                    while (fgets(line, sizeof(line), status_file)) {
                        if (strncmp(line, "State:", 6) == 0) {
                            process_status = line[7];  // Extract the status character
                            break;
                        }
                    }
                    fclose(status_file);
                    char mem_path[256];
                    snprintf(mem_path, sizeof(mem_path), "/proc/%d/status", num);

                    FILE *mem_file = fopen(mem_path, "r");
                    if (mem_file == NULL) {
                        perror("Failed to open mem file");
                        return;
                    }
                    char vm_usage_str[64];
                    while (fgets(line, sizeof(line), mem_file)) {
                        if (strncmp(line, "VmRSS:", 6) == 0) {
                            strcpy(vm_usage_str, line + 7);  // Extract the VmRSS value
                            break;
                        }
                    }
                    fclose(mem_file);
                    char exe_path[1024];
                    for(int i=0;i<1024;i++)
                        exe_path[i]='\000';
                    // exe_path[0]='';
                    printf("%s\n",proc_path);
                    ssize_t len = readlink(proc_path, exe_path, 1024);
                    printf("%s\n",exe_path);
                    char newpath[256];
                    newpath[0]='~';
                    int counter=1;
                    int flag=0;
                    for(int i=0;i<256;i++)
                    {
                        if(b[i]=='\0')
                            flag=1;
                        if(exe_path[i]=='\0' && b[i]!='\0')
                        {
                            strcpy(newpath,exe_path);
                            break;
                        }
                        if(flag==1)
                        {
                            if(exe_path[i]!='\0')
                                newpath[counter++]=exe_path[i];
                            else
                                break;
                        }
                    }
                    newpath[counter]='\0';
                    printf("pid : %d\n",num);
                    printf("process Status : %c", process_status);
                    if(getpgid(getpid())==tcgetpgrp(STDIN_FILENO))
                        printf("+\n");
                    else
                        printf("\n");
                    printf("Process Group : %d\n", getpgid(num));
                    printf("Virtual Memory : ");
                    for(int k=0;k<64;k++)
                        if(vm_usage_str[k]<='9' && vm_usage_str[k]>='0')
                            printf("%c",vm_usage_str[k]);
                    printf("\n");
                    printf("Executable Path: %s\n", newpath);
                }
}

void pastevents(char * input,char * def,char* prev, char * b,char ** filedata,int * time,int * background)
{
                char args[20][5000];
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
                if(c==1)
                {
                    for(int i=14;i>=0;i--)
                    {
                        printf("%s",filedata[i]);
                    }
                }
                if(c==2)
                {
                    if(args[1][0]=='p' && args[1][1]=='u' && args[1][2]=='r' && args[1][3]=='g' && args[1][4]=='e')
                    {
                        for(int i=0;i<15;i++)
                        {
                            for(int j=0;j<1000;j++)
                                filedata[i][j]='\000';
                        }
                    }
                }
                if(c==3)
                {
                    int v=atoi(args[2]);
                    if(v>15)
                        printf("InVaLiD InPuT\n");
                    else
                    {
                        if(filedata[v-1][0]=='\000')
                            printf("INVALID\n");
                        else
                        {
                            char inpcopy[4096];
                            char inp[4096];
                            strcpy(inp,filedata[v-1]);
                            strcpy(inpcopy,filedata[v-1]);
                            pseudomain(inp,inpcopy,def,prev,b,time,background);
                        }
                    }
                }

}

int rec(char * search,int x,int flagset,int *d,int *f,char * address)
{
                struct dirent **entry;
                const char *dir_path = ".";
                char current[1000];
                getcwd(current,1000);
                int entry_count = scandir(dir_path, &entry, NULL, alphasort);
                for(int i=0;i<entry_count;i++)
                {
                    if (entry[i]->d_name[0] == '.')
                        continue;
                    char path[6000];
                    snprintf(path, sizeof(path), "%s/%s", current, entry[i]->d_name);

                    struct stat fileStat;
                    if (stat(path, &fileStat) == -1) {
                        perror("stat");
                        continue;
                    }
                    if(S_ISDIR(fileStat.st_mode))
                    {
                        // printf("\033[34m""%s\n""\033[0m", entry[i]->d_name);
                        chdir(entry[i]->d_name);
                        char dummy[1000];
                        getcwd(dummy,1000);
                        // printf("\033[34m""%s\n""\033[0m", dummy);
                        if(flagset&1 && strcmp(entry[i]->d_name,search)==0)
                        {
                            x++;
                            char add[1000];
                            for(int i=0;i<1000;i++)
                                add[i]='\000';
                            for(int i=0;i<1000;i++)
                            {
                                if(dummy[i]!='\000' || dummy[i]!='\0')
                                    add[i]=dummy[i];
                                else
                                {
                                    add[i]=dummy[i];
                                    break;
                                }
                            }
                            printf("\033[34m""%s\n""\033[0m", add);
                            // printf("Hello%s\n%s\n",add,dummy);
                            (*d)++;
                            strcpy(address,dummy);
                        }
                        
                        x=rec(search,x,flagset,d,f,address);
                        chdir("..");
                    }
                    else
                    {
                        if(flagset&2 && strcmp(entry[i]->d_name,search)==0)
                        {
                            x++;
                            char dummy[1000];
                            getcwd(dummy,1000);
                            strcat(dummy,"/");
                            strcat(dummy,entry[i]->d_name);
                            (*f)++;
                            strcpy(address,dummy);
                            char add[1000];
                            for(int i=0;i<1000;i++)
                                add[i]='\000';
                            for(int i=0;i<1000;i++)
                            {
                                if(dummy[i]!='\000' || dummy[i]!='\0')
                                    add[i]=dummy[i];
                                else
                                {
                                    add[i]=dummy[i];
                                    break;
                                }
                            }
                            if(fileStat.st_mode & S_IXOTH)
                                printf("\033[32m""%s\n""\033[0m", add);
                            else
                                printf("%s\n", add);
                        }
                    }
                }
                return x;
}

void seek(char * input,char * def,char* prev, char * b)
{
                char args[20][5000];
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
                int flagset=0;
                int x=2;
                while(x<c && args[x-1][0]=='-')
                {
                    int q=0;
                    for(int i=1;i<array[x-1];i++)
                    {
                        if(args[x-1][i]=='d')
                            flagset|=1;
                        else if(args[x-1][i]=='f')
                            flagset|=2;
                        else if(args[x-1][i]=='e')
                            flagset|=4;
                        else
                        {
                            q=1;
                            break;
                        }
                    }
                    if(q==1)
                        break;
                    x++;
                }
                if(flagset%4==3)
                {
                    printf("Invalid flags\n");
                    return;
                }
                if(flagset==4 || flagset==0)
                    flagset+=3;
                char search[1000];
                char dest[1000];
                if(c>=x)
                {
                    strcpy(search,args[x-1]);
                    if(c>=x+1)
                    {
                        strcpy(dest,args[x]);
                    }
                }
                else
                {
                    printf("Invalid input\n");
                    return;
                }
                
                char prevbackup[1000];
                char curbackup[1000];
                strcpy(prevbackup,prev);
                strcpy(curbackup,def);
                if(dest[0]=='\000')
                {
                    dest[0]='.';
                    dest[1]='\000';
                    strcat(input," ");
                    strcat(input,dest);
                    c++;
                }
                changedir(input,def,prev,b,c-1);
                char cu[1000];
                // getcwd(cu,1000);
                // printf("%s\n",cu);
                // chdir(dest);
                    // printf("Error\n");
                char address[1000];
                // printf("%s\t%s\n",search,dest);
                int d=0,f=0;
                int y= rec(search,0,flagset,&d,&f,address);
                if(y==0)
                {
                    printf("No match found!\n");
                }
                else if(flagset>=4 && y==1 && d==1 && f==0)
                {
                    if(access(address, X_OK) == 0) // | R_OK
                    { 
                        getcwd(prev,5000);
                        chdir(address);
                        // printf("***%s***\n",address);
                        return;
                    }
                    else
                    {
                        printf("Missing permissions for task!\n");
                    }
                }
                else if(flagset>=4 && y==1 && d==0 && f==1)
                {
                    if(access(address, R_OK) == 0) // | R_OK
                    {
                        FILE * filer=fopen(address,"r");
                        char *buffer = NULL;
                        size_t buffer_size = 0;
                        ssize_t characters_read;

                        while ((characters_read = getline(&buffer, &buffer_size, filer)) != -1) {
                            printf("%s", buffer); // Print the read line
                        }
                    }
                    else
                    {
                        printf("Missing permissions for task!\n");
                    }
                }
                chdir(curbackup);
                strcpy(prev,prevbackup);
}

int process(char *input,char * def, char * prev, char * b,char ** filedata,int * time,int * background)
{
                int t=0;
                while(input[t]==' ' || input[t]=='\t')
                    t++;
                if((input[t]=='w' && input[1+t]=='a' && input[2+t]=='r' && input[3+t]=='p') || (input[t]=='c' && input[1+t]=='d'))
                {
                    changedir(input,def,prev,b,1);
                }
                else if(input[0+t]=='p' && input[1+t]=='e' && input[2+t]=='e' && input[3+t]=='k')
                {
                    peekfn(input,def,prev,b);
                }
                else if(input[t+0]=='p' && input[t+1]=='r' && input[t+2]=='o' && input[t+3]=='c')
                {
                    proclore(input,def,prev,b);
                }
                else if(input[t]=='p' && input[t+1]=='a' && input[t+2]=='s' && input[t+3]=='t' && input[t+4]=='e')
                {
                    pastevents(input,def,prev,b,filedata,time,background);
                    return 1;
                }
                else if(input[t]=='s' && input[t+1]=='e' && input[t+2]=='e' && input[t+3]=='k')
                {
                    seek(input,def,prev,b);
                }
                else
                {
                    pid_t pid = fork();
                    if (pid == 0) 
                    {
                        char *args[] = { "/bin/sh", "-c", input, NULL };
                        execvp("/bin/sh", args);
                    }
                    else
                    { // Parent process
                        int status;
                        waitpid(pid, &status, 0);
                    }
                }
                return 0;
}

void pseudomain(char * inp,char * inpcopy,char * def,char * prev,char * b,int * time,int * background)
{
        char delimiters[]=";";
        char * dummy1;
        // int time=0;
        int counter2=countTokens(inp,delimiters);
        char *inpu = strtok_r(inp, delimiters,&dummy1);
        FILE *file = fopen("file.txt", "r");
        char buffer[5000];
        for(int i=0;i<5000;i++)
            buffer[i]='\000';
        int bytesRead = fread(buffer, 1, 5000, file);
        // printf("%s******\n",buffer);
        int file_size=0;
        for(file_size=0;file_size<5000;file_size++)
        {
            if(buffer[file_size]=='\000')
                break;
        }
        int linecount=0,lettercount=0;
        char **filedata=malloc(sizeof(char*)*15);
        for(int i=0;i<15;i++)
            filedata[i]=malloc(sizeof(char)*1000);
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<1000;j++)
                filedata[i][j]='\000';
        }
        for(int i=0;i<file_size;i++)
        {
            if(buffer[i]=='\n')
            {
                filedata[linecount][lettercount++]=buffer[i];
                linecount++;
                lettercount=0;
            }
            else
            {
                filedata[linecount][lettercount++]=buffer[i];
            }
        }
        int pastflag=0;
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        while (inpu!=NULL)
        {
            counter2--;
            char del[]="&";
            char * dummy2;
            int numTokens = countTokens(inpu, del);
            char *input = strtok_r(inpu, del,&dummy2);
            // printf("%d\n",numTokens);
            int counter=0;
            // printf("%d\n",numTokens);
            while (input != NULL && counter<numTokens)
            {
                // printf("%s****\n",input);
                struct timespec start, end;
                double elapsed_seconds;
                clock_gettime(CLOCK_MONOTONIC, &start);
                pid_t p1=1;
                int flag=0;
                if(counter+1!=numTokens)
                {
                    // printf("******%s*****\n",input);
                    p1=fork();
                    flag=1;
                }
                counter++;
                if(p1==0)
                {
                    // counter++;
                    if (input[0]!='\0')
                    {
                        // pastflag=process(input,def,prev,b,filedata,time);
                        char *args[] = { "/bin/sh", "-c", input, NULL };
                        execvp("/bin/sh", args);
                        printf("background process successfully executed\n");
                    }
                    
                }
                else if(flag==1)
                {
                    printf("%d\n",p1);
                    int i;
                    for(i=0;i<100;i++)
                    {
                        if(background[i]==-1)
                            break;
                    }
                    background[i]=p1;
                }
                else if(flag==0)
                {
                    pastflag=process(input,def,prev,b,filedata,time,background);
                    int status;
                    waitpid(p1,&status,WNOHANG);
                }
                // else
                //     exit(0);
                clock_gettime(CLOCK_MONOTONIC, &end);
                elapsed_seconds = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec) / 1000000000.0;
                *time=(int)(elapsed_seconds);
                if(elapsed_seconds-*time>=0.5)
                    (*time)++;
                input = strtok_r(NULL, del,&dummy2);
            }
            inpu = strtok_r(NULL, delimiters,&dummy1);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////
        }
                char args[20][5000];
                int array[20];
                for(int i=0;i<20;i++)
                {
                    array[i]=0;
                    for(int j=0;j<5000;j++)
                        args[i][j]='\000';
                }
                char s[100];
                int count=0;
                int c=0;
                
                // printf("%s",inpcopy);
                for(int i=0;i<4096;i++)
                {
                    if(inpcopy[i]=='\n' || inpcopy[i]=='\0')
                    {
                        if(count==0)
                            break;
                        c++;
                        array[c-1]=count;
                        count=0;
                        break;
                    }
                    if((inpcopy[i]==' ' && count!=0) || (inpcopy[i]=='\t' && count!=0))
                    {
                        c++;
                        array[c-1]=count;
                        count=0;
                        continue;
                    }
                    if(inpcopy[i]!=' ' && inpcopy[i]!='\t')
                    {
                        if(inpcopy[i]==';')
                        {
                            c++;
                            array[c-1]=count;
                            count=0;
                            args[c][count++]=inpcopy[i];
                            c++;
                            array[c-1]=1;
                            count=0;
                        }
                        else
                            args[c][count++]=inp[i];
                    }
                }
        char inputstring[1000];
        for(int i=0;i<1000;i++)
            inputstring[i]='\000';
        for(int i=0;i<c;i++)
        {
            strcat(inputstring,args[i]);
            if(i!=c)
                strcat(inputstring," ");
        }
        if(pastflag==0)
        {
            int fl=0;
            for(int i=0;i<strlen(inputstring);i++)
            {
                if(inputstring[i]!=filedata[0][i] || filedata[0][i]=='\0')
                {
                    fl=1;
                    break;
                }
            }
            if(filedata[0][strlen(inputstring)]!='\0');
            strcat(inputstring,"\n");
            if(fl==1)
            {
                for(int j=13;j>=0;j--)
                {
                    for(int k=0;k<1000;k++)
                    {
                        filedata[j+1][k]=filedata[j][k];
                        filedata[j][k]='\000';
                    }
                }
                for(int i=0;i<1000;i++)
                {
                    filedata[0][i]=inputstring[i];
                }
            }
        }
        fclose(file);
        FILE *file1 = fopen("file.txt", "w");
        
        for(int i=0;i<15;i++)
        {
            int flag=0;
            fprintf(file1,"%s",filedata[i]);
        }
        fclose(file1);
}

int main()
{
    // Keep accepting commands
    char * currentdir=malloc(sizeof(char)*5000);
    for(int i=0;i<5000;i++)
        currentdir[i]='\000';
    char b[5000];
    for(int i=0;i<5000;i++)
        b[i]='\000';
    char def[5000];
    for(int i=0;i<5000;i++)
        def[i]='\000';
    char prev[5000];
    for(int i=0;i<5000;i++)
        prev[i]='\000';
    getcwd(b, 5000);
    getcwd(prev, 5000);
    getcwd(def, 5000);
    int background[100];
    for(int i=0;i<100;i++)
        background[i]=-1;
    int time=0;
    getcwd(currentdir, 5000);
    int n=0;
    for(n=0;n<5000;n++)
    {
        if(currentdir[n]=='\n')
            break;
    }
    n++;
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        prompt(currentdir,n,time);
        char inp[4096];
        for(int i=0;i<4096;i++)
            inp[i]='\000';
        fgets(inp, 4096, stdin);
        for(int i=0;i<100;i++)
        {
            if(background[i]==-1)
                continue;
            int status;
            pid_t result = waitpid(background[i], &status, WNOHANG);
            if(result!=0 && result !=-1)
            {
                printf("Command exited normally (%d)\n",background[i]);
                background[i]=-1;
            }
        }
        char inpcopy[4096];
        for(int i=0;i<4096;i++)
            inpcopy[i]='\000';
        strcpy(inpcopy,inp);
        pseudomain(inp,inpcopy,def,prev,b,&time,background);
    }
}


