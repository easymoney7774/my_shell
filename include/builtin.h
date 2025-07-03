// builtin.h
#ifndef BUILTIN_H
#define BUILTIN_H

#define MAX_BUILTINS 10

// 检查是否是内建命令
int is_builtin_command(const char* cmd);

// 执行内建命令（返回 1 表示已执行，不需要继续处理）
int execute_builtin_command(char* cmdline);

// 给 readline 用的补全函数
char** builtin_completion(const char* text, int start, int end);

#endif
