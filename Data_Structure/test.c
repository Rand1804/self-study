#include <stdio.h>
#include <stdlib.h>

void 
swap(int tree[], int a, int b)
{
    int temp = tree[a];
    tree[a] = tree[b];
    tree[b] = temp;
}



void 
heapify(int tree[], int n, int i)
{
    if (i >= n) {
        return;
    }
    
    int c1 = 2 * i + 1;
    int c2 = 2 * i + 2;
    int max = i;
    
    if (c1 < n && tree[c1] > tree[max]) {
        max = c1;
    }
    if (c2 < n && tree[c2] > tree[max]) {
        max = c2;
    }
    if (max != i) {
        swap(tree, max, i);
        heapify(tree, n, max);
    }
}


int 
main()
{
    int tree[] = {4, 10, 2, 5, 1, 3};
    int n = sizeof(tree) / sizeof(tree[0]);
    heapify(tree, n, 0);
    
    for (int i = 0; i < n; i++) {
        printf("%d\n", tree[i]);
    }
    
    return 0;
    
}