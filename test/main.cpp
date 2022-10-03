#include "ft/vector.hpp"
#include "debug.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>
#include "vector/vector_test.hpp"

int Test_Error(int result, int line, const char* file) {
  std::cout << "ERROR at line " << line << " from test "
            << file << std::endl;
  return result;
}

int main() {
{
  int a = 4;
  std::vector<int> vec(0, a);

  printf("%lu \n", vec.capacity());
  printf("%lu \n", vec.size());
  //printf("%i \n", vec.front()); segfaultea.
}
  if (insert_single_test() != 0
      || erase_range_single_test() != 0
      || erase_pos_single_test() != 0)
  {
    return 1;
  }

  return 0;
}