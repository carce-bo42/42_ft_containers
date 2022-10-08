#ifndef CONTAINERS_RBT_NODE_HPP
# define CONTAINERS_RBT_NODE_HPP

namespace ft {

enum rb_tree_node_color {
  red = false,
  black = true
};

enum rb_tree_node_orientation {
  right_child = false,
  left_child = true
};

enum rb_tree_node_nillness {
  nil = true,
  not_nil = false
};

// This will allow to separate what is importnant for 
// balancing from the rest of the node information.
// allowing declarations of the type
// node( ..., red, right_child, nil).
struct rb_tree_node_properties {

  typedef rb_tree_node_properties  self;
  typedef rb_tree_node_color       n_color;
  typedef rb_tree_node_orientation n_orientation;
  typedef rb_tree_node_nillness    nilness;

  n_color       color;
  n_orientation orientation;
  nilness       nil;

  rb_tree_node_properties(n_color color,
                          n_orientation orientation,
                          nilness nil)
  :
    color(color),
    orientation(orientation),
    nil(nil)
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
    parent(),
    left(),
    right(),
    data(value),
    properties(black, o, nil)
  {}

  rb_tree_node(const T& value, const node_ptr parent,
               n_orientation o, n_color c)
  :
    parent(parent),
    data(value),
    properties(c, o, not_nil)
  {}

  /*
   * Rotations depend on wether a child is at the right
   * or at the left of the parent, so these methods are
   * necessary.
   */
  bool is_left_child() {
    return properties.orientation == left_child;
  }

  bool is_right_child() {
    return properties.orientation == right_child;
  }

  bool is_nil() {
    return properties.nil == nil;
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

  /* 
   * 0 ^ ~0 = 1
   * 1 ^ ~1 = 0 
   */
  void change_color() {
    properties.color ^= ~properties.color;
  }

}; // struct rb_tree_node

} // namespace


#endif