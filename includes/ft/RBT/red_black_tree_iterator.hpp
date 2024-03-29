#ifndef FT_CONTAINERS_RED_BLACK_TREE_ITERATOR
# define FT_CONTAINERS_RED_BLACK_TREE_ITERATOR
#pragma once

#include "ft/utils/iterator_traits.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/utils/utils.hpp"
#include "ft/RBT/red_black_tree.hpp"

namespace ft {

// https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/ 
template <typename Val, typename Node > 
class rb_tree_iterator {

  public:

  typedef Val                                               value_type;
  typedef value_type&                                       reference;
  typedef value_type*                                       pointer;
  typedef bidirectional_iterator_tag                        iterator_category;
  typedef ptrdiff_t                                         difference_type;
  typedef typename ft::iterator_traits<Node>::pointer       node_ptr;
  typedef const node_ptr                                    const_node_ptr;
  typedef size_t                                            size_type;
  typedef rb_tree_iterator                                  self;

  private:

  node_ptr node;
  node_ptr node_end;

  public:

  rb_tree_iterator() {}

  rb_tree_iterator(const rb_tree_iterator& it)
  :
    node(it.base()),
    node_end(it.get_node_end())
  {}

  template < typename UVal, typename UPtr >
  rb_tree_iterator(const rb_tree_iterator<UVal, UPtr>& it)
  :
    node(it.base()),
    node_end(it.get_node_end())
  {}

  rb_tree_iterator(node_ptr start, node_ptr end)
  :
    node(start),
    node_end(end)
  {}

  template <typename UVal, typename UPtr>
  rb_tree_iterator& operator=( const rb_tree_iterator<UVal, UPtr>& other) {
    if (this != &other) {
      this->node = other.node;
      this->node_end = other.node_end;
    }
    return *this;
  }

  node_ptr base() const {
    return node;
  }

  node_ptr get_node_end() const {
    return node_end;
  }

  reference operator*() const {
    return node->data;
  }

  pointer operator->() const {
    return &node->data;
  }

  /* Given the following tree
   *
   *                     1.1
   *                  /      \
   *               /            \
   *            /                  \
   *          2.1                 2.2
   *       /       \           /       \
   *     3.1       3.2       3.3       3.4
   *    /   \     /   \     /   \     /   \
   *  4.1  4.2  4.3  4.4  4.5  4.6  4.7  4.8
   * 
   * Iterators point towards nodes, from begin() to end(), like:
   * 4.1, 3.1, 4.2, 2.1, 4.3, 3.2, 4.4, 1.1, 4.5, 3.3, 4.6, 2.2, 4.7, 3.4, 4.8
   */
  self& operator++() {
    if (node == node_end) {
      node = node->left; // node_end->left contains de minimum value
      return *this;
    }
    if (node->right != node_end) {
      node = node->right;
      while (node->left != node_end) {
        node = node->left;
      }
    // else, go up until we are a node which is not its parents' right child
    } else {
      node_ptr maybe_next = node->parent;
      while (maybe_next->right == node) {
        node = maybe_next;
        maybe_next = maybe_next->parent;
      }
      node = maybe_next;
    }
    return *this;
  }

  // it++
  self operator++(int) {
    self t = *this;
    this->operator++();
    return t;
  }

  /* This has perfect symmetry with the ++ case. Switch left/right.
  */
  self& operator--() {
    if (node == node_end) {
      node = node->right; // node_end->right contains the maximum value.
      return *this;
    }
    if (node->left != node_end) {
      node = node->left;
      while (node->right != node_end) {
        node = node->right;
      }
    // else, go up until we are a node which
    // is not its parents' left child
    } else {
      node_ptr maybe_next = node->parent;
      while (maybe_next->left == node) {
        node = maybe_next;
        maybe_next = maybe_next->parent;
      }
      node = maybe_next;
    }
    return *this;
  }

  self operator--(int) {
    self t = *this;
    this->operator--();
    return t;
  }

};

template < typename UVal, typename UPtr, typename VVal, typename VPtr > 
bool operator==(const rb_tree_iterator<UVal, UPtr>& lhs,
                const rb_tree_iterator<VVal, VPtr>& rhs)
{
  return lhs.base() == rhs.base();
}

template < typename UVal, typename UPtr, typename VVal, typename VPtr > 
bool operator!=(const rb_tree_iterator<UVal, UPtr>& lhs,
                const rb_tree_iterator<VVal, VPtr>& rhs)
{
  return lhs.base() != rhs.base();
}

} // namespace ft


#endif /* FT_CONTAINERS_RED_BLACK_TREE_NODE_ITERATOR */