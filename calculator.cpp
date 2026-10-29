#include <iostream>
#include <limits>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

using namespace std;

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0.0) return numeric_limits<double>::quiet_NaN();
    return a / b;
}

// Operation: 1 = +, 2 = -, 3 = *, 4 = /
extern "C" EMSCRIPTEN_KEEPALIVE double calculate(double a, double b, int operation) {
    if (operation == 1) return add(a, b);
    if (operation == 2) return subtract(a, b);
    if (operation == 3) return multiply(a, b);
    if (operation == 4) return divide(a, b);
    return numeric_limits<double>::quiet_NaN();
}

#ifndef __EMSCRIPTEN__
int main() {
    double a, b;
    int operation;

    cout << "First number: ";
    if (!(cin >> a)) {
        cerr << "Invalid numeric input." << endl;
        return 1;
    }

    cout << "Second number: ";
    if (!(cin >> b)) {
        cerr << "Invalid numeric input." << endl;
        return 1;
    }

    cout << "Operation (1=+, 2=-, 3=*, 4=/): ";
    if (!(cin >> operation)) {
        cerr << "Invalid operation selection." << endl;
        return 1;
    }

    cout << "Result: " << calculate(a, b, operation) << endl;
    return 0;
}
#endif