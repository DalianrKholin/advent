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

void exeOne(char* file){
    register int32_t result = 0;
    int8_t count=0;
    int32_t lineArg=0;
    int32_t line;
    for (int i = 0;; ++i) {
        putchar(file[i]);
        if (file[i]=='\n' ||file[i]=='\0' ){
            line++;
            if (count==1){
                lineArg+=(lineArg/10);
            }
            result+= lineArg;
            count=0;
            printf("dane: %d, wynik %d\n",lineArg,result);
            if (file[i]=='\0') break;
            continue;
        }
        if(file[i]<'0'|| file[i]>'9'){
            continue;
        }
        if(count==0){
            lineArg=(file[i]-'0')*10;

        }else{
            lineArg-= lineArg%10;
            lineArg+= (file[i]-'0');
        }
        count++;
    }
    printf("wynik := %d %d\n",result,line);
}

int32_t isNumer(char* word,int32_t *temp){
    char *s="ofstenz";
    char buff[6]={0};
    char *par;
    strncpy(buff,word,1);
    if((par =strpbrk(buff,s))==NULL){
        return 0;
    }
    strncpy(buff,word,5);
    switch (*par) {
        case 'z':
            buff[4]='\0';
            if (strcmp(buff,"zero")==0){
                *temp=0;
                return 1;
            }

            break;
        case 'o':
            buff[3]='\0';
            if (strcmp(buff,"one")==0){
                *temp=1;
                return 1;
            }
            break;
        case 'f':
            buff[4]='\0';
            if (strcmp(buff,"five")==0){
                *temp=5;
                return 1;
            }
            if (strcmp(buff,"four")==0){
                *temp=4;
                return 1;
            }
            break;
        case 's':
            if (strcmp(buff,"seven")==0){
                *temp=7;
                return 1;
            }
            buff[3]='\0';
            if (strcmp(buff,"six")==0){
                *temp=6;
                return 1;
            }
            break;
        case 't':
            if (strcmp(buff,"three")==0){
                *temp=3;
                return 1;
            }
            buff[3]='\0';
            if (strcmp(buff,"two")==0){
                *temp=2;
                return 1;
            }
            break;
        case 'e':
            if (strcmp(buff,"eight")==0){
                *temp=8;
                return 1;
            }
            break;
        case 'n':
            buff[4]='\0';
            if (strcmp(buff,"nine")==0){
                *temp=9;
                return 1;
            }
            break;

    }
    return 0;
}

void exeTwo(char* file){
    register int32_t result = 0;
    int8_t count=0;
    int32_t lineArg=0;
    int32_t line;
    int32_t temp;
    for (int i = 0;; ++i) {
        if (file[i]=='\n' ||file[i]=='\0' ){
            line++;
            if (count==1){
                lineArg+=(lineArg/10);
            }
            result+= lineArg;
            count=0;
            if (file[i]=='\0') break;
            continue;
        }
        int8_t ok=0;

        if(isNumer(&file[i],&temp)){
            ok=1;
        }
        if(!ok&&(file[i]<'0'|| file[i]>'9')){
            continue;
        }
        temp = ok==0? file[i]-'0' : temp;
        if(count==0){
            lineArg=(temp)*10;

        }else{
            lineArg-= lineArg%10;
            lineArg+= temp;
        }
        count++;
    }
    printf("wynik := %d %d\n",result,line);
}

int main(){

    int32_t fd = Open("/home/dalinarkholin/Uczelnia/cShit/adventOfCode/day1/data",O_RDONLY,0);
    struct stat st;
    fstat(fd,&st);
    ftruncate(fd,st.st_size+10);
    char *file = mmap(NULL, st.st_size+10,PROT_READ,MAP_PRIVATE,fd,0);
    exeOne(file);
    exeTwo(file);
}
