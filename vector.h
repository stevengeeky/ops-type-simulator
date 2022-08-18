#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "types.h"

class Vector
{
    protected:
    std::vector<number> data;

    public:
    Vector(size_t size);
    Vector(size_t size, std::function<number(int)> compute);
    Vector(const std::initializer_list<number>& data);

    const Vector& init(std::function<number(int)> compute);

    size_t size();

    number dot(const Vector& other);
    number length();

    std::string join(const std::string& separator);

    number operator[](int index);

    Vector operator*(Vector other);
    Vector operator*(number c);

    Vector operator/(Vector other);
    Vector operator/(number c);

    Vector operator+(Vector other);
    Vector operator+(number c);

    Vector operator-(Vector other);
    Vector operator-(number c);

    friend std::ostream& operator<<(std::ostream& os, Vector& mat);

    std::vector<number>& _data();
};
