#include <stdio.h>

// A K=17
int A(int x) {
    x = (x << 4) + x;
    printf("%d", x);
}

// B K=-7
int B(int x) {
    x = -((x << 3) - x);
    printf("%d", x);
}

// C K=60
int C(int x) {
    x = (x << 6) - (x << 2);
    printf("%d", x);
}

// D K=-112
int D(int x) {
    x = (x << 4) - (x << 7);
    printf("%d", x);
}


int main() {
    B(2);
}