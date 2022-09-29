#include "ft/vector.hpp"
#include "debug.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>

int main() {
{ 
  int a = 4;
  std::vector<int> vec(0, a);

  printf("%lu \n", vec.capacity());
  printf("%lu \n", vec.size());
  //printf("%i \n", vec.front()); segfaultea.
}
{
  ft::vector<int> vec_1(3, 4); // 4 4 4 
  ft::vector<int> vec_2(2, 5); // 5 5 

  vec_1.push_back(3);
  // same template can be called in two different ways :D
  print_vector(vec_1);
  std::cout << std::endl;
  print_vector<int>(vec_1);
  std::cout << std::endl;
}
  return 0;
}