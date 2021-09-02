#pragma once

#include <vector>
#include "vector.h"
#include <iostream>

template<class T, uint R, uint C>
class Matrix
{
  /////////////////////////
  //
  // Declarations
  //
  /////////////////////////
  public:

  Matrix();
  Matrix(const T *inputData);
  // Matrix(unsigned int rows, unsigned int columns, const std::vector<T> &inputData);
  Matrix(const Matrix<T, R, C> &inputMatrix);

  ~Matrix();

  // Overload +, - and * operator
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator+ (const Matrix<U, E, D> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator- (const Matrix<U, E, D> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator* (const Matrix<U, E, D> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D> friend Matrix<U, E, D> operator* (const U& lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D, uint sz> friend Vector<U, sz> operator* (const Vector<U, sz> &lhs, const Matrix<U, E, D> &rhs);
  template <class U, uint E, uint D, uint sz> friend Matrix<U, E, D> operator* (const Matrix<U, E, D> &lhs, const Vector<U, sz> &rhs);

  void print();

  //private:
  uint m_rows;
  uint m_cols;
  uint m_num_elements;
  T* m_data;

  private:

  static bool less_than_epsilon(T compare)
  {
    return compare < 0.0001;
  }

};


template <class U, uint R, uint C>
Matrix<U, R, C> operator+ (const Matrix<U, R, C> &lhs, const Matrix<U, R, C> &rhs)
{
  // Test if size of matrices are compatible for addition
  U res[lhs.m_rows * lhs.m_cols];
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      res[(i * 4) + j] = lhs.m_data[(i * 4) + j] + rhs.m_data[(i * 4) + j];
    }
  }

  return Matrix<U, R, C> {4, 4, res};
}

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

  return Matrix<U, R, C> {4, 4, res};
}

///////////////////
//
// MULTIPLICATION
//
///////////////////
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
    if (result[i] < 0.0000001 && result[i] > -0.0000001) { result[i] = 0; };
  }
  return Matrix<U, rows, cols> {result};
}

template <class U, uint rows, uint cols, uint sz>
Vector<U, sz> operator* (const Vector<U, sz> &lhs, const Matrix<U, rows, cols> &rhs)
{
  // Algorithm for square 3x3 and 4x4 matrices, at least
  
  // Init
  double result[cols];
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
Matrix<T, R, C>::Matrix()
{
  m_rows = R;
  m_cols = C;
  m_num_elements = R * C;
  m_data = new T[m_num_elements];

  for(uint i = 0; i < m_num_elements; i++)
  {
    m_data[i] = 0.0;
  }
}

template <class T, uint R, uint C>
Matrix<T, R, C>::Matrix(const T *inputData)
{
  m_rows = R;
  m_cols = C;
  m_num_elements = R * C;
  m_data = new T[m_num_elements];

  for(uint i = 0; i < m_num_elements; i++)
  {
    m_data[i] = inputData[i];
  }
}

template <class T, uint R, uint C>
Matrix<T, R, C>::Matrix(const Matrix<T, R, C> &other_matrix)
{
  m_rows = other_matrix.m_rows;
  m_cols = other_matrix.m_cols;
  m_num_elements = other_matrix.m_num_elements;
  m_data = new T[m_num_elements];

  for(uint i = 0; i < m_num_elements; i++)
  {
    m_data[i] = other_matrix.m_data[i];
  }
}

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

template<class T, uint R, uint C>
Matrix<T, R, C>::~Matrix()
{
  delete[] m_data;
}
