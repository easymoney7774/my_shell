#ifndef HISTORY_H
#define HISTORY_H

#define MAX_HISTORY 100

void init_history();
void add_history_entry(const char* cmd);
void print_history();
const char* get_history_entry(int index);  // ✅ 添加这行

#endif
