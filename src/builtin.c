#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "builtin.h"
#include "alias.h"
#include "history.h"

#define MAX_BUILTINS 10

// 内建命令列表
static const char* builtin_cmds[] = {
    "cd", "exit", "alias", "history", NULL
};

// 判断是否是内建命令
int is_builtin_command(const char* cmd) {
    for (int i = 0; builtin_cmds[i]; i++) {
        if (strncmp(cmd, builtin_cmds[i], strlen(builtin_cmds[i])) == 0) {
            return 1;
        }
    }
    return 0;
}

// 执行内建命令
int execute_builtin_command(char* cmdline) {
    char* args[64];
    int argc = 0;
    char* token = strtok(cmdline, " ");
    while (token && argc < 63) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    if (argc == 0) return 0;

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    if (strcmp(args[0], "cd") == 0) {
        char* path = args[1];
        if (!path || strcmp(path, "~") == 0)
            path = getenv("HOME");
        if (chdir(path) != 0)
            perror("cd");
        return 1;
    }

    if (strcmp(args[0], "alias") == 0) {
        if (argc == 1) {
            print_aliases();
        } else {
            char name[64], value[256];
            if (sscanf(cmdline + 6, "%[^=]=\'%[^\']\'", name, value) == 2) {
                add_or_update_alias(name, value);
            } else {
                printf("alias 格式错误，示例: alias ll='ls -l'\n");
            }
        }
        return 1;
    }

    if (strcmp(args[0], "history") == 0) {
        print_history();
        return 1;
    }

    return 0;
}

// =================== readline 补全支持 ===================

#include <dirent.h>
#include <sys/stat.h>

// 命令名补全
char* command_generator(const char* text, int state) {
    static int list_index;
    static int len;
    const char* name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = builtin_cmds[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

char** builtin_completion(const char* text, int start, int end) {
    if (start == 0) {
        return rl_completion_matches(text, command_generator);
    }
    return NULL;
}
