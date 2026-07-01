#include <GL/gl.h>
#include <stdio.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "../depend/load_apps.h"
#include "../depend/launch.h"

int main(){
    //initing the app location
    double xpos, ypos;
    DIR *dir1 = opendir("/usr/share/applications/");
    DIR *dir2 = opendir("/usr/local/share/applications/");
    struct passwd *pw = getpwuid(getuid());
    strcat(pw->pw_dir, "/.local/share/applications/");
    DIR *dir3 = opendir(pw->pw_dir);
    if(dir1 == NULL || dir2 == NULL || dir3 == NULL){
        printf("dir reading error\n");
        return 1;
    }
    unsigned int size = get_size(dir1, dir2, dir3), sizeofcmd, index;
    closedir(dir1);
    closedir(dir2);
    closedir(dir3);

    app softwares[size];
    dir1 = opendir("/usr/share/applications/");
    dir2 = opendir("/usr/local/share/applications/");
    dir3 = opendir(pw->pw_dir);
    load_apps(dir1, dir2, dir3, pw->pw_dir, softwares);

    for(unsigned int i = 0; i < size; i++){
        printf("%s\n", softwares[i].name);
    }

    char buff[256];
    fgets(buff, 256, stdin);
    buff[strcspn(buff, "\n")] = 0;
    for(unsigned int i = 0; i < size; i++){
        if(!strcmp(softwares[i].name, buff)){
            index = i;
            goto launch;
        }
    }
    printf("can't launch: no such option\n");
    return 0;
    launch:
    launch(softwares[index].exec);
    return 0;
}
