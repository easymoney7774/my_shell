// executor.h
#ifndef EXECUTOR_H
#define EXECUTOR_H

int execute_command(char* args[], int is_background);
int execute_piped_command(char* cmdline);

#endif
