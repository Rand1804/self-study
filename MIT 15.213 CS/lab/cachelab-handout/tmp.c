#include <stdio.h>


void transpose_submit(int M, int N, int A[4][4], int B[4][4])
{
    int i, j, k, l;
    for (i = 0; i < N; i += 2) {
        for (j = 0; j < M; j += 2) {
            for (k = i; k < i+2; k++) {
                for (l = j; l < j+2; l++) {
                    B[l][k] = A[k][l];
                    printf("A[%d][%d], B[%d][%d]\n", k, l, l, k);
                }
            printf("k-----------------\n");
            }
            printf("j-----------------\n");
        }
        printf("i--------------------\n");
    }
    for (i=0;i<N;i++) {
        printf("\n");
        for (j=0;j<M;j++) {
            printf("A:%d\t", A[i][j]);
            printf("B:%d\t", B[i][j]);
        }
    }
}
        


int main()
{
    int A[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    int B[4][4] = {0};
    transpose_submit(4, 4, A, B);
    
}