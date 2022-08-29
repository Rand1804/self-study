
int main () {
    int i, sum = 0;
    int a[6] = {0, 1, 2, 3, 4, 5};
    for (i = 0; i < (6-2); i += 2) {
        sum += a[i];
        sum += a[i+1];
    }

}