#pragma once

#include <vector>
#include "vector.h"
#include <iostream>
#include <array>

template<class T, uint R, uint C>
class Matrix
{
  public:

  Matrix() = default;
  Matrix(const T *inputData);
  Matrix(const Matrix<T, R, C> &inputMatrix) = default;

  // Overload +, - and * operator
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator+ (const Matrix<U, E, D> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator- (const Matrix<U, E, D> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator* (const Matrix<U, E, D> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator* (const U& lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D, uint sz> friend Vector<U, sz> operator* (const Vector<U, sz> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D, uint sz> friend Matrix<U, E, D> operator* (const Matrix<U, E, D> &lhs, const Vector<U, sz> &rhs);
  Vector<T, C>& operator[] (uint);

  void print();

  //private:
  uint m_rows;
  uint m_cols;
  std::array<T, R * C> m_data;

  private:

  static bool less_than_epsilon(T compare)
  {
    return (compare < 0.0001 && compare > -0.0001) ;
  }

};


///////////////////
//
// CONSTRUCTORS
//
///////////////////


template <class T, uint R, uint C>
Matrix<T, R, C>::Matrix(const T *inputData)
{
  m_rows = R;
  m_cols = C;

  for(uint i = 0; i < R * C; i++)
  {
    m_data[i] = inputData[i];
  }
}

///////////////////
//
// OPERATOR OVERLOADING
//
///////////////////

// ADDITION
template <class U, uint R, uint C>
Matrix<U, R, C> operator+ (const Matrix<U, R, C> &lhs, const Matrix<U, R, C> &rhs)
{
  // Test if size of matrices are compatible for addition
  U res[R * C];
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      res[(i * 4) + j] = lhs.m_data[(i * 4) + j] + rhs.m_data[(i * 4) + j];
    }
  }

  return Matrix<U, R, C> {res};
}

// SUBTRACTION
template <class U, uint R, uint C>
Matrix<U, R, C> operator- (const Matrix<U, R, C> &lhs, const Matrix<U, R, C> &rhs)
{
  // Test if size of matrices are compatible for addition
  U res[lhs.m_rows * lhs.m_cols];
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      res[(i * 4) + j] = lhs.m_data[(i * 4) + j] - rhs.m_data[(i * 4) + j];
    }
  }

  return Matrix<U, R, C> {res};
}

// MULTIPLICATION
template <typename U, uint rows, uint cols>
Matrix<U, rows, cols> operator* (const Matrix<U, rows, cols> &lhs, const Matrix<U, rows, cols> &rhs)
{
  // Algorithm for square 3x3 and 4x4 matrices, at least
  // uint rows = lhs.m_rows;
  // uint cols = lhs.m_cols;

  // Init
  U result[rows * cols];
  for(int i = 0; i < rows * cols; i++)
  {
    result[i] = 0;
  }

  // Matrix multiplication
  // lhs = "left hand side" matrix, rhs = "right hand side" matrix
  uint max_index = (rows * cols) - 1;
  for(uint r = 0; r < rows; r++)
  {
    for (uint i = 0; i < rows * cols; i++)
    {
      if (i == max_index)
      {
        result[(r * rows) + i/cols] += lhs.m_data[(r * rows) + i/cols] * rhs.m_data[i];
      }
      else
      {
        result[(r * rows) + i/cols] += lhs.m_data[(r * rows) + (i % cols)] * rhs.m_data[(i * cols) % (max_index)];
      }
    }
  }

  for (uint i = 0; i < rows * cols; i++)
  {
    if (result[i] < 0.00001 && result[i] > -0.00001) { result[i] = 0; };
  }
  return Matrix<U, rows, cols> {result};
}

template <class U, uint rows, uint cols, uint sz>
Vector<U, sz> operator* (const Vector<U, sz> &lhs, const Matrix<U, rows, cols> &rhs)
{
  // Algorithm for square 3x3 and 4x4 matrices, at least
  
  // Init
  std::array<U, cols> result;
  for(int i = 0; i < cols; i++)
  {
    result[i] = 0;
  }

  // Matrix multiplication
  uint max_index = (rows * cols) - 1;

  for (uint i = 0; i < rows * cols; i++)
  {
    if (i == max_index)
    {
      result[i / cols] += ((double) lhs.v_data[i % cols] * (double) rhs.m_data[i]);
    }
    else
    {
      result[i / cols] += ((double) lhs.v_data[i % cols] * (double) rhs.m_data[(i * cols) % (max_index)]);
      //std::cout << result[i / cols] << " " << lhs.v_data[i % cols] << " " << rhs.m_data[(i * cols) % (max_index)] << std::endl;
    }
  }

  for (uint i = 0; i < rows; i++)
  {
    if (result[i] < 0.0000001 && result[i] > -0.0000001)
    {
      result[i] = 0;
    }
  }

  return Vector<U, sz> {result};
}

template <class T, uint rows, uint cols, uint sz>
Matrix<T, rows, cols> operator* (const Matrix<T, rows, cols> &lhs, const Vector<T, sz> &rhs)
{
  // Init
  T result[rows * cols];
  for(int i = 0; i < rows * cols; i++)
  {
    result[i] = 0;
  }

  // Matrix multiplication
  uint max_index = (rows * cols) - 1;

  for (uint i = 0; i < rows * cols; i++)
  {
    if (i == max_index)
    {
      result[i] += lhs.m_data[i] * rhs.v_data[i];
    }
    else
    {
      result[i] += lhs.m_data[i] * rhs.v_data[i % cols];
    }
  }
  return Matrix<T, rows, cols> {result};
}

template <class T, uint rows, uint cols>
Matrix<T, rows, cols> operator* (const T &lhs, const Matrix<T, rows, cols> &rhs)
{
  T result[rows * cols];
  for(uint i = 0; i < (rows * cols); i++)
  {
    result[i] = 0;
  }

  for(uint i = 0; i < (rows * cols); i++)
  {
    T temp = lhs * rhs.m_data[i];
    result[i] = temp;
  }
  return Matrix<T, rows, cols> {result};
}

/////////////////////////
//
// Implementations
//
/////////////////////////


template <class T, uint R, uint C>
void Matrix<T, R, C>::print()
{
  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_cols ; j++)
    std::cout << m_data[(i * m_rows) + j] << ' ';
    std::cout << std::endl;
  }
}

