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

int main() {
    print_square(1.234);
    intval();
}
