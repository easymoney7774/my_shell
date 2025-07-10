#include <stdio.h>
#include <string.h>
#include "alias.h"

static Alias alias_table[MAX_ALIASES];
static int alias_count = 0;

void init_alias() {
    alias_count = 0;
}

void add_or_update_alias(const char* name, const char* value) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_table[i].name, name) == 0) {
            strncpy(alias_table[i].value, value, sizeof(alias_table[i].value));
            return;
        }
    }
    if (alias_count < MAX_ALIASES) {
        strncpy(alias_table[alias_count].name, name, sizeof(alias_table[alias_count].name));
        strncpy(alias_table[alias_count].value, value, sizeof(alias_table[alias_count].value));
        alias_count++;
    }
}

const char* resolve_alias(const char* name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_table[i].name, name) == 0) {
            return alias_table[i].value;
        }
    }
    return NULL;
}

void print_aliases() {
    for (int i = 0; i < alias_count; i++) {
        printf("alias %s='%s'\n", alias_table[i].name, alias_table[i].value);
    }
}

int remove_alias(const char* name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_table[i].name, name) == 0) {
            for (int j = i; j < alias_count - 1; j++) {
                alias_table[j] = alias_table[j + 1];
            }
            alias_count--;
            return 1;
        }
    }
    return 0;
}
const char* get_alias_name(int index) {
    extern int alias_count;
    extern Alias alias_table[MAX_ALIASES];
    if (index < 0 || index >= alias_count) return NULL;
    return alias_table[index].name;
}
