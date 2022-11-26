#ifndef CONTAINERS_RBT_NODE_HPP
# define CONTAINERS_RBT_NODE_HPP

#include <string.h>
//#include <iostream>

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

  public:

  typedef T                       value_type;
  typedef rb_tree_node*           node_ptr;
  typedef rb_tree_node_color      n_color;
  
  node_ptr         parent;
  node_ptr         left;
  node_ptr         right;
  value_type       data;
  n_color          color;

  rb_tree_node(const T& value, node_ptr node_end)
  :
    parent(node_end),
    left(node_end),
    right(node_end),
    data(value),
    color(red)
  {}

  /*
   * Trick: This is not a copy constructor. This is used to bypass 
   * Key being const and be able to swap nodes more easily
   */
  rb_tree_node(const T& value, node_ptr parent, node_ptr left,
                               node_ptr right, n_color c)
  :
    parent(parent),
    left(left),
    right(right),
    data(value),
    color(c)
  {}

  template <typename V>
  rb_tree_node(const rb_tree_node<T>& node)
  :
    parent(node.parent),
    left(node.left),
    right(node.right),
    data(node.data),
    color(node.color)
  {}

  ~rb_tree_node() {
  }

  void swap_values(node_ptr other) {
    value_type tmp = this->data;
    data = other->data;
    other->data = tmp;
  }
  
  inline bool is_left_child() const {
    return (parent->left == this);
  }

  inline bool is_right_child() const {
    return (parent->right == this);
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

  node_ptr uncle() const {
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
  /*
  void print_node_state(node_ptr node_end) {
    std::cout << std::endl;
    std::cout << "node_ptr : " << this << std::endl;
    if (parent != node_end) {
      std::cout << "parent : " << parent->data.first 
                << ", " << ((parent->color == black) ? "black" : "red")
                << std::endl;
    } else {
      std::cout << "parent : nill" << std::endl;
    }
    if (left != node_end) {
      std::cout << "left : " << left->data.first
                << ", " << ((left->color == black) ? "black" : "red")
                << std::endl;
    } else {
      std::cout << "left : nill" << std::endl;
    }
    if (right != node_end) {
      std::cout << "right pointer : " << right
                << ", " << ((right->color == black) ? "black" : "red")
                << std::endl;
    } else {
      std::cout << "right : nill" << std::endl;
    }
    std::cout << "data : (" << data.first << ", " << data.second << ")" 
              << std::endl;
    std::cout << "properties : ("
              << (color == black ? "black" : "red") << ", "
              << (is_left_child() ? "left" : "right") << ")"
              << std::endl;
  }
  */

}; // struct rb_tree_node

} // namespace


#endif