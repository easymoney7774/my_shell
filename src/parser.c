#include <string.h>
#include "parser.h"

void parse_args(char* cmdline, char* args[], int max_args) {
    int argc = 0;
    char* token = strtok(cmdline, " ");
    while (token && argc < max_args - 1) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;
}
