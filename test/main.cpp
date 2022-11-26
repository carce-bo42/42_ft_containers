#include "ft/vector.hpp"
#include "ft/stack.hpp"
#include "ft/map.hpp"
#include "ft/set.hpp"

#include <vector>
#include <map>
#include <stdio.h>
#include <iostream>

// static declarations and unused functions :
// #include "test_utils.hpp"

#include "test.hpp"

#include "ft/RBT/red_black_tree.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"
#include "ft/utils/pair.hpp"
#include "ft/utils/utils.hpp"
#include "ft/RBT/reb_black_tree_reverse_iterator.hpp"

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