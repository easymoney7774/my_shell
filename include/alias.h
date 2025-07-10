#ifndef ALIAS_H
#define ALIAS_H

#define MAX_ALIASES 100

typedef struct {
    char name[64];
    char value[256];
} Alias;  // ✅ 类型定义写在头文件中
const char* get_alias_name(int index);

void init_alias();
void add_or_update_alias(const char* name, const char* value);
const char* resolve_alias(const char* name);
void print_aliases();
int remove_alias(const char* name);

#endif
