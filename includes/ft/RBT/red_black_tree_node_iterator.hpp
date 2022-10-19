#ifndef RBT_NODE_ITERATOR
# define RBT_NODE_ITERATOR

#include "ft/utils/iterator_traits.hpp"
#include "ft/RBT/red_black_tree_node.hpp"

namespace ft {

//  https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/ 
// why use nil https://cs.stackexchange.com/questions/44422/what-is-the-purpose-of-using-nil-for-representing-null-nodes
template <typename Val, typename Node = rb_tree_node<Val> > 
class rb_tree_node_iterator {

  typedef Val&                  reference;
  typedef Val*                  pointer;
  typedef rb_tree_node_iterator iterator;

  private:

  Node* node;

  public:

  rb_tree_node_iterator() {}

  rb_tree_node_iterator(const rb_tree_node_iterator& it)
  :
    node(it.node)
  {}

  rb_tree_node_iterator(Node* start)
  :
    node(start)
  {}

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
  iterator& operator++() {
    Node* save = node;
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
    // else, go up until we are a node which
    // is not its parents' right child
    } else {
      if (node->parent) {
        Node* maybe_next = node->parent;
        // while the option (maybe next) has the node as right child
        while (maybe_next->right == node) {
          // assign current node to parent.
          node = maybe_next;
          // assign maybe_next to the parent of the current node
          if (maybe_next->parent) {
            maybe_next = maybe_next->parent;
          } else {
            // we got to the root
            break;
          }
          // repeat.
        }
        // asign node to the first right child which is not node
        if (maybe_next->right != node) {
          node = maybe_next->right;
        } else {
          node = save; // case it is the maximum (we went up until the root)
        }
      }
    }
    return *this;
  }

};

} // namespace ft


#endif /* # define RBT_NODE_ITERATOR */