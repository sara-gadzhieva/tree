#include <iostream>

#include "counter.h"
#include "matrix.h"

int main() {
    utils::counter::Counter c;
    c.increment();
    c.increment();
    std::cout << c.value() << "\n";
    const Matrix<int> m(3,3);
    std::cout << m[1][1] << "\n";
    //m[1][1] = 1;
    return 0;
}
