#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

#include <memory>
#include <functional>
#include "ft/RBT/red_black_tree_node.hpp"

// KeyOfVal functor for rb_tree
template < typename Key,
           typename Val /* = ft::pair<Key, typename T> */ >
struct get_key {

  typedef ft::rb_tree_node<Val> node_type;

  Key operator()(const node_type* node) {
    return node->data.first;
  }

};

namespace ft {

/* To understand the allocator template :
 * https://gcc.gnu.org/bugzilla/attachment.cgi?id=34289
 * PD: search for '__alloc_traits'. Check the definition of 'struct rebind'
 * inside __alloc_traits, then search for 'struct rebind'.
 * Find the one inside class allocator. The STL tree calls the template inside __alloc_traits,
 * im calling the template inside std::allocator which is the same. 
 */

template < typename Key,
           typename Val, // Val is some implementation of a pair of values.
           typename KeyOfVal, // In stl, this is used presumably to generalize
                              // Val to any structure containing Key. With this
                              // functor you are supposed to operate on Val
                              // types to extract Keys.
                              // I like how this also hints how there must
                              // be a Key inside Val (Key Of Val).
           typename Compare = std::less<Key>, // functor
           typename Alloc = std::allocator<Val> >
class rb_tree {

  protected:
  
  typedef rb_tree_node<Val>                  node_type;
  typedef node_type*                         node_ptr;
  typedef const node_type*                   const_node_ptr;
  typedef rb_tree_node_color                 n_color;
  typedef rb_tree_node_orientation           n_orientation;
  // get another allocator.
  typedef typename Alloc::
          template rebind<node_type >::other node_allocator;

  public:

  typedef Key               key_type;
  typedef Val               value_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type&       reference;
  typedef const value_type& const_reference;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;
  typedef Alloc             allocator_type;

  private:

  node_ptr       root;
  node_ptr       current; // for recursion
  size_t         node_count;
  node_allocator node_alloc;
  Compare        key_cmp;
  KeyOfVal       key_of_val;

/*
 * red black tree interface  
 * 
 * get_node_from_key()
 * get_node_key is not implemented because get_key exists
 * get_node_data()
 * construct_node()
 * destroy_node()
 * search_node() given a key
 * get_minimum()
 * get_maximum()
 * /////// iterators go somewhere else
 * pure_insert() - insert a node on the tree 
 * pure_erase() - erase a node from the tree
 * after_insert_check() : will determine if a newly inserted
 *                        node is a problem and which problem
 *                        is it.
 * after_erase_check() : same but with deletion, in case theres
 *                       diferent conditions met. But will somehow
 *                       redirect it to rebalance in a way rebalance
 *                       is agnostic to wether an insertion or 
 *                       deletion happened.
 * rebalance() : will recieve a node and a problem to solve.
 *
 */
  public:

  rb_tree()
  :
    root(),
    current(),
    node_count(0),
    node_alloc()
  {
    current = root;
  }

  node_ptr construct_node(const Val& value,
                          const node_ptr parent,
                          n_orientation orientation,
                          n_color color )
  {
    node_ptr new_node = node_alloc.allocate(1);
    node_alloc.construct(new_node,
                         node_type(value, parent, orientation, color));
    return new_node;
  }

  void destroy_node(node_ptr node) {
    node_alloc.destroy(node);
    node_alloc.deallocate(node, 1);
  }

  // returns either the node or NULL.
  node_ptr get_node_from_key(Key key, node_ptr start) {

    if (start != NULL) {
      Key node_key = key_of_val(start);
      if (node_key == key) {
        node_ptr ret = start;
        start = root;
        return ret;
      } else if (key_cmp(node_key, key)) { // if n_key < key
        start = start->right;
      } else {
        start = start->left;
      }
      return get_node_from_key(key, start);
    } else {
      return NULL;
    }
  }

  Val get_node_data(node_ptr node) {
    return node->data;
  }

  Key get_maximum() {
    if (!root) {
      return Key(); // empty Key contructor
    }
    node_ptr aux = root;
    while (aux->right) {
      aux = aux->right;
    }
    return key_of_val(aux);
  }

  Key get_minimum() {
    if (!root) {
      return Key(); // empty Key contructor
    }
    node_ptr aux = root;
    while (aux->left) {
      aux = aux->left;
    }
    return key_of_val(aux);
  }

  /*
   * map insert methods return an iterator. 
   * So iterators have to be done.
   *
   */
  void pure_insert(node_ptr new_node) {
    if (!root) {
      root = new_node;
    } else {
      // ...
    }
  }

}; // class rbtree

} // namespace
#endif