#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10000

typedef struct hash_table_entry {
    unsigned long key;
    char *value;
    struct hash_table_entry *next;
} hash_table_entry;

typedef struct {
    int size;
    hash_table_entry **entries;
} hash_table;

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

hash_table *create_hash_table() {
    hash_table *table = malloc(sizeof(hash_table));
    table->entries = calloc(TABLE_SIZE, sizeof(hash_table_entry *));
    table->size = TABLE_SIZE;
    return table;
}

void set_value(hash_table *table, char *key, char *value) {
    unsigned long hashed_key = hash(key);
    int index = hashed_key % table->size;

    hash_table_entry *entry = table->entries[index];
    while (entry != NULL && entry->key != hashed_key)
        entry = entry->next;

    if (entry == NULL) {
        entry = malloc(sizeof(hash_table_entry));
        entry->key = hashed_key;
        entry->value = strdup(value);
        entry->next = table->entries[index];
        table->entries[index] = entry;
    } else {
        free(entry->value);
        entry->value = strdup(value);
    }
}

char *get_value(hash_table *table, char *key) {
    unsigned long hashed_key = hash(key);
    int index = hashed_key % table->size;

    hash_table_entry *entry = table->entries[index];
    while (entry != NULL && entry->key != hashed_key)
        entry = entry->next;

    if (entry == NULL) {
        return NULL;
    } else {
        return entry->value;
    }
}

int main() {
    hash_table *table = create_hash_table();

    set_value(table, "hello", "world");
    set_value(table, "foo", "bar");

    printf("Value of 'hello': %s\n", get_value(table, "hello"));
    printf("Value of 'foo': %s\n", get_value(table, "foo"));

    return 0;
}
