#include "../vector.h"

typedef Vector<double, 4> vec4d;
typedef Vector<double, 3> vec3d;

// bool add()
// {

// }

// bool subtract()
// {

// }

bool dot()
{
  std::array<double, 2> vec1_data { 1.0, 0.0 };
  std::array<double, 2> vec2_data { 1.0, 1.0 };
  Vector<double, 2> vec1 {vec1_data};
  Vector<double, 2> vec2 {vec2_data};

  bool result {false};
  return (std::abs(Vector<double,2>::dot(vec1, vec2)) < 0.0001);
}

bool cross()
{
  std::array<double, 4> vec1_data { 1.0, 0.0, 0.0, 1.0 };
  std::array<double, 4> vec2_data { 1.0, 1.0, 0.0, 1.0 };
  vec4d vec1 {vec1_data};
  vec4d vec2 {vec2_data};

  vec4d cross_vec = vec4d::cross(vec1, vec2);
  bool x_result {false};
  bool y_result {false};
  bool z_result {false};
  bool w_result {false};
  x_result = std::abs(cross_vec.x()) < 0.00000001; 
  y_result = std::abs(cross_vec.y()) < 0.00000001; 
  z_result = std::abs(cross_vec.z() - 1.0) < 0.00000001; 
  w_result = std::abs(cross_vec.w() - 1.0) < 0.00000001;
  return z_result && w_result;
}

bool cross_real_test()
{
  std::array<double, 4> vec1_data { 1.0, 0.0, 0.0, 1.0 };
  std::array<double, 4> vec2_data { 1.0, 1.0, 0.0, 1.0 };
  vec4d vec1 {vec1_data};
  vec4d vec2 {vec2_data};
}

vec3d normalize()
{
    std::array<double, 3> vec1_data { 1.0, 1.0, 1.0 };
    vec3d vec1 {vec1_data};
    vec1.normalize();
    return vec1;
}

vec4d getDirection()
{
    std::array<double, 4> vec1_data { 1.0, 1.0, 1.0, 1.0 };
    vec4d vec1 {vec1_data};
    return vec1.getDirection();
}

double getLength()
{
    std::array<double, 4> vec1_data { 1.0, 1.0, 1.0, 1.0 };
    vec4d vec1 {vec1_data};
    return vec1.getLength();
}

int main()
{
  std::cout << "Cross product is " << cross() << std::endl;
  std::cout << "Dot product is " << dot() << std::endl;
 
  vec3d normalized = normalize();
  std::cout << "Normalize should give 0.57735 for each element and returns ";
  normalized.print();

  vec4d direction = getDirection();
  std::cout << "getDirection() should give 0.57735 for each 3d element in and returns ";
  direction.print();

  std::cout << "getLength() should give magnitude 1.732 of 3d elements and returns " << getLength() << std::endl;
}