#include <stdio.h>


int cent = 0;

int func2() {
    return cent++;
}

int main() {
    int res = func2();
    printf("%d  %d", res, cent);
}