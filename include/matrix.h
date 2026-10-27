//
// Created by Bogdan Sirotich on 26.10.2026.
//

#ifndef OC26_MATRIX_H
#define OC26_MATRIX_H

#include <vector>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
public:
    Matrix(size_t rows, size_t cols);
    const std::vector<T>& operator[](size_t row) const;
    std::vector<T>& operator[](size_t row);
};

extern template class Matrix<int>;
extern template class Matrix<double>;
#endif //OC26_MATRIX_H
