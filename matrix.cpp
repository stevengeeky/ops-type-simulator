#include "matrix.h"

#include "math.h"
#include <functional>

Matrix::Matrix(size_t size) : Matrix(size, size) { }
Matrix::Matrix(size_t size, std::function<number(int, int)> compute)
    : Matrix(size, size, compute) {
}

Matrix::Matrix(size_t rows, size_t cols) {
    this->_cols = cols;
    this->_rows = rows;
    this->data = std::vector<std::vector<number>>(cols * rows);

    for (int j = 0; j < rows; j++) {
        this->data[j] = std::vector<number>(cols);
    }
}

Matrix::Matrix(size_t rows, size_t cols, const std::vector<number>& data)
    : Matrix(rows, cols) {
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            this->set(j, i, data[j * cols + i]);
        }
    }
}

Matrix::Matrix(const std::vector<std::vector<number>>& data) {
    this->_rows = data.size();
    this->_cols = data.data()->size();
    this->init([data] (int j, int i) { return data[j][i]; });
}

Matrix::Matrix(size_t rows, size_t cols,
               std::function<number(int, int)> compute)
    : Matrix(rows, cols) {
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            this->data[j][i] = compute(j, i);
        }
    }
}

Matrix::Matrix(const std::initializer_list<Vector>& data) {
    this->data = std::vector<std::vector<number>>();
    this->_rows = 0;
    this->_cols = 0;

    for (auto value : data) {
        this->_rows++;
        this->_cols = value.size();
        this->data.push_back(value._data());
    }
}

Matrix::Matrix(const std::initializer_list<number>& data)
    : Matrix(roundl(sqrtl(data.size()))) {
    int i = 0, j = 0;

    for (auto value : data) {
        if (j == this->_rows) {
            break;
        }

        this->data[j][i] = value;
        i++;

        if (i == this->_rows) {
            i = 0;
            j++;
        }
    }
}

const size_t Matrix::rows() {
    return this->_rows;
}

const size_t Matrix::cols() {
    return this->_cols;
}

const number Matrix::get(const int row, const int col) {
    return this->data[row][col];
}

const number Matrix::set(const int row, const int col, number value) {
    this->data[row][col] = value;
    return value;
}

const Matrix& Matrix::init(std::function<number(int, int)> compute) {
    for (int j = 0; j < this->_rows; j++) {
        for (int i = 0; i < this->_cols; i++) {
            this->set(j, i, compute(j, i));
        }
    }

    return *this;
}

number Matrix::determinant() {
    if (this->_rows == 1) {
        return 1;
    }

    if (this->_rows == 2) {
        return this->data[0][0] * this->data[1][1] -
            this->data[0][1] * this->data[1][0];
    }

    number result = 0;
    for (int i = 0; i < this->_rows; i++) {
        result += this->data[0][i] * this->adjugate(i, 0);
    }

    return result;
}

Matrix Matrix::inverse() { return this->adjugate() / this->determinant(); }

Matrix Matrix::adjugate() { return this->cofactor().transpose(); }
number Matrix::adjugate(int j, int i) { return this->cofactor(i, j); }

Matrix Matrix::cofactor() {
    if (this->_cols != this->_rows) {
        throw "Cannot compute determinant of non-square matrix (" +
            std::to_string(this->_cols) + " != " + std::to_string(this->_rows) +
            ")";
    }

    if (this->_rows == 1) {
        return Matrix{1};
    }

    return Matrix(this->_cols, this->_rows,
                  [this] (int j, int i) { return this->cofactor(j, i); });
}
number Matrix::cofactor(int j, int i) {
    return (((j + i) % 2) ? -1 : 1) *
        Matrix(this->_rows - 1, this->_rows - 1, [this, j, i] (int y, int x) {
        return this->get(y + (y >= j), x + (x >= i));
        }).determinant();
}

Matrix Matrix::apply(Matrix other) {
    auto result = Matrix(this->_cols, other.cols());

    for (int j = 0; j < this->_rows; j++) {
        for (int i = 0; i < this->_cols; i++) {
            for (int k = 0; k < this->_cols; k++) {
                result.set(
                    j, i, result.get(j, i) + this->get(j, k) * other.get(k, i));
            }
        }
    }

    return result;
}
Vector Matrix::apply(Vector vector) {
    return Vector(this->_cols, [this, &vector] (int j) {
        number result = 0;
        for (int i = 0; i < this->_cols; i++) {
            result += this->data[j][i] * vector[i];
        }
        return result;
    });
}

Matrix Matrix::transpose() {
    return Matrix(this->_rows, this->_cols,
                  [this] (int j, int i) { return this->data[i][j]; });
}

Matrix Matrix::operator*(Matrix other) {
    return Matrix(this->_rows, this->_cols, [this, other] (int j, int i) {
        return this->data[j][i] * other.data[j][i];
    });
}
Matrix Matrix::operator*(number c) {
    return Matrix(this->_rows, this->_cols,
                  [this, c] (int j, int i) { return this->data[j][i] * c; });
}

Matrix Matrix::operator/(Matrix other) {
    return Matrix(this->_rows, this->_cols, [this, other] (int j, int i) {
        return this->data[j][i] / other.data[j][i];
    });
}
Matrix Matrix::operator/(number c) {
    return Matrix(this->_rows, this->_cols,
                  [this, c] (int j, int i) { return this->data[j][i] / c; });
}

Matrix Matrix::operator+(Matrix other) {
    return Matrix(this->_rows, this->_cols, [this, other] (int j, int i) {
        return this->data[j][i] + other.data[j][i];
    });
}
Matrix Matrix::operator+(number c) {
    return Matrix(this->_rows, this->_cols,
                  [this, c] (int j, int i) { return this->data[j][i] + c; });
}

Matrix Matrix::operator-(Matrix other) {
    return Matrix(this->_rows, this->_cols, [this, other] (int j, int i) {
        return this->data[j][i] - other.data[j][i];
    });
}
Matrix Matrix::operator-(number c) {
    return Matrix(this->_rows, this->_cols,
                  [this, c] (int j, int i) { return this->data[j][i] - c; });
}

std::ostream& operator<<(std::ostream& os, Matrix mat) {
    os << "[";
    for (int j = 0; j < mat.rows(); j++) {
        if (j < mat.rows() - 1) {
            os << ",\n";
        }

        os << "[";
        for (int i = 0; i < mat.cols(); i++) {
            if (i) {
                os << ",";
            }
            os << mat.get(j, i);
        }
        os << "]";
    }
    os << "]";

    return os;
}
