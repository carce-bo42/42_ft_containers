#ifndef CONTAINERS_RBT_NODE_HPP
# define CONTAINERS_RBT_NODE_HPP

#include <string.h>

enum rb_tree_node_color {
  red = false,
  black = true
};

namespace ft {

/*
 * A node template from a red-black tree. T will
 * always be pairs in case of the map. 
 */
template <typename T>
struct rb_tree_node {

  typedef T                       value_type;
  typedef rb_tree_node*           node_ptr;

  typedef rb_tree_node_color       n_color;
  
  node_ptr         parent;
  node_ptr         left;
  node_ptr         right;
  value_type       data;
  n_color          color;

  // default construction is as left child, and red _color.
  rb_tree_node(const T& value)
  :
    parent(0),
    left(0),
    right(0),
    data(value),
    color(red)
  {}

  ~rb_tree_node() {
  }

  /*
   * Rotations depend on wether a child is at the right
   * or at the left of the parent, so these methods are
   * necessary.
   */
  bool is_left_child() {
    return (parent->left == this);
  }

  bool is_right_child() {
    return (parent->right == this);
  }

  inline void make_root(node_ptr node_end) {
    parent = node_end;
  }

  inline void assign_right_child(node_ptr node) {
    right = node;
  }

  inline void assign_left_child(node_ptr node) {
    left = node;
  }

  inline void assign_parent(node_ptr node) {
    parent = node;
  }

  inline void set_color(n_color c) {
    color = c;
  }

  node_ptr uncle() const{
    if (parent->is_left_child()) {
      return parent->parent->right;
    } else if (parent->is_right_child()) {
      return parent->parent->left;
    } else {
      // if parent is root, node_end is both grandparent and uncle
      return parent->parent;
    }
  }

  // debug:
  void print_node_state() {
    std::cout << std::endl;
    std::cout << "parent : " << parent << std::endl;
    std::cout << "left : " << left << std::endl;
    std::cout << "right : " << right << std::endl;
    std::cout << "data : (" << data.first << ", " << data.second << ")" 
              << std::endl;
    std::cout << "properties : ("
              << (color == black ? "black" : "red") << ", "
              << (is_left_child() ? "left" : "right") << ")"
              << std::endl;
  }

}; // struct rb_tree_node

} // namespace


#endif