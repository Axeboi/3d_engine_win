#ifndef MESH
#define MESH

#include "vector.h"
#include <vector>
#include <algorithm>
#include <iostream>

typedef unsigned int uint;



template <class T>
struct Triangle
{
    Triangle() {};
    Triangle(const Triangle<T>& other)
    {
        v.clear();
        for (Vector<double, 4> el : other.v)
        {
            v.push_back(el);
        }
    }
    Triangle(Triangle<T>&& other)
    {
       //std::swap(v, other.v);
        v.clear();
        for (Vector<double, 4> el : other.v)
        {
            v.push_back(el);
        }
    }

    Triangle(T p1, T p2, T p3)
    {
        v.push_back(p1);
        v.push_back(p2);
        v.push_back(p3);
    };

    // template <class U>
    const Triangle<T>& operator= (const Triangle<T>& other)
    {
        if (this == &other)
            return *this;

        v.clear();

        for (auto vec : other.v)
            vec.push_back(other.v);

        return *this;
    }

    ~Triangle()
    {
        v.clear();
    }

    void print();
    std::vector<T> v;
};

template<class T>
struct Mesh
{
    void add_tri(Triangle<T> triangle) { tris.push_back(triangle); };
    std::vector< Triangle<T> > tris;
};

template <class T>
void Triangle<T>::print()
{
    for (Vector<double, 4> vec : this->v)
    {
        std::cout << vec.v_data[0] << " " << vec.v_data[1] << " " << vec.v_data[2] << " " << vec.v_data[3] << std::endl;
    }
}
#endif