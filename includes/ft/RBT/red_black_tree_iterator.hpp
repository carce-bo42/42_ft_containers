#ifndef RBT_NODE_ITERATOR
# define RBT_NODE_ITERATOR

#include "ft/utils/iterator_traits.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/utils/utils.hpp"

namespace ft {

//  https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/ 
// why use nil https://cs.stackexchange.com/questions/44422/what-is-the-purpose-of-using-nil-for-representing-null-nodes
template <typename Val, typename Node = rb_tree_node<Val> > 
class rb_tree_iterator {

  typedef Val         value_type;
  typedef value_type& reference;
  typedef value_type* pointer;

  private:

  Node* node;

  public:

  rb_tree_iterator() {}

  template < typename U >
  rb_tree_iterator(const rb_tree_iterator<U>& it,
                   typename ft::enable_if<
                            ft::is_same_type<
                     typename rb_tree_iterator<U>::value_type,
                              value_type>::value,
                            value_type>::type* = 0 )
  :
    node(it.node)
  {}

  rb_tree_iterator(Node* start)
  :
    node(start)
  {}

  Node* base() const {
    return node;
  }

  rb_tree_iterator& operator=( const rb_tree_iterator& other) {
    if (this != other) {
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
  rb_tree_iterator& operator++() {
    Node* save = node;
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
    // else, go up until we are a node which is not its parents' right child
    } else {
      if (node->parent) {
        Node* maybe_next = node->parent;
        while (maybe_next->right == node) {
          node = maybe_next;
          if (maybe_next->parent) {
            maybe_next = maybe_next->parent;
          } else {
            // case we got to the root
            node = save;
            return *this;
          }
        }
        node = maybe_next;
      }
    }
    return *this;
  }

  // it++
  rb_tree_iterator operator++(int) {
    rb_tree_iterator t = *this;
    this->operator++();
    return t;
  }

  /* This has perfect symmetry with the ++ case. Switch left/right.
  */
  rb_tree_iterator& operator--() {
    Node* save = node;
    if (node->left) {
      node = node->left;
      while (node->right) {
        node = node->right;
      }
    // else, go up until we are a node which
    // is not its parents' left child
    } else {
      if (node->parent) {
        Node* maybe_next = node->parent;
        while (maybe_next->left == node) {
          node = maybe_next;
          if (maybe_next->parent) {
            maybe_next = maybe_next->parent;
          } else {
            // case we got to the root
            node = save;
            return *this;
          }
        }
        node = maybe_next;
      }
    }
    return *this;
  }

  rb_tree_iterator operator--(int) {
    rb_tree_iterator t = *this;
    this->operator--();
    return t;
  }

};

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool	operator==(const rb_tree_iterator<KeyX,ValX>& x,
                  const rb_tree_iterator<KeyY,ValY>& y)
{
  return x.base() == y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool	operator!=(const rb_tree_iterator<KeyX,ValX>& x,
                  const rb_tree_iterator<KeyY,ValY>& y)
{
  return x.base() != y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool		operator>(const rb_tree_iterator<KeyX,ValX>& x,
                  const rb_tree_iterator<KeyY,ValY>& y)
{
  return x.base() > y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool operator<(const rb_tree_iterator<KeyX,ValX>& x,
                const rb_tree_iterator<KeyY,ValY>& y)
{
  return x.base() < y.base();
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool operator>=(const rb_tree_iterator<KeyX,ValX>& x,
                const rb_tree_iterator<KeyY,ValY>& y)
{
  return !(x.base() < y.base());
}

template <typename KeyX, typename KeyY, typename ValX, typename ValY>
bool operator<=(const rb_tree_iterator<KeyX,ValX>& x,
                const rb_tree_iterator<KeyY,ValY>& y)
{
  return !(x.base() > y.base());
}

} // namespace ft


#endif /* # define RBT_NODE_ITERATOR */