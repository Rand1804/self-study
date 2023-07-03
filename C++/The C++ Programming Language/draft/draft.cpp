#include <iostream>
using namespace std;

double square(double x) {
    return x*x;
}

void print_square(double x) {
    cout << "the square of" << x << "is" << square(x) << "\n";
}

void intval()
{
    for (char c; cin >> c; )
        cout << "the value of '" << c << "' is " << int{c} << '\n';
}

void f(int* pi)
{
    void* pv = pi; // ok: implicit conversion of int* to void*
  
    int* pi2 = static_cast<int*>(pv);// explicit conversion back to int*

    double* pd3 = static_cast<double*>(pv); // unsafe (§11.5.2)
    
}


int main() {
    print_square(1.234);
    intval();
}
