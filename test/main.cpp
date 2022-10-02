#include "ft/vector.hpp"
#include "debug.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>
#include "vector/vector_test.hpp"

int main() {
{
  int a = 4;
  std::vector<int> vec(0, a);

  printf("%lu \n", vec.capacity());
  printf("%lu \n", vec.size());
  //printf("%i \n", vec.front()); segfaultea.
}
  if (insert_single_test() != 0) {
    return 1;
  }

  return 0;
}