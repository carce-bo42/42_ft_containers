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
  vec_1.push_back(3);
  // same template can be called in two different ways :D
  print_vector(vec_1);
  print_vector<int>(vec_1);
  ft::vector<int>::iterator it = vec_1.begin();
  ++it;
  // vec_1 = 4 4 4 3
  vec_1.insert(it, 12);
  // shoudl be now 4 12 4 4 3
  print_vector(vec_1);
  // iterator invalidated !.
  ft::vector<int>::iterator it_ = vec_1.begin();
  for (int i = 0; i < 1; i++) {
    vec_1.insert(it_, 21);
  }
  print_vector<int>(vec_1);
}
{ // insert several at last position by inserting 1 each time
  ft::vector<int> vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    ft::vector<int>::iterator it = vec.begin();
    for(; it != vec.end(); it++) {}
    vec.insert(it, 21);
  }
  print_vector(vec);
}
{ // insert several at last position at once
  ft::vector<int> vec(4, 5); // 5 5 5 5 
  ft::vector<int>::iterator it = vec.begin();
  for(; it != vec.end(); it++) {}
  vec.insert(it, 10, 21);
  print_vector(vec);  
}
{ // insert several before last position by inserting 1 each time
  ft::vector<int> vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    ft::vector<int>::iterator it = vec.begin();
    for(; it != vec.end(); it++) {}
    it--;
    vec.insert(it, 21);
  }
  print_vector(vec);
}
{ // insert several before last position by inserting 1 each time,
  // this time reserving 200 before inserting, to check for capacity variations.
  ft::vector<int> vec(4, 5); // 5 5 5 5 
  vec.reserve(200);
  size_t capacity = vec.capacity();
  for (int i = 0; i < 10; i++) {
    ft::vector<int>::iterator it = vec.begin();
    for(; it != vec.end(); it++) {}
    it--;
    vec.insert(it, 21);
  }
  print_vector(vec);
  std::cout << "capacity == after insert capacity = "
            << (capacity == vec.capacity()) << std::endl;
}
  return 0;
}