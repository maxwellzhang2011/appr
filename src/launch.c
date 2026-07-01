#include <unistd.h>
#include "../depend/split.h"
#include "../depend/launch.h"

void launch(char* exec){
    char **command;
    split(&command, exec);
    execvp(command[0], command);
}
