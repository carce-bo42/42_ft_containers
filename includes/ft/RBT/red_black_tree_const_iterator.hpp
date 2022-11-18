#ifndef RBT_NODE_CONST_ITERATOR
# define RBT_NODE_CONST_ITERATOR

#include "ft/utils/iterator_traits.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/utils/utils.hpp"
#include "ft/RBT/red_black_tree.hpp"

namespace ft {

//  https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/ 
// why use nil https://cs.stackexchange.com/questions/44422/what-is-the-purpose-of-using-nil-for-representing-null-nodes
template <typename Val, typename Node = rb_tree_node<Val> > 
class rb_tree_const_iterator {

  public:

  
  typedef Val                              value_type;
  typedef const value_type&                reference;
  typedef const value_type*                pointer;
  typedef ptrdiff_t                        difference_type;
  typedef bidirectional_iterator_tag       iterator_category;
  typedef rb_tree_const_iterator<Val>      self;
  typedef const Node*                      node_ptr;
  typedef size_t                           size_type;

  private:

  node_ptr node;
  node_ptr node_end;

  public:

  rb_tree_const_iterator() {}

  template < typename U >
  rb_tree_const_iterator(const rb_tree_const_iterator<U>& it,
                   typename ft::enable_if<
                            ft::is_same_type<
                     typename rb_tree_const_iterator<U>::value_type,
                              value_type>::value,
                            value_type>::type* = 0 )
  :
    node(it.base())
  {}

  rb_tree_const_iterator(node_ptr start, node_ptr end)
  :
    node(start),
    node_end(end)
  {}

  node_ptr base() const {
    return node;
  }

  self& operator=( const self& other) {
    if (this != &other) {
      this->node = other.node;
    }
    return *this;
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

  self operator+(size_type n) const {
    self ret(*this);
    while (n-- > 0) {
      ++ret;
    }
    return ret;
  }

  self operator-(size_type n) const {
    self ret(*this);
    while (n-- > 0) {
      --ret;
    }
    return ret;
  }

};

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool	operator==(const rb_tree_const_iterator<KeyX,ValX>& x,
                  const rb_tree_const_iterator<KeyY,ValY>& y)
{
  return x.base() == y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool	operator!=(const rb_tree_const_iterator<KeyX,ValX>& x,
                  const rb_tree_const_iterator<KeyY,ValY>& y)
{
  return x.base() != y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool		operator>(const rb_tree_const_iterator<KeyX,ValX>& x,
                  const rb_tree_const_iterator<KeyY,ValY>& y)
{
  return x.base() > y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool operator<(const rb_tree_const_iterator<KeyX,ValX>& x,
                const rb_tree_const_iterator<KeyY,ValY>& y)
{
  return x.base() < y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool operator>=(const rb_tree_const_iterator<KeyX,ValX>& x,
                const rb_tree_const_iterator<KeyY,ValY>& y)
{
  return !(x.base() < y.base());
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool operator<=(const rb_tree_const_iterator<KeyX,ValX>& x,
                const rb_tree_const_iterator<KeyY,ValY>& y)
{
  return !(x.base() > y.base());
}

/*
 * Allows :
 * (rit1 +/- rit2) to work as an arithmetic value.
 * Two typenames are included for const T / T workarounds.
 */
template < typename U, typename V > 
typename rb_tree_const_iterator<U>::difference_type
operator+(const rb_tree_const_iterator<U>& lhs,
          const rb_tree_const_iterator<V>& rhs)
{
  return (lhs.base() + rhs.base());
}

template < typename U, typename V > 
typename rb_tree_const_iterator<U>::difference_type
operator-(const rb_tree_const_iterator<U>& lhs,
          const rb_tree_const_iterator<V>& rhs)
{
  return (lhs.base() - rhs.base());
}

// Reorder arguments to call inner operator- (iterator at left)
template <typename T>
rb_tree_const_iterator<T>
operator-(typename ft::rb_tree_const_iterator<T>::difference_type n,
          rb_tree_const_iterator<T> it)
{
  return (it - n);
}

template <typename T>
rb_tree_const_iterator<T>
operator+(typename ft::rb_tree_const_iterator<T>::difference_type n,
          rb_tree_const_iterator<T> it)
{
  return (it + n);
}

} // namespace ft

#endif