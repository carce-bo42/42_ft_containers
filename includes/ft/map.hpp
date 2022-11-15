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

  // This allows map interface to use tree's private member variables
  // and functions. 
  template < typename A, typename B, typename C,
             typename D, typename E >
  friend class ft::rb_tree;

  typedef typename tree_type::node_ptr               node_ptr;

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
    insert(first, last);
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
      insert(other.begin(), other.end());
    }
    return *this;
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
      return tree.insert(value_type(key, T())).first->second;
    }
    return n->data->second;
  }

  inline iterator begin() {
    return tree.begin();
  }

  inline const_iterator begin() const {
    return tree.begin();
  }

  inline reverse_iterator rbegin() {
    return tree.rbegin();
  }

  inline const_reverse_iterator rbegin() const {
    return tree.rbegin();
  }

  inline iterator end() {
    return tree.end();
  }

  inline const_iterator end() const {
    return tree.end();
  }

  inline reverse_iterator rend() {
    return tree.rend();
  }

  inline const_reverse_iterator rend() const {
    return tree.rend();
  }

  bool empty() const {
    return tree.node_count == 0;
  }

  size_type size() const {
    return tree.node_count;
  }

  size_type max_size() const {
    return tree.max_size();
  }

  inline void clear() {
    tree.delete_subtree(tree._root);
  }

  ft::pair<iterator, bool> insert( const value_type& value ) {
    return tree.insert(value);
  }

  iterator insert( iterator pos, const value_type& value ) {
    return tree.insert_with_hint(pos, value);
  }

  template< class InputIt >
  void insert( InputIt first, InputIt last,
              typename ft::enable_if<
                        ft::is_same_type<
                typename InputIt::value_type,
                          value_type>::value,
                        value_type>::type* = 0 )
  {
    while (first != last) {
      tree.insert(*first);
      first++;
    }
  }

  void erase( iterator pos ) {
    erase(pos.base());
  }

  // This does not invalidate iterators because we substitute
  // for inorder PREDECESSOR and an rb_tree iterator always ends
  // up with greater key values when incrementing.
  void erase( iterator first, iterator last ) {
    while (first != last) {
      tree.erase(first.base());
      first++;
    }
  }
  
  size_type erase( const Key& key ) {
    if (tree.erase(key)) {
      return 1;
    }
    return 0;
  }

  
}; // class ft::map

} // namespace 

#endif /* CONTAINERS_MAP_HPP */