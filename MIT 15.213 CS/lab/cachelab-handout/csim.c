#include "cachelab.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// assume address bits 32

typedef struct dNode
{
    unsigned tag;
    struct dNode *next, *prev;
}dNode;

typedef struct dList
{
    int size;
    struct dNode *head, *tail;
}dList;


static int s, E, b;
static int hits, misses, evictions;


void initDList(dList* dListArr, int i)
{
    dListArr[i].head = (dNode*) calloc(1, sizeof(dNode));
    dListArr[i].tail = (dNode*) calloc(1, sizeof(dNode));
    dListArr[i].size = 0;

    dListArr[i].head->next = dListArr[i].tail;
    dListArr[i].tail->prev = dListArr[i].head;
}

void insertNode(dList* curList, dNode* prevNode, unsigned value)
{
    dNode* newNode = (dNode*) malloc(sizeof(dNode));
    newNode->tag = value;

    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    prevNode->next->prev = newNode;
    prevNode->next = newNode;
    
    curList->size++;

}


void deleteNode(dList* curList, dNode* node2del)
{
    node2del->next->prev = node2del->prev;
    node2del->prev->next = node2del->next;

    free(node2del);

    curList->size--;
}

void moveNode(dNode* sourceNode, dNode* objPreNode)
{
    sourceNode->prev->next = sourceNode->next;
    sourceNode->next->prev = sourceNode->prev;

    sourceNode->prev = objPreNode;
    sourceNode->next = objPreNode->next;

    objPreNode->next->prev = sourceNode;
    objPreNode->next = sourceNode;

}

void parseOption(int argc, char** argv, char* filePath)
{
    int opt;
    while (-1 != (opt = getopt(argc, argv, "s:E:b:t:")))
    {
        switch (opt)
        {   
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            strcpy(filePath, optarg);
            break;
        default:
            printf("wrong argument");
            break;
        }
    }

}


void updateCache(dList* dListArr, unsigned address)
{
    unsigned setMask =  0xffffffffu >> (32 - s);
    unsigned set = setMask & (address >> b);
    unsigned tag = address >> (s + b);

    int found = 0;
    dList* curList = &dListArr[set];
    dNode* curNode = curList->head->next;
    while (curNode != curList->tail)
    {
        if (curNode->tag == tag) {
            found = 1;
            break;
        }
        curNode = curNode->next;
    }


    if (found) {
        hits++;
        moveNode(curNode, curList->head);
        printf("hit set:%d\n", set);
    }else{
        if (curList->size == E) {
            misses++;
            evictions++;
            deleteNode(curList, curList->tail->prev);
            insertNode(curList, curList->head, tag);
            printf("miss + eviction, set:%d\n", set);

        }else{
            misses++;
            insertNode(curList, curList->head, tag);
            printf("only miss set:%d\n", set);
        }
    }
    

}

void cacheSimulate(char* filePath)
{   
    int totalSize = 1 << s;
    dList* dListArr = (dList*) malloc(totalSize*sizeof(dList));
    for (int i = 0; i < totalSize; i++) initDList(dListArr, i);
    char op;
    unsigned address;
    int size;
    FILE* file = fopen(filePath, "r");
    while (fscanf(file, " %c %x, %d", &op, &address, &size) > 0)
    {
        switch (op)
        {
        case 'L':
            updateCache(dListArr, address);
            break;
        case 'M':
            updateCache(dListArr, address);
        case 'S':
            updateCache(dListArr, address);
            break;
        }
    }
    
}


int main(int argc, char** argv)
{
    char* filePath = (char*) calloc(100, sizeof(char));
    parseOption(argc, argv, filePath);
    cacheSimulate(filePath);
    printSummary(hits, misses, evictions);
    return 0;
}
