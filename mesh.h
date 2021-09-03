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
        for(uint i {0}; i < v.size(); i++)
            v[i] = other.v[i];
        //std::copy(v.begin(), v.end(), other.v.begin());
        // for (Vector<double, 4> el : other.v)
        // {
        //     v.push_back(el);
        // }
    }
    Triangle(Triangle<T>&& other)
    {
       std::swap(v, other.v);
    }

    Triangle(T p1, T p2, T p3)
    {
        v[0] = p1;
        v[1] = p2;
        v[2] = p3;
    };

    T& operator[] (uint index)
    {
        if (this->v.size() < index)
        {
            throw std::out_of_range("Error: Requested index out of range. Exiting");
            exit(0);
        }
        return this->v[index];
    };

    const Triangle<T>& operator= (const Triangle<T>& other)
    {
        if (this == &other)
            return *this;

        for(uint i {0}; i < v.size(); i++) 
            v[i] = other.v[i];
        
        return *this;
    }


    // ~Triangle()
    // {
    //     v.clear();
    // }

    void print();
    std::array<T, 3> v;
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