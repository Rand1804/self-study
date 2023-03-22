void transpose (int *dst, int *src, int dim) {
    int i, j;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[j*dim +i] = src[i*dim + j];
}

void transpose_effect (int *dst, int *src, int N) {
    int i, j;
    for (i = 0; i <= N-2; i+=2)
        for (j = 0; j <= N-2; j+=2) {
        dst[j*N+i] = src[i*N+j];
        dst[j*N+i+1] = src[(i+1)*N+j];
        dst[(j+1)*N+i] = src[i*N+j+1];
        dst[(j+1)*N+i+1] = src[(i+1)*N+j+1];
        }
    if (i < N) {
        dst[]
    }
}

