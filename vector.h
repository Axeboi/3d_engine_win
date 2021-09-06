#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>

typedef unsigned int uint;

template <class T, uint sz>
class Vector
{
public:
    Vector<T, sz> () = default;
    Vector<T, sz> (const std::array<T, sz> &other);

    Vector<T, sz> &operator= (const Vector<T, sz> &) = default;

    template <class U, uint Usize> friend Vector<U, Usize> operator+ (const Vector<U, Usize>& lhs, const Vector<U, Usize>& rhs);
    template <class U, uint Usize> friend Vector<U, Usize> operator- (const Vector<U, Usize>& lhs, const Vector<U, Usize>& rhs);
    template <class U, uint Usize> friend Vector<U, Usize> operator* (const Vector<U, Usize>& lhs, const Vector<U, Usize>& rhs);
    template <class U, uint Usize> friend Vector<U, Usize> operator* (const U& lhs, const Vector<U, Usize>& rhs);
    T& operator[] (uint);

    void print() const;

    T getLength()
    {
        uint dimensions = std::min((uint)3, sz);
        T squared_sum = 0;

        for (uint i = 0; i < dimensions; i++)
            squared_sum += this->v_data[i] * this->v_data[i];

        return std::sqrt(squared_sum);
    }

    Vector<T, sz> getDirection()
    {
        // TOOD: should be same function as getDirection() so could be extracted 
        uint dimensions = std::min((uint)3, sz);
        T squared_sum = 0;

        for (uint i = 0; i < dimensions; i++)
            squared_sum += this->v_data[i] * this->v_data[i];

        T magnitude = (T)std::sqrt(squared_sum);

        std::array<T, sz> result;
        for (uint i = 0; i < dimensions; i++)
        {
            T temp = this->v_data[i] / magnitude;
            result[i] = temp;
        }

        // If vector is 4d, we don't want to use w to change direction
        if (dimensions < sz)
        {
            for (uint i = dimensions; i < sz; i++)
            {
                result[i] = this->v_data[i];
            }
        }

        return Vector<T, sz> { result };
    }

    T x() const { return this->v_data[0]; }
    T y() const { return this->v_data[1]; }
    T z() const // Question: is it possible to constexpr this function to only exist for >= 3d?
    {
        if (this->v_data.size() < 3)
            throw std::out_of_range ("No z value in a 2d Vector");
        return this->v_data[2];
    }

    T w() const // Question: is it possible to constexpr this function to only exist for >= 4d?
    {
        if (this->v_data.size() < 4)
            throw std::out_of_range ("No z value in a 2d Vector");
        return this->v_data[3];
    }

    void normalize()
    {
        // TOOD: should be same function as getDirection() so could be extracted 
        uint dimensions = std::min((uint)3, sz);
        T squared_sum { 0 };

        for (uint i = 0; i < dimensions; i++)
            squared_sum += this->v_data[i] * this->v_data[i];

        T magnitude = (T) std::sqrt(squared_sum);

        for (uint i = 0; i < dimensions; i++)
        {
            T temp = this->v_data[i] / magnitude;
            this->v_data[i] = temp;
        }
    }

    uint size() const { return sz; };
    static T dot(const Vector<T, sz>& lhs, const Vector<T, sz>& rhs);
    static Vector<T, sz> cross(Vector<T, sz>& a, Vector<T, sz>& b);

    // Class members
    std::array<T, sz> v_data;
};

////////////////////////
//
// CONSTRUCTORS
//
////////////////////////

template <typename T, uint sz>
Vector<T, sz>::Vector (const std::array<T, sz> &other)
{
    v_data = other;
}

////////////////////////
//
// OPERATOR OVERLOADING
//
////////////////////////

// ADDITION
template <class T, uint sz>
Vector<T, sz> operator+ (const Vector<T, sz>& lhs, const Vector<T, sz>& rhs)
{
    std::array<T, sz> result;

    for (uint i = 0; i < sz; i++)
    {
        result[i] = lhs.v_data[i] + rhs.v_data[i];
    }
    return Vector<T, sz> { result };
}

// SUBTRACTION
template <class T, uint sz>
Vector<T, sz> operator- (const Vector<T, sz>& lhs, const Vector<T, sz>& rhs)
{
    std::array<T, sz> result;

    for (uint i = 0; i < sz; i++)
        result[i] = lhs.v_data[i] - rhs.v_data[i];

    return Vector<T, sz> { result};
}

// MULTIPLICATION
template <class T, uint sz>
Vector<T, sz> operator* (const Vector<T, sz>& lhs, const Vector<T, sz>& rhs)
{
    std::array<T, sz> result;

    for (uint i = 0; i < sz; i++)
        result[i] = lhs.v_data[i] * rhs.v_data[i];

    return Vector<T, sz> { result};
}

template <class T, uint sz>
Vector<T, sz> operator* (const T& value, const Vector<T, sz>& rhs)
{
    std::array<T, sz> result;

    for (uint i = 0; i < sz; i++)
        result[i] = value * rhs.v_data[i];

    return Vector<T, sz> { result};
}

template <class T, uint size>
T& Vector<T, size>::operator[] (uint index)
{ 
    if (this->v_data.size() < index )
        throw std::out_of_range("Error: index is out of bounds");
    return this->v_data[index];
} 

////////////////////////
//
// VECTOR IMPLEMENTATION
//
////////////////////////


// STATIC
template <class T, uint sz>
T Vector<T, sz>::dot(const Vector<T, sz>& lhs, const Vector<T, sz>& rhs)
{
    uint size = lhs.size();
    T sum { 0.0 };

    for (uint i = 0; i < size; i++)
        sum += lhs.v_data[i] * rhs.v_data[i];

    return sum;
}

template <class T, uint sz>
Vector<T, sz> Vector<T, sz>::cross(Vector<T, sz>& a, Vector<T, sz>& b)
{
    if (a.size() < 3 && b.size() < 3)
        throw std::invalid_argument("Vectors must be the same size");

    // a2b3−a3b2,a3b1−a1b3,a1b2−a2b1
    T x = (a.v_data[1] * b.v_data[2]) - (a.v_data[2] * b.v_data[1]);
    T y = (a.v_data[2] * b.v_data[0]) - (a.v_data[0] * b.v_data[2]);
    T z = (a.v_data[0] * b.v_data[1]) - (a.v_data[1] * b.v_data[0]);

    std::array<T, sz> cross_product;
    for (uint i = 0; i < sz; i++)
    {
        switch (i)
        {
        case 0: cross_product[i] = x; break;
        case 1: cross_product[i] = y; break; //(std::abs(y) > 0.000001) ? y : 0.0; break;
        case 2: cross_product[i] = z; break;
        default: cross_product[i] = a[i]; //Add w component if it exist. Arbitrary, though.
        }
    }
    return Vector<T, sz> { cross_product };
}



template <class T, uint size>
void Vector<T, size>::print() const
{
    for (uint i = 0; i < size(); i++)
        std::cout << v_data[i] << ' ';

    std::cout << std::endl;
}

#endif
