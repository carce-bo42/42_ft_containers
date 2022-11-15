#ifndef CONTAINERS_MAP_HPP
# define CONTAINERS_MAP_HPP
#pragma once

#include <ft/RBT/red_black_tree.hpp>
#include <ft/utils/pair.hpp>
#include <ft/utils/utils.hpp>
#include <stdexcept>

namespace ft {

template < typename Key,
           typename T,
           typename Val = ft::pair<const Key, T>,
           typename Compare = std::less<Key>,
           typename Allocator = std::allocator<Val> >
class map {

  public:

  typedef Key                                        key_type;
  typedef T                                          mapped_type;
  typedef ft::pair<const Key, T>                     value_type;
  typedef size_t                                     size_type;
  typedef Compare                                    key_compare;
  typedef Allocator                                  allocator_type;
  typedef value_type&                                reference;
  typedef const value_type&                          const_reference;
  typedef typename Allocator::pointer                pointer;
  typedef typename Allocator::const_pointer          const_pointer;

  typedef rb_tree<Key, Val,
                  map_get_key<Key, Val>,
                  Compare,
                  Allocator >                        tree_type;
  typedef typename tree_type::iterator               iterator;
  typedef typename tree_type::const_iterator         const_iterator;
  typedef typename tree_type::reverse_iterator       reverse_iterator;
  typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

  private:

  typedef typename tree_type::node_ptr               node_ptr;

  // This allows map interface to use tree's private member variables
  // and functions. 
  template < typename A, typename B, typename C,
             typename D, typename E >
  friend class ft::rb_tree;

  tree_type      tree;
  allocator_type allocator; // useless, but needed for get_allocator.

  public:

  map()
  :
    tree(),
    allocator()
  {}

  explicit map( const Compare& comp,
                const Allocator& alloc = Allocator())
  :
    tree(comp),
    allocator(alloc)
  {}

  template< class InputIt >
  map( InputIt first, InputIt last,
      const Compare& comp = Compare(),
      const Allocator& alloc = Allocator(),
      typename ft::enable_if<
                 ft::is_same_type<
          typename InputIt::value_type,
                   value_type>::value,
                 value_type>::type* = 0 )
  :
    tree(comp),
    allocator(alloc)
  {
    while (first != last) {
      tree.insert(*first);
      first++;
    }
  }

  map( const map& other )
  :
    tree(other.tree),
    allocator(other.alloc)
  {}

  ~map() {}

  map& operator=( const map& other ) {
    if (this != &other) {
      clear();

    }
  }

  allocator_type get_allocator() const {
    return allocator;
  }

  T& at( const Key& key ) {
    node_ptr n = tree.find(key);
    if (!n) {
      throw std::out_of_range("ft::map::at( const Key& Key )");
    }
    return n->data->second;
  }

  const T& at( const Key& key ) const {
    node_ptr n = tree.find(key);
    if (!n) {
      throw std::out_of_range("ft::map::at( const Key& Key )");
    }
    return n->data->second;
  }

  T& operator[]( const Key& key ) {
    node_ptr n = tree.find(key);
    if (!n) {
      tree.insert(value_type(key, T()));
    }
  }

  void clear() {
    tree.delete_subtree(tree._root);
  }







  
}; // class ft::map

} // namespace 

#endif /* CONTAINERS_MAP_HPP */