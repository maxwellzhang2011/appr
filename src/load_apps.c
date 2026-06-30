#include <stdio.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "../depend/load_apps.h"

unsigned int get_size(DIR *dir1, DIR *dir2, DIR *dir3){
    struct dirent *entry;
    char *name;
    unsigned int size = 0;
    while((entry = readdir(dir1)) != NULL){
        name = entry->d_name;
        if(!strcmp(strlen(name)-8+name, ".desktop")){
            size++;
        } 
    }
    while((entry = readdir(dir2)) != NULL){
        name = entry->d_name;
        if(!strcmp(strlen(name)-8+name, ".desktop")){
            size++;
        }
    }
    while((entry = readdir(dir3)) != NULL){
        name = entry->d_name;
        if(!strcmp(strlen(name)-8+name, ".desktop")){
            size++;
        }
    }
    return size;
}

char* readapp(char* name){
    FILE* file = fopen(name, "r");
    fseek(file, 0, SEEK_END);
    unsigned int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buf = malloc(size);
    fread(buf, 1, size, file);
    return buf;
}

char* getname(char* file){
    char cmp[6];
    unsigned int size = 0;
    char chr;
    for(unsigned int i = 0; i < strlen(file)-4; i++){
        strncpy(cmp, file+i, 5);
        cmp[5] = '\0';
        if(!strcmp(cmp, "Name=")){
            do{
                chr = file[i+size+5];
                size++;
            } while(chr != '\n');
            size--;
            char *out = malloc(size+1);
            strncpy(out, file+i+5, size);
            out[size]='\0';
            return out;
        }
    }
    return NULL;
}

char* getexec(char* file){
    char cmp[6];
    unsigned int size = 0;
    char chr;
    for(unsigned int i = 0; i < strlen(file)-4; i++){
        strncpy(cmp, file+i, 5);
        cmp[5] = '\0';
        if(!strcmp(cmp, "Exec=")){
            do{
                chr = file[i+size+5];
                size++;
            } while(chr != '\n');
            size--;
            char *out = malloc(size+1);
            strncpy(out, file+i+5, size);
            out[size] = '\0';
            return out;
        }
    }
    return NULL;
}

void load_apps(DIR *dir1, DIR *dir2, DIR *dir3, char* base_dir, app softwares[]){
    struct dirent *entry;
    char *file;
    unsigned int softwares_i=0;
    entry = readdir(dir1);
    while((entry = readdir(dir1)) != NULL){
        char name[24+strlen(entry->d_name)];
        strcpy(name, "/usr/share/applications/");
        strcat(name, entry->d_name);
        if(strlen(name) >= 8 && !strcmp(strlen(name)-8+name, ".desktop")){
            file = readapp(name);
            softwares[softwares_i].name = getname(file);
            softwares[softwares_i].exec  = getexec(file);
            softwares_i++;
        } 
    }
    while((entry = readdir(dir2)) != NULL){
        char name[30+strlen(entry->d_name)];
        strcpy(name, "/usr/local/share/applications/");
        strcat(name, entry->d_name);
        if(strlen(name) >= 8 && !strcmp(strlen(name)-8+name, ".desktop")){
            file = readapp(name);
            softwares[softwares_i].name = getname(file);
            softwares[softwares_i].exec  = getexec(file);
            softwares_i++;
        }
    }
    while((entry = readdir(dir3)) != NULL){
        char name[strlen(base_dir)+strlen(entry->d_name)];
        strcpy(name, base_dir);
        strcat(name, entry->d_name);
        if(strlen(name) >= 8 && !strcmp(strlen(name)-8+name, ".desktop")){
            file = readapp(name);
            softwares[softwares_i].name = getname(file);
            softwares[softwares_i].exec  = getexec(file);
            softwares_i++;
        }
    }
}
