#ifndef CONTAINERS_RBT_NODE_HPP
# define CONTAINERS_RBT_NODE_HPP

namespace ft {
/*
 * abstraction of the color of a node.
 */
enum rb_tree_node_color { red = false, black = true };

/*
 * A node template from a red-black tree. T will
 * always be pairs in case of the map. 
 */
template <typename T>
struct rb_tree_node {

  typedef rb_tree_node<T>*       node_ptr;
  typedef const rb_tree_node<T>* const_node_ptr;
  typedef rb_tree_node_color     node_color;
  typedef T                      value_type;
  
  node_ptr   parent; // needed for balancing
  node_ptr   left;
  node_ptr   right;
  node_color color;
  value_type data;

  // empty constructor
  rb_tree_node(const T& value = T())
  :
    parent(),
    left(),
    right(),
    color(black),
    data(value)
  {}

  rb_tree_node(const T& value)
  :
    parent(),
    left(),
    right(),
    color(black),
    data(value)
  {}

  rb_tree_node(const T& value, const node_ptr parent)
  :
    parent(parent),
    data(value)
  {}

}; // struct rb_tree_node

} // namespace


#endif