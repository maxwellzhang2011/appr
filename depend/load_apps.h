#ifndef LOAD_APPS_H
#define LOAD_APPS_H

#include <dirent.h>

typedef struct{
    char *name;
    char *exec;
} app;

void load_apps(DIR *dir1, DIR *dir2, DIR *dir3, char* base_dir, app softwares[]);
unsigned int get_size(DIR *dir1, DIR *dir2, DIR *dir3);

#endif
