#include "matrix.h"

#include <vector>

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) {
    data.resize(rows);
    for (size_t r = 0; r < rows; r++) {
        data[r].resize(columns);
    }
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](size_t row) const {
    return data[row];
}

template <typename T>
std::vector<T>& Matrix<T>::operator[](size_t row) {
    return data[row];
}

template class Matrix<int>;
template class Matrix<double>;

