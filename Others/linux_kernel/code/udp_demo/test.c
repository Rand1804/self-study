#include "net.h"

int main() {
    char s[] = "5003";

    short port = htons((short)atoi(s));

    printf("%d", port);
}