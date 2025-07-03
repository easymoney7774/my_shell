#include <stdio.h>
#include "utils.h"

void print_prompt() {
    printf("my_shell$ ");
    fflush(stdout);
}

void print_banner() {
    printf("========== My Shell ==========\n");
    printf("Type 'exit' to quit.\n");
}
