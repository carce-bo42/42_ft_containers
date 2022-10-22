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

  n_color       color;
  n_orientation orientation;
  //nilness       nil;

  rb_tree_node_properties(n_color color,
                          n_orientation orientation)
                          //nilness nil)
  :
    color(color),
    orientation(orientation)
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

  // empty constructor
  rb_tree_node(n_orientation o, const T& value = T())
  :
    parent(0),
    left(0),
    right(0),
    data(value),
    properties(black, o)
  {}

  rb_tree_node(const T& value, const node_ptr parent,
               n_orientation o, n_color c)
  :
    parent(parent),
    left(0),
    right(0),
    data(value),
    properties(c, o)
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
    return properties.orientation == left_child;
  }

  bool is_right_child() const {
    return properties.orientation == right_child;
  }

  bool is_root() const  {
    return properties.orientation == root;
  }

  void assign_right_child(node_ptr node) {
    right = node;
  }

  void assign_left_child(node_ptr node) {
    left = node;
  }

  void assign_parent(node_ptr node) {
    parent = node;
  }

  void change_color() {
    properties.color = (n_color)!properties.color;
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
              << (properties.color == black ? "black" : "red") << ", "
              << (properties.orientation == left_child ? "left" : "right") << ")"
              << std::endl;
  }

}; // struct rb_tree_node

} // namespace


#endif