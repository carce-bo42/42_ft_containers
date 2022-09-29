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
{ // insert 1 value test
  ft::vector<int> vec_1(3, 4); // 4 4 4 
  ft::vector<int> vec_2(2, 5); // 5 5 

  vec_1.push_back(3);
  // same template can be called in two different ways :D
  print_vector(vec_1);
  std::cout << std::endl;
  print_vector<int>(vec_1);
  ft::vector<int>::iterator it = vec_1.begin();
  ++it;
  for (int i = 0; i < 1; i++) {
    vec_1.insert(it, 12);
  }
  std::cout << std::endl;
  print_vector(vec_1);
  // iterator invalidated !.
  ft::vector<int>::iterator it_ = vec_1.begin();
  for (int i = 0; i < 1; i++) {
    vec_1.insert(it_, 21);
  }
  std::cout << std::endl;
  print_vector<int>(vec_1);
}
  return 0;
}