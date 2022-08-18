#include "vector.h"

#include <sstream>
#include <vector>

#include "math.h"

Vector::Vector(size_t size) { this->data = std::vector<number>(size); }
Vector::Vector(size_t size, std::function<number(int)> compute) : Vector(size) {
    this->init(compute);
}

Vector::Vector(const std::initializer_list<number>& data) {
    this->data = std::vector<number>();
    for (auto value : data) {
        this->data.push_back(value);
    }
}

const Vector& Vector::init(std::function<number(int)> compute) {
    for (int i = 0; i < this->size(); i++) {
        this->data[i] = compute(i);
    }

    return *this;
}

size_t Vector::size() { return this->data.size(); }

number Vector::length() { return sqrtl(this->dot(*this)); }

number Vector::dot(const Vector& other) {
    number result = 0;
    for (const auto value : this->data) {
        result += value * value;
    }
    return result;
}

std::string Vector::join(const std::string& delimiter) {
    std::stringstream result;

    for (int i = 0; i < this->size(); i++) {
        if (i > 0) {
            result << delimiter;
        }
        result << this->data[i];
    }

    return result.str();
}

std::ostream& operator<<(std::ostream& os, Vector& vec) {
    os << "[" << vec.join(",") << "]";
    return os;
}

std::vector<number>& Vector::_data() {
    return this->data;
}

number Vector::operator[](int i) { return this->data[i]; }

Vector Vector::operator*(Vector other) {
    return Vector(this->size(), [this, &other] (int i) { return (*this)[i] * other[i]; });
}
Vector Vector::operator*(number c) {
    return Vector(this->size(), [this, c] (int i) { return (*this)[i] * c; });
}

Vector Vector::operator/(Vector other) {
    return Vector(this->size(), [this, &other] (int i) { return (*this)[i] / other[i]; });
}
Vector Vector::operator/(number c) {
    return Vector(this->size(), [this, c] (int i) { return (*this)[i] / c; });
}

Vector Vector::operator+(Vector other) {
    return Vector(this->size(), [this, &other] (int i) { return (*this)[i] + other[i]; });
}
Vector Vector::operator+(number c) {
    return Vector(this->size(), [this, c] (int i) { return (*this)[i] + c; });
}

Vector Vector::operator-(Vector other) {
    return Vector(this->size(), [this, &other] (int i) { return (*this)[i] - other[i]; });
}
Vector Vector::operator-(number c) {
    return Vector(this->size(), [this, c] (int i) { return (*this)[i] - c; });
}
