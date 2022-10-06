#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

#include <memory>
#include <functional>
#include "ft/RBT/red_black_tree_node.hpp"

namespace ft {

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
  
  typedef rb_tree_node<Val>*       node_ptr;
  typedef const rb_tree_node<Val>* const_node_ptr;

  private:

  node_ptr root;
  size_t   node_count;
  // possibly missing some variables for now.
  // balancing will be the last thing to do.

  public:

  typedef Key 				      key_type;
  typedef Val 				      value_type;
  typedef value_type*       pointer;
  typedef const value_type* const_pointer;
  typedef value_type& 			reference;
  typedef const value_type& const_reference;
  typedef size_t 				    size_type;
  typedef ptrdiff_t 			  difference_type;
  typedef Alloc 				    allocator_type;

/*
 * red black tree interface  
 * 
 * get_node_from_key()
 * get_node_key()
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




}; // class rbtree

} // namespace
#endif