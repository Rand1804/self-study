#include <iostream>
#include <map>

enum color {WHITE, BLACK, RED};
struct obj {
    int i;
    char c;
    int a[10];

    obj(int i, char c, int a[10]) : i(i), c(c) {
        for (int j = 0; j < 10; j++) {
            this->a[j] = a[j];
        }
    }
    obj() {}

    // obj& operator=(const obj& o) {
    //     i = o.i;
    //     c = o.c;
    //     for (int j = 0; j < 10; j++) {
    //         a[j] = o.a[j];
    //     }
    //     return *this;
    // }
};


int main() {
    std::map<int, obj> mymap;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    obj o(1, 'a', a);
    mymap[1] = o;
    std::cout << &mymap[1].a << std::endl;
    
    std::cout << &a << std::endl;
    std::cout << &o.a << std::endl;
}