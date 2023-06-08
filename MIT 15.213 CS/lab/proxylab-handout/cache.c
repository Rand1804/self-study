#include "csapp.h"
#include "cache.h"


/* $begin hash */
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c*/
    }

    return hash;
}


hash_table *create_hash_table(unsigned size)
{
    hash_table *table = malloc(sizeof(hash_table));
    table->entries = calloc(size, sizeof(hash_table_entry));
    table->size = size;

    return table;
}


void set_value(hash_table *table, char *key, char *value)
{
    unsigned long hashed_key = hash(key);
    int index = hashed_key % table->size;
    
    hash_table_entry *entry = table->entries[index];
    while ((entry != NULL) && (entry->key != hashed_key))
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
    while (entry != NULL && entry->key != hashed_key) {
        entry = entry->next;
    }

    if (entry == NULL) {
        return NULL;
    } else {
        return entry->value;
    }
}

/* $end hash */


typedef struct queue_node {
    struct queue_node *prev, *next;
    char *context;
} queue_node;

typedef struct {
    unsigned counter;
    unsigned size;
    queue_node *front, *rear;
} Queue;


Queue *create_queue(unsigned size) {
    Queue *temp = malloc(sizeof(Queue));
    temp->size = size;
    temp->front = temp->rear = NULL;
    
    return temp;
}

queue_node *new_queue_node(char *context) {
    queue_node *temp = malloc(sizeof(queue_node));
    temp->context = context;
    temp->prev = temp->next = NULL;

    return temp;
}

static inline AreAllFramesFull(Queue *queue) {
    return queue->counter == queue->size;
}

static inline isQueueEmpty(Queue *queue) {
    return queue->rear == NULL;
}


void deQueue(Queue *queue) {
    if (isQueueEmpty(queue))
        return;
    // If this is the only node in list
    if (queue->front == queue->rear)
        queue->front = NULL;
    
    queue_node *temp = queue->rear;
    queue->rear = queue->rear->prev;

    if (queue->rear)
        queue->rear->next = NULL;
    free(temp);

    queue->counter--;
}


void enQueue()

int main()
{   
    hash_table *table = create_hash_table(4);

    set_value(table, "hello", "world");
    set_value(table, "foo", "bar");

    printf("Value of 'hello': %s\n", get_value(table, "hello"));
    printf("Value of 'foo': %s\n", get_value(table, "foo"));

    return 0;
}