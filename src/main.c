#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "alias.h"
#include "history.h"
#include "builtin.h"
#include "executor.h"
#include "parser.h"
#include "utils.h"

#define MAX_CMD_LEN 1024
#define MAX_ARG_NUM 64

int main() {
    rl_attempted_completion_function = builtin_completion;
    init_alias();
    init_history();
    print_banner();

    char cmdline[MAX_CMD_LEN];
    char* args[MAX_ARG_NUM];

    while (1) {
        char* input = readline("my_shell$ ");
        if (!input) break;

        if (strlen(input) == 0) {
            free(input);
            continue;
        }

        strncpy(cmdline, input, MAX_CMD_LEN);
        add_history(input);             // readline 自带记录
        add_history_entry(cmdline);     // 自定义 history
        free(input);

        // 去除换行
        cmdline[strcspn(cmdline, "\n")] = '\0';

        // ===== !n 历史命令执行 =====
        if (cmdline[0] == '!' && strlen(cmdline) > 1) {
            int index = atoi(cmdline + 1);
            const char* prev_cmd = get_history_entry(index);
            if (!prev_cmd) {
                printf("无效的历史编号: !%d\n", index);
                continue;
            }
            printf("执行: %s\n", prev_cmd);
            strncpy(cmdline, prev_cmd, MAX_CMD_LEN);
        }

        // ===== 管道命令检测 =====
        if (strchr(cmdline, '|')) {
            execute_piped_command(cmdline);
            continue;
        }

        // ===== 内建命令（alias, cd, history 等） =====
        if (is_builtin_command(cmdline)) {
            if (execute_builtin_command(cmdline)) continue;
        }

        // ===== alias 替换命令名 =====
        char alias_check[1024];
        strncpy(alias_check, cmdline, sizeof(alias_check));
        char* first = strtok(alias_check, " ");
        const char* alias_value = resolve_alias(first);
        if (alias_value) {
            char new_cmdline[1024];
            snprintf(new_cmdline, sizeof(new_cmdline), "%s%s", alias_value, cmdline + strlen(first));
            strncpy(cmdline, new_cmdline, sizeof(cmdline));
        }

        // ===== 参数解析 =====
        parse_args(cmdline, args, MAX_ARG_NUM);

        // ===== 后台命令检测 =====
        int is_background = 0;
        int last = 0;
        while (args[last]) last++;
        if (last > 0 && strcmp(args[last - 1], "&") == 0) {
            is_background = 1;
            args[last - 1] = NULL;
        }

        // ===== 执行外部命令（含重定向） =====
        execute_command(args, is_background);
    }

    return 0;
}
