#include <iostream>

#include "polynomial.h"

using namespace std;

int main() {
    Polynomial a, b;

    // (a) istream& operator >>
    cin >> a;
    cin >> b;

    // (b) ostream& operator <<
    cout << a;
    cout << b;

    // (c) Copy Constructor
    Polynomial *c = new Polynomial(a);
    cout << c;

    // (d) Assignment
    *c = b;
    cout << c;

    // (e) Destructor
    delete c;

    // (f) Addition
    cout << a + b;

    // (g) Substraction
    cout << a - b;

    // (h) Multiplication
    cout << a * b;

    // (i) Evaluate
    float x = 2.5;
    cout << a.Evaluate(x);
    cout << b.Evaluate(x);
}
