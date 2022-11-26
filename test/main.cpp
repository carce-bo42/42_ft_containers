#include "ft/vector.hpp"
#include "ft/stack.hpp"
#include "ft/map.hpp"
#include "ft/set.hpp"

#include <vector>
#include <map>
#include <stdio.h>
#include <iostream>
#include "map/rbtree_test.hpp"

// static declarations and unused functions :
// #include "test_utils.hpp"

#include "test.hpp"

#include "ft/RBT/red_black_tree.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"
#include "ft/utils/pair.hpp"
#include "ft/utils/utils.hpp"
#include "ft/RBT/reb_black_tree_reverse_iterator.hpp"

int main() {

  vector_test();
  vector_performance();

  map_test();
  map_performance();
  
  return 0;
}