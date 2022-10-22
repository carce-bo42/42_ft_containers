#include "ft/vector.hpp"
#include "ft/stack.hpp"
#include "debug.hpp"
#include <vector>
#include <stdio.h>
#include <map>
#include <iostream>
#include "vector/vector_test.hpp"

#include "ft/RBT/red_black_tree.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"
#include "ft/utils/pair.hpp"
#include "ft/utils/utils.hpp"

int Test_Error(int result, int line, const char* file) {
  std::cout << "ERROR at line " << line << " from test "
            << file << std::endl;
  return result;
}

int vector_test() {
  if (insert_point_single_test() != 0
      || insert_range_value_single_test() != 0
      || insert_range_iterators_single_test() != 0
      || erase_range_single_test() != 0
      || erase_pos_single_test() != 0)
  {
    return 1;
  }
  return 0;
}

class Example {

  public:

  Example(int a, int b)
  :
    i(a),
    j(b)
  {}
  ~Example() {
    i = 0;
    j = 0;
  }

  int i;
  int j;

  void print_numbers() {
    std::cout << "i = " << i
              << ", j = " << j
              << std::endl;
  }


};

int main() {
{
  int a = 4;
  std::vector<int> vec(10, a);

  printf("%lu \n", vec.capacity());
  printf("%lu \n", vec.size());

  vec.resize(123);

  printf("%lu \n", vec.capacity());
  printf("%lu \n", vec.size());
  //printf("%i \n", vec.front()); segfaultea.
}
  if (vector_test() != 0) {
    return 1;
  }
{
  std::allocator<Example> alloc;

  Example* ptr = alloc.allocate(1);

  // Correct way of calling construct with no simple constructor ?
  alloc.construct(ptr, Example(3, 4 ));

  ptr->print_numbers();
  alloc.destroy(ptr);
  ptr->print_numbers();
  alloc.deallocate(ptr, 1);

/*
 * With nodes:
 * 
 * alloc = std::allocator<Node>
 * node_ptr = alloc.allocate(1);
 * alloc.construct(node_ptr, rb_tree_node(a, b, c, d)); (works)
 * 
 * We recieve an std::pair<Key, T>. 
 * this std::pair is the value_type of the map.
 * The correct way of creating a node, will be:
 * node_ptr = node_allocator.allocate(1);
 * node_allocator.construct(node_ptr, rb_tree_node(pair, parent,
 *                                                 color, orientation)).
 * This should work.
 * 
 * 
 */
}
{
  ft::rb_tree<
    int,
    ft::pair<int, std::string>,
    get_key<int, ft::pair<int, std::string> > > tree;
  
  ft::rb_tree_node<ft::pair<int, std::string> > *node =
      tree.construct_node(ft::pair<int, std::string>(3, "hello"),
                          NULL, root, black);
  node->print_node_state();
  node->change_color();
  node->print_node_state();

  tree.pure_insert(node);
  std::cout << "minimum : " << tree.get_minimum() <<  std::endl;
  std::cout << "maximum : " << tree.get_maximum() <<  std::endl;

  std::map<int, std::string> map;

/*
 * The following tree insertions creates this tree:
 * 
 *                      4
 *                  /      \
 *               /            \
 *            /                  \
 *           0                   13
 *       /       \           /       \
 *      -9        2         11       60
 *    /   \     /   \     /   \     /   \
 *  -12   -4   1    3    5    12  40    80
 */
  map.insert(std::pair<int, std::string>(3, "hello)"));
  map.insert(std::pair<int, std::string>(5, "hello)"));
  map.insert(std::pair<int, std::string>(4, "hello)"));
  map.insert(std::pair<int, std::string>(2, "hello)"));
  map.insert(std::pair<int, std::string>(1, "hello)"));
  map.insert(std::pair<int, std::string>(0, "hello)"));
  map.insert(std::pair<int, std::string>(11, "hello)"));
  map.insert(std::pair<int, std::string>(13, "hello)"));
  map.insert(std::pair<int, std::string>(-12, "hello)"));
  map.insert(std::pair<int, std::string>(-9, "hello)"));
  map.insert(std::pair<int, std::string>(-4, "hello)"));
  map.insert(std::pair<int, std::string>(12, "hello)"));
  map.insert(std::pair<int, std::string>(40, "hello)"));
  map.insert(std::pair<int, std::string>(60, "hello)"));
  map.insert(std::pair<int, std::string>(80, "hello)"));
  for (std::map<int, std::string>::iterator it = map.begin();
       it != map.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
}
{
  ft::rb_tree<
    int,
    ft::pair<int, std::string>,
    get_key<int, ft::pair<int, std::string> > > tree;

  // root.
  ft::rb_tree_node<ft::pair<int, std::string> > *_root =
      tree.construct_node(ft::pair<int, std::string>(4, "hello"),
                          NULL, root, black);
  // root right/left
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_r =
      tree.construct_node(ft::pair<int, std::string>(13, "hello"),
                          _root, right_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_l =
      tree.construct_node(ft::pair<int, std::string>(0, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_ll =
      tree.construct_node(ft::pair<int, std::string>(-9, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lr =
      tree.construct_node(ft::pair<int, std::string>(2, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lll =
      tree.construct_node(ft::pair<int, std::string>(-12, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_llr =
      tree.construct_node(ft::pair<int, std::string>(-4, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lrl =
      tree.construct_node(ft::pair<int, std::string>(1, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lrr =
      tree.construct_node(ft::pair<int, std::string>(3, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rl =
      tree.construct_node(ft::pair<int, std::string>(11, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rr =
      tree.construct_node(ft::pair<int, std::string>(60, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rll =
      tree.construct_node(ft::pair<int, std::string>(5, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rlr =
      tree.construct_node(ft::pair<int, std::string>(12, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rrl =
      tree.construct_node(ft::pair<int, std::string>(40, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rrr =
      tree.construct_node(ft::pair<int, std::string>(80, "hello"),
                          _root, left_child, black);

  _root->assign_left_child(_root_l);
  _root->assign_right_child(_root_r);
  _root_l->assign_parent(_root);
  _root_r->assign_parent(_root);

  _root_l->assign_left_child(_root_ll);
  _root_l->assign_right_child(_root_lr);
  _root_ll->assign_parent(_root_l);
  _root_lr->assign_parent(_root_l);

  _root_ll->assign_left_child(_root_lll);
  _root_ll->assign_right_child(_root_llr);
  _root_lll->assign_parent(_root_ll);
  _root_llr->assign_parent(_root_ll);

  _root_lr->assign_left_child(_root_lrl);  
  _root_lr->assign_right_child(_root_lrr);
  _root_lrl->assign_parent(_root_lr);
  _root_lrr->assign_parent(_root_lr);

  _root_r->assign_left_child(_root_rl);
  _root_r->assign_right_child(_root_rr);
  _root_rl->assign_parent(_root_r);
  _root_rr->assign_parent(_root_r);

  _root_rr->assign_left_child(_root_rrl);
  _root_rr->assign_right_child(_root_rrr);
  _root_rrl->assign_parent(_root_rr);
  _root_rrr->assign_parent(_root_rr);

  _root_rl->assign_left_child(_root_rll);  
  _root_rl->assign_right_child(_root_rlr);
  _root_rll->assign_parent(_root_rl);
  _root_rlr->assign_parent(_root_rl);

  tree.pure_insert(_root);

  std::cout << std::endl;
  ft::rb_tree_iterator<ft::pair<int, std::string> > it(_root_lll);
  for (int i = 0; i < 25; i++) {
    std::cout << it->first << std::endl;
    it++;
  }

}
{
  ft::vector<int> vec(3, 4);
  ft::vector<int>::iterator int_it = vec.begin();

  //ft::vector<char>::iterator char_it(int_it); // Substitution failure
}
  return 0;
}