#ifndef CONTAINERS_RBT_NODE_HPP
# define CONTAINERS_RBT_NODE_HPP

#include <string.h>

enum rb_tree_node_color {
  red = false,
  black = true
};

enum rb_tree_node_orientation {
  root = 0,
  left_child,
  right_child  
};

enum rb_tree_node_nillness {
  nil = true,
  not_nil = false
};

namespace ft {

// This will allow to separate what is importnant for 
// balancing from the rest of the node information.
// allowing declarations of the type
// node( ..., red, right_child, nil).
struct rb_tree_node_properties {

  typedef rb_tree_node_properties  self;
  typedef rb_tree_node_color       n_color;
  typedef rb_tree_node_orientation n_orientation;
  //typedef rb_tree_node_nillness    nilness;

  n_color       _color;
  n_orientation _orientation;
  //nilness       nil;

  rb_tree_node_properties(n_color _color,
                          n_orientation orientation)
                          //nilness nil)
  :
    _color(_color),
    _orientation(orientation)
    //nil(nil)
  {}
};

/* Red black trees must hold :
 * (0) Nodes are either RED or BLACK (surprise)
 * (1) Root and nil leaves are BLACK.
 * (2) If a node is RED, its children are BLACK.
 * (3) All paths from a node (not counting the starting
 *     one) to its nil descendants contain the same number
 *     of black nodes.
 */


/*
 * A node template from a red-black tree. T will
 * always be pairs in case of the map. 
 */
template <typename T>
struct rb_tree_node {

  typedef T                       value_type;
  typedef rb_tree_node*           node_ptr;
  typedef const rb_tree_node*     const_node_ptr;
  typedef rb_tree_node_color      node_color;

  typedef rb_tree_node_properties node_properties;
  typedef rb_tree_node_color       n_color;
  typedef rb_tree_node_orientation n_orientation;
  typedef rb_tree_node_nillness    nilness;
  
  node_ptr         parent;
  node_ptr         left;
  node_ptr         right;
  value_type       data;
  node_properties  properties;

  rb_tree_node(const T& value, const node_ptr parent,
               n_orientation o, n_color c)
  :
    parent(parent),
    left(0),
    right(0),
    data(value),
    properties(c, o)
  {}

  // default construction is as left child, and red _color.
  rb_tree_node(const T& value, n_color c)
  :
    parent(0),
    left(0),
    right(0),
    data(value),
    properties(c, left_child)
  {}

  ~rb_tree_node() {
    memset((void*)this, 0, sizeof(*this));
  }

  /*
   * Rotations depend on wether a child is at the right
   * or at the left of the parent, so these methods are
   * necessary.
   */
  bool is_left_child() const {
    return properties._orientation == left_child;
  }

  bool is_right_child() const {
    return properties._orientation == right_child;
  }

  n_orientation orientation() const {
    return properties._orientation;
  }

  bool is_root() const  {
    return properties._orientation == root;
  }

  inline void make_root() {
    properties._orientation = root;
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

  inline void assign_parent(node_ptr node, n_orientation o) {
    parent = node;
    properties._orientation = o;
  }

  inline void set_color(n_color c) {
    properties._color = c;
  }

  inline node_ptr uncle() {
    if (parent) {
      if (parent->is_left_child()) {
        return parent->parent->right;
      } else if (parent->is_right_child()) {
        return parent->parent->left;
      } else {
        // if parent is root, node_end is both grandparent and uncle 
        return parent->parent;
      }
    }
    return NULL;
  }

  inline n_color color() const {
    return properties._color;
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
              << (properties._color == black ? "black" : "red") << ", "
              << (properties._orientation == left_child ? "left" : "right") << ")"
              << std::endl;
  }

}; // struct rb_tree_node

} // namespace


#endif