#ifndef RBT_NODE_ITERATOR
# define RBT_NODE_ITERATOR

#include "ft/utils/iterator_traits.hpp"
#include "ft/RBT/red_black_tree_node.hpp"

namespace ft {

//  https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/ 
// why use nil https://cs.stackexchange.com/questions/44422/what-is-the-purpose-of-using-nil-for-representing-null-nodes
template <typename Val, typename Node = rb_tree_node<Val> > 
class rb_tree_node_iterator {

  typedef Val&    reference;
  typedef Val*    pointer;

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

};

} // namespace ft


#endif /* # define RBT_NODE_ITERATOR */