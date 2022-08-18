#pragma once
#include <functional>

#include "vector.h"

typedef long double number;

class Matrix
{
    protected:
    size_t _cols;
    size_t _rows;
    std::vector<std::vector<number>> data;

    public:
    Matrix(size_t size);
    Matrix(size_t size, std::function<number(int, int)> compute);

    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, const std::vector<number>& data);
    Matrix(size_t rows, size_t cols, std::function<number(int, int)> compute);

    Matrix(const std::vector<std::vector<number>>& data);
    Matrix(const std::initializer_list<number>& data);
    Matrix(const std::initializer_list<Vector>& data);

    const number get(int row, int col);
    const number set(int row, int col, number value);
    const Matrix& init(std::function<number(int, int)> compute);

    const size_t rows();
    const size_t cols();

    Matrix inverse();
    number determinant();

    Matrix adjugate();
    number adjugate(int j, int i);

    Matrix cofactor();
    number cofactor(int j, int i);

    Matrix apply(Matrix other);
    Vector apply(Vector values);

    Matrix transpose();

    Matrix operator*(Matrix other);
    Matrix operator*(number c);

    Matrix operator/(Matrix other);
    Matrix operator/(number c);

    Matrix operator+(Matrix other);
    Matrix operator+(number c);

    Matrix operator-(Matrix other);
    Matrix operator-(number c);

    friend std::ostream& operator<<(std::ostream& os, Matrix& mat);
};