//
// Created by dalinarkholin on 12/2/23.
//
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int32_t Open(char* path,int32_t flag, int32_t offset){
    int32_t fd;
    if( (fd=open(path,flag,offset))==-1){
        fprintf(stderr,"cant open file");
        exit(-1);
    }
    return fd;
}
void exeTwo(char *file){
    char buff[256];
    int32_t result = 0;
    for (int i = 1; i <= 100; ++i) {
        int32_t rMin=0;
        int32_t bMin=0;
        int32_t gMin=0;
        char *xd = strchr(file,'\n');
        if (xd==NULL){
            xd = strchr(file,'\0');
        }
        strncpy(buff,file, xd-file);
        char *buffPointer;
        buffPointer = strchr(buff,':')+1;
        char *token = strchr(buffPointer,';');
        for (;token != NULL;) {
            char copy[256] ={0};
            strncpy(copy,buffPointer+1,token-buffPointer-1);
            char *copyPoint = copy;
            while ((copyPoint-2)!=0){
                char nu[5]={};
                strncpy(nu,copyPoint, strchr(copyPoint,' ')- copyPoint);
                int32_t num = atoi(nu);
                switch (*(strchr(copyPoint,' ')+1)) {
                    case 'r':
                        if (num>rMin){
                            rMin=num;
                            break;
                        }
                        break;
                    case 'b':
                        if (num>bMin){
                            bMin=num;
                            break;
                        }
                        break;
                    case 'g':
                        if (num>gMin){
                            gMin=num;
                            break;
                        }
                        break;
                }
                copyPoint=strchr(copyPoint,',')+2;
            }
            buffPointer=token+1;
            token = strchr(buffPointer,';');
        }
        printf("%s\n",buff);
        printf("%d, %d, %d\n", rMin, gMin, bMin);
        result+= (rMin*bMin*gMin);
        file=xd+1;
        for (int j = 0; j < 256; ++j) {
            buff[j]=0;
        }
    }
    printf("%d\n",result);
}


void execOne(char* file){
    char buff[256];
    int result = 0;
    for (int i = 1; i <= 100; ++i) {
        int ok =1;
        char *xd = strchr(file,'\n');
        if (xd==NULL){
            xd = strchr(file,'\0');
        }
        strncpy(buff,file, xd-file);
        printf("%s\n",buff);
        char *buffPointer;
        buffPointer = strchr(buff,':')+1;
        char *token = strchr(buffPointer,';');
        for (;token != NULL && ok;) {
            char copy[256] ={0};
            strncpy(copy,buffPointer+1,token-buffPointer-1);
            printf("%s\n",copy);
            char *copyPoint = copy;
            while ((copyPoint-2)!=0){
                char nu[5]={};
                strncpy(nu,copyPoint, strchr(copyPoint,' ')- copyPoint);
                int32_t num = atoi(nu);
                printf("%d %c\n",num,*(strchr(copyPoint,' ')+1));
                switch (*(strchr(copyPoint,' ')+1)) {
                    case 'r':
                        if (num>12){
                            ok=0;
                            break;
                        }
                        break;
                    case 'b':
                        if (num>14){
                            ok=0;
                            break;
                        }
                        break;
                    case 'g':
                        if (num>13){
                            ok=0;
                            break;
                        }
                        break;
                }

                copyPoint=strchr(copyPoint,',')+2;
            }
            buffPointer=token+1;
            token = strchr(buffPointer,';');
        }
        if (ok){
            result+=i;
        }
        file=xd+1;
        for (int j = 0; j < 256; ++j) {
            buff[j]=0;
        }

    }
    printf("%d\n",result);
}


int main(){
    int32_t fd = Open("/home/dalinarkholin/Uczelnia/cShit/adventOfCode/day2/data",O_RDONLY,0);
    struct stat st;
    fstat(fd,&st);
    char *file = mmap(NULL, st.st_size,PROT_READ,MAP_PRIVATE,fd,0);
    execOne(file);
    exeTwo(file);

}