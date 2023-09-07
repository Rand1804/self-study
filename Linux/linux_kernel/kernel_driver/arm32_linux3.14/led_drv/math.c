

#include <linux/init.h>
#include <linux/module.h>


int my_add(int a, int b) {
    return a + b;
}

EXPORT_SYMBOL(my_add);

int my_sub(int a, int b) {
    return a - b;
}

EXPORT_SYMBOL(my_sub);

MODULE_LICENSE("GPL");







