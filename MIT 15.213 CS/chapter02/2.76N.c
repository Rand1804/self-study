#include <stdio.h>

void *my_calloc(size_t nmemb, size_t size) {
    for(int i=0; i <= (int) nmemb; i++)
        malloc(size);
}