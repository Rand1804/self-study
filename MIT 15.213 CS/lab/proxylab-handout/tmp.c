#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000

typedef struct {
    char* key;
    char* value;
} hash_node;

typedef struct {
    hash_node* nodes;
    int size;
} hash_table;

unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

hash_node* create_node(const char* key, const char* value) {
    hash_node* node = malloc(sizeof(hash_node));
    node->key = strdup(key);
    node->value = strdup(value);
    return node;
}

hash_table* create_table(int size) {
    hash_table* table = malloc(sizeof(hash_table));
    table->nodes = calloc(size, sizeof(hash_node));
    table->size = size;
    return table;
}

void put(hash_table* table, const char* key, const char* value) {
    unsigned long index = hash(key) % table->size;
    int i = 1;
    while (table->nodes[index].key != NULL) {
        if (strcmp(table->nodes[index].key, key) == 0) {
            free(table->nodes[index].value);
            table->nodes[index].value = strdup(value);
            return;
        }
        index = (index + i * i) % table->size;
        i++;
    }
    table->nodes[index] = *create_node(key, value);
}

char* get(hash_table* table, const char* key) {
    unsigned long index = hash(key) % table->size;
    int i = 1;
    while (table->nodes[index].key != NULL) {
        if (strcmp(table->nodes[index].key, key) == 0) {
            return table->nodes[index].value;
        }
        index = (index + i * i) % table->size;
        i++;
    }
    return NULL;
}

int main() {
    hash_table* table = create_table(TABLE_SIZE);
    put(table, "hello", "world");
    put(table, "foo", "bar");
    put(table, "cat", "meow");
    put(table, "dog", "woof");
    put(table, "act", "play");
    printf("%s\n", get(table, "hello"));
    printf("%s\n", get(table, "foo"));
    printf("%s\n", get(table, "cat"));
    printf("%s\n", get(table, "dog"));
    printf("%s\n", get(table, "act"));
    return 0;
}