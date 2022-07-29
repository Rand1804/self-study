struct ACE {
    short v;
    struct ACE *p;
};


short test(struct ACE *ptr) {
    short res = 1;
    while (ptr) {
        res *= ptr->v;
        ptr = ptr->p;
    }
}



// 0 16  24   st->s.x    &(st->s.x) 

/*  short   movw    8(%rdi), %ax
            movw    %ax, (rsi)
    char *  leaq    10(%rdi), %rax
            movq    %rax, (%rsi)
    int *   movq    %rdi, %rax
    int     movq    (%rdi), %rax
            movl   (%rdi,%rax,4), %eax
            movl    %eax, (%rsi)
    char    movq    8(%rdi), %rax
            movb    (%rax), %al

*/
