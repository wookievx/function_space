#include <iostream>
#include "functional_space.h"

using namespace std;


int main() {
    cout << "Hello, World!" << endl;
    //Examples of usage
    auto a = functional_space<int>::basic_function([](const int &a) {
        return 3 * a;
    }) + 2;

    auto b = functional_space<int>::basic_function([](const int &x) {
        return x + 5;
    }) * 2;

    functional_space<int>::multiplicative xc = functional_space<int>::basic_function([](const int &x) -> int {
        return x * x;
    }) * [](const int &y) -> int {
        return y / 3;
    };
    cout << xc(100) << endl; //33000
    cout << a(5) << endl; //17
    cout << b(-5) << endl; //0
    auto c = a * b;
    cout << c(1) << endl; //60
    auto d = a + b;
    cout << d(1) << endl; //17
    return 0;
}