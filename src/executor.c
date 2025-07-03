#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "executor.h"

#define MAX_ARG_NUM 64

// 将命令行字符串分割为参数数组
void split_command(char* cmd, char* args[]) {
    int argc = 0;
    char* token = strtok(cmd, " ");
    while (token && argc < MAX_ARG_NUM - 1) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;
}

// 处理 I/O 重定向符号
int handle_redirection(char* args[]) {
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], "<") == 0 && args[i + 1]) {
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("无法打开输入文件");
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
            break;
        }
        else if (strcmp(args[i], ">") == 0 && args[i + 1]) {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("无法打开输出文件");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            break;
        }
        else if (strcmp(args[i], ">>") == 0 && args[i + 1]) {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("无法打开输出文件");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            break;
        }
    }
    return 0;
}

// 执行普通命令（支持重定向 + 后台）
int execute_command(char* args[], int is_background) {
    pid_t pid = fork();

    if (pid == 0) {
        // 子进程执行命令
        if (handle_redirection(args) < 0) exit(1);
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        // 父进程处理后台/前台等待
        if (!is_background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[后台进程] PID: %d\n", pid);
        }
        return 0;
    } else {
        perror("fork");
        return -1;
    }
}

// 执行带管道命令（仅支持 cmd1 | cmd2）
int execute_piped_command(char* cmdline) {
    char* pipe_pos = strchr(cmdline, '|');
    if (!pipe_pos) return -1;

    // 拆分左右命令
    *pipe_pos = '\0';
    char* left_cmd = cmdline;
    char* right_cmd = pipe_pos + 1;
    while (*right_cmd == ' ') right_cmd++; // 去除右边空格

    char* args1[MAX_ARG_NUM];
    char* args2[MAX_ARG_NUM];
    split_command(left_cmd, args1);
    split_command(right_cmd, args2);

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // 子进程 1：写入管道
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp(args1[0], args1);
        perror("execvp 左侧");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // 子进程 2：读取管道
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execvp(args2[0], args2);
        perror("execvp 右侧");
        exit(1);
    }

    // 主进程关闭管道并等待两个子进程
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
