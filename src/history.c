#include <stdio.h>
#include <string.h>
#include "history.h"

static char history[MAX_HISTORY][1024];
static int history_count = 0;

void init_history() {
    history_count = 0;
}

void add_history_entry(const char* cmd) {
    if (strlen(cmd) == 0) return;

    if (history_count < MAX_HISTORY) {
        strncpy(history[history_count], cmd, sizeof(history[0]));
        history_count++;
    } else {
        // 滚动记录
        for (int i = 1; i < MAX_HISTORY; i++) {
            strncpy(history[i - 1], history[i], sizeof(history[0]));
        }
        strncpy(history[MAX_HISTORY - 1], cmd, sizeof(history[0]));
    }
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d  %s\n", i + 1, history[i]);
    }
}

const char* get_history_entry(int index) {
    if (index < 1 || index > history_count) return NULL;
    return history[index - 1];
}

int get_history_count() {
    return history_count;
}
