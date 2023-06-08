#include "csapp.h"


#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
#define NUM_OF_FRAMES 4
#define TABLE_SIZE 4



typedef struct hash_table_entry {
    unsigned long key;
    char *value;
    struct hash_table_entry *next;
} hash_table_entry;


typedef struct {
    unsigned size;
    hash_table_entry **entries;
} hash_table;


hash_table *create_hash_table(unsigned size);












