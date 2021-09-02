#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <cmath>
#include <algorithm>

typedef unsigned int uint;

template <class T, uint sz>
class Vector
{
public:
    Vector();
    Vector(T* input);
    Vector(Vector<T, sz>& input);
    Vector(std::vector<T>&& input);

    Vector(const Vector<T, sz>& other)
    {
        v_size = other.v_size;
        v_data = new T[v_size];
        for (uint i{ 0 }; i < v_size; ++i)
            v_data[i] = other.v_data[i];
    }

    ~Vector();

    Vector<T, sz> operator= (const Vector<T, sz>& other); //Copy assignment
    Vector<T, sz> operator= (Vector<T, sz>&& other); // Move assignment


    template <class U, uint Usize> friend Vector<U, Usize> operator+ (const Vector<U, Usize>& lhs, const Vector<U, Usize>& rhs);

    template <class U, uint Usize> friend Vector<U, Usize> operator- (const Vector<U, Usize>& lhs, const Vector<U, Usize>& rhs);

    template <class U, uint Usize> friend Vector<U, Usize> operator* (const Vector<U, Usize>& lhs, const Vector<U, Usize>& rhs);
    template <class U, uint Usize> friend Vector<U, Usize> operator* (const U& lhs, const Vector<U, Usize>& rhs);

    void print() const;

    T getLength()
    {
        uint dimensions = std::min((uint)3, this->v_size);
        T squared_sum = 0;

        for (uint i = 0; i < dimensions; i++)
            squared_sum += this->v_data[i] * this->v_data[i];

        return std::sqrt(squared_sum);
    }

    Vector<T, sz> getDirection()
    {
        uint dimensions = std::min((uint)3, this->v_size);
        T squared_sum = 0;

        for (uint i = 0; i < dimensions; i++)
            squared_sum += this->v_data[i] * this->v_data[i];

        T magnitude = (T)std::sqrt(squared_sum);

        T result[dimensions];
        for (uint i = 0; i < dimensions; i++)
        {
            T temp = this->v_data[i] / magnitude;
            result[i] = temp;
        }

        // If vector is 4d, we don't want to use w to change direction
        if (dimensions < this->v_size)
        {
            for (uint i = dimensions - 1; i < this->v_size; i++)
            {
                result[i] = this->v_data[i];
            }
        }

        return Vector<T, sz> { this->v_size, result };
    }

    T x() const
    {
        return this->v_data[0];
    }

    T y() const
    {
        return this->v_data[1];
    }

    T z() const
    {
        // verify z, if 2d
        return this->v_data[2];
    }

    T w() const
    {
        // verify w
        return this->v_data[3];
    }

    void normalize()
    {
        uint dimensions = std::min((uint)3, this->v_size);
        T squared_sum = 0;

        for (uint i = 0; i < dimensions; i++)
            squared_sum += this->v_data[i] * this->v_data[i];

        T magnitude = (T)std::sqrt(squared_sum);

        for (uint i = 0; i < dimensions; i++)
        {
            T temp = this->v_data[i] / magnitude;
            this->v_data[i] = temp;
        }
    }

    static T dot(const Vector<T, sz>& lhs, const Vector<T, sz>& rhs);
    static Vector<T, sz> cross(const Vector<T, sz>& a, const Vector<T, sz>& b);

    // Class members
    uint v_size;
    T* v_data;
};

////////////////////////
//
// OPERATORS
//
////////////////////////


// ADDITION
template <class T, uint sz>
Vector<T, sz> operator+ (const Vector<T, sz>& lhs, const Vector<T, sz>& rhs)
{
    uint size = lhs.v_size;
    T result[size];

    for (uint i = 0; i < size; i++)
    {
        result[i] = lhs.v_data[i] + rhs.v_data[i];
    }
    return Vector<T, sz> {size, result};
}

// SUBTRACTION
template <class T, uint sz>
Vector<T, sz> operator- (const Vector<T, sz>& lhs, const Vector<T, sz>& rhs)
{
    uint size = lhs.v_size;
    T result[size];

    for (uint i = 0; i < size; i++)
        result[i] = lhs.v_data[i] - rhs.v_data[i];

    return Vector<T, sz> {size, result};
}

// MULTIPLICATION
template <class T, uint sz>
Vector<T, sz> operator* (const Vector<T, sz>& lhs, const Vector<T, sz>& rhs)
{
    // confirm they are the right size
    uint size = lhs.v_size;
    T result[size];

    for (uint i = 0; i < size; i++)
        result[i] = lhs.v_data[i] * rhs.v_data[i];

    return Vector<T, sz> {size, result};
}

template <class T, uint sz>
Vector<T, sz> operator* (const T& value, const Vector<T, sz>& rhs)
{
    // confirm they are the right size
    uint size = rhs.v_size;
    T result[size];

    for (uint i = 0; i < size; i++)
        result[i] = value * rhs.v_data[i];

    return Vector<T, sz> {size, result};
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
    uint size = lhs.v_size;
    T sum;

    for (uint i = 0; i < size; i++)
        sum += lhs.v_data[i] * rhs.v_data[i];

    return sum;
}

template <class T, uint sz>
Vector<T, sz> Vector<T, sz>::cross(const Vector<T, sz>& a, const Vector<T, sz>& b)
{
    if (a.v_size < 3 && b.v_size < 3)
        throw std::invalid_argument("Vectors must be the same size");

    uint length = 3;
    // TODO: ensure x,y,z components, i.e. at least 3 elements in vector

    // a2b3−a3b2,a3b1−a1b3,a1b2−a2b1
    T x = (a.v_data[1] * b.v_data[2]) - (a.v_data[2] * b.v_data[1]);
    T y = (a.v_data[2] * b.v_data[0]) - (a.v_data[0] * b.v_data[2]);
    T z = (a.v_data[0] * b.v_data[1]) - (a.v_data[1] * b.v_data[0]);

    T cross_product[length];
    for (uint i = 0; i < length; i++)
    {
        switch (i)
        {
        case 0: cross_product[i] = x; break;
        case 1: cross_product[i] = y; break;
        case 2: cross_product[i] = z; break;
        }
    }
    // TODO: should add remaining dimensions also
    return Vector<T, sz> {a.v_size, cross_product };
}

template <class T, uint sz>
Vector<T, sz>::Vector()
{
    v_size = 1;
    T* v_data = nullptr;
}

template<class T, uint size>
Vector<T, size>::Vector(T* input)
{
    v_size = size;
    v_data = new T[size];

    for (uint i = 0; i < size; i++)
        v_data[i] = input[i];
}

template<class T, uint sz>
Vector<T, sz>::Vector(std::vector<T>&& input)
{
    v_size = sz;
    v_data = new T[sz];

    for (uint i = 0; i < sz; i++)
        v_data[i] = input[i];
}

template<class T, uint size>
Vector<T, size>::Vector(Vector<T, size>& input)
{
    v_size = size;
    v_data = new T[size];

    for (uint i = 0; i < size; i++)
        v_data[i] = input.v_data[i];
}

template<class T, uint size>
Vector<T, size>::~Vector()
{
    delete[] v_data;
}

template <class T, uint size>
void Vector<T, size>::print() const
{
    for (uint i = 0; i < v_size; i++)
        std::cout << v_data[i] << ' ';

    std::cout << std::endl;
}


template <class T, uint sz>
Vector<T, sz> Vector<T, sz>::operator= (const Vector<T, sz>& other)
{
    // self-assignment check
    if (this == &other)
        return *this;

    // if data exists in the current string, delete it
    if (this->v_size) delete[] this->v_data;

    // copy the data from str to the implicit object
    this->v_data = new T[sz];

    for (int i{ 0 }; i < sz; i++)
        this->v_data[i] = other.v_data[i];

    // return the existing object so we can chain this operator
    return *this;
};

template <class T, uint sz>
Vector<T, sz> Vector<T, sz>::operator= (Vector<T, sz>&& other)
{
    //std::swap(v_size, other.v_size);
    T* temp = other.v_data;
    v_data = other.v_data;
    other.v_data = v_data;
    return *this;
    //std::swap(&v_data, &other.v_data);
}

#endif