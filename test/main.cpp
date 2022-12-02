#include <map>
#include <string>

// static declarations and unused functions :
// #include "test_utils.hpp"

#include "test.hpp"

std::map<int, std::string> error_map;

int main() {
  
  LoadErrorMap();

  vector_test();
  vector_performance();

  stack_test();
  stack_performance();

  map_test();
  map_performance();

  set_test();
  set_performance();
  
  return 0;
}