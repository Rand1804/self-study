#define IDENT 0
#define OP +


typedef long data_t;

typedef struct {
    long len;

    data_t *data;
}vec_rec, *vec_ptr;



void combine1 (vec_ptr v, data_t *dest) {
    long i;

    *dest = IDENT;
    for (i = 0; i< vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void combine2 (vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(v);
    *dest = IDENT;

    for (i = 0; i < length; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void combine3 (vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    *dest = IDENT;
    
    for (i = 0; i < length; i++) {
        *dest = *dest OP data[i];
    }
}

void combine4 (vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;
    
    for (i = 0; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}

void combine5 (vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;
    
    for (i = 0; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}

int main() {
    vec_ptr v;
    data_t *dest;
    long a[3] = {1, 2, 3};
    v->len = 3;
    v->data = a;
    combine1(v, dest);
    data_t *dest;
}


/*
    256 22  8   2
    32  24  5   3
    1   27  0   5
*/

/*
    8+3+2
    0    1110    0011    0100
    CO = 0x0
    CI = 0x5
    CT = 0x71
    y
    0B

    0x0CB4
    0    1100    1011    0100
    CO = 0x0
    CI = 0x5
    CT = 0x65
    N
    -

    0x0A31
    0    1010    0011    0001
    CO = 0x1
    CI = 0x4
    CT = 0x51
    N
    -

