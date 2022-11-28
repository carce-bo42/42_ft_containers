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
           typename Compare = std::less<Key>,
           typename Allocator = std::allocator<ft::pair<const Key, T> > >
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

  typedef struct ValueCompare {

    map_get_key<Key, value_type> get_key;
    key_compare           key_cmp;

    bool operator()(const value_type& x, const value_type& y) {
      return key_cmp(get_key(x), get_key(y));
    }

  } value_compare;

  private:

  typedef rb_tree<Key, value_type,
                  map_get_key<Key, value_type>,
                  Compare,
                  Allocator >                        tree_type;
  typedef typename tree_type::node_ptr               node_ptr;

  tree_type      tree;
  allocator_type allocator;
  value_compare  value_cmp;

  public:

  typedef typename tree_type::iterator               iterator;
  typedef typename tree_type::const_iterator         const_iterator;
  typedef typename tree_type::reverse_iterator       reverse_iterator;
  typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

  map()
  :
    tree(),
    allocator(),
    value_cmp()
  {}

  explicit map( const Compare& comp,
                const Allocator& alloc = Allocator())
  :
    tree(comp),
    allocator(alloc),
    value_cmp()
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
    allocator(alloc),
    value_cmp()
  {
    insert(first, last);
  }

  map( const map& other )
  :
    tree(other.tree),
    allocator(other.allocator),
    value_cmp(other.value_cmp)
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
    return n->data.second;
  }

  const T& at( const Key& key ) const {
    node_ptr n = tree.find(key);
    if (!n) {
      throw std::out_of_range("ft::map::at( const Key& Key )");
    }
    return n->data.second;
  }

  T& operator[]( const Key& key ) {
    node_ptr n = tree.find(key);
    if (!n) {
      // tree.insert(pair).first == iterator
      // *iterator = node->data
      // node->data.second = mapped_type.
      return (*tree.insert(value_type(key, T())).first).second;
    }
    return n->data.second;
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
    return tree.empty();
  }

  size_type size() const {
    return tree.size();
  }

  size_type max_size() const {
    return tree.max_size();
  }

  inline void clear() {
    tree.clear();
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
      ++first;
    }
  }

  void erase( iterator pos ) {
    if (pos != end()) {
      tree.erase((*pos).first);
    }
  }

  // This does not invalidate iterators because we substitute
  // for inorder PREDECESSOR and an rb_tree iterator always ends
  // up with greater key values when incrementing.
  void erase( iterator first, iterator last ) {
    while (first != last) {
      tree.erase((*first++).first);
    }
  }
  
  size_type erase( const Key& key ) {
    if (tree.erase(key)) {
      return 1;
    }
    return 0;
  }

  void swap(map& other) {
    ft::swap(allocator, other.allocator);
    tree.swap(other.tree);
  }

  size_type count( const Key& key ) const {
    node_ptr n = tree.find(key);
    if (n) {
      return 1;
    }
    return 0;
  }

  iterator find( const Key& key ) {
    node_ptr n = tree.find(key);
    if (n) {
      return iterator(n, tree.get_node_end());
    }
    return end();
  }

  const_iterator find( const Key& key ) const {
    node_ptr n = tree.find(key);
    if (n) {
      return const_iterator(n, tree.get_node_end());
    }
    return end();
  }

  /*
   * Returns a range containing all elements with the given key in the
   * container. The range is defined by two iterators, one pointing to
   * the first element that is not less than key and another pointing
   * to the first element greater than key
   */
  ft::pair<iterator,iterator> equal_range( const Key& key ) {
    return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
  }

  ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
    return ft::pair<const_iterator,
                    const_iterator>(lower_bound(key), upper_bound(key));
  }

  /*
   * Returns an iterator pointing to the first element that is not
   * less than (i.e. greater or equal to) key.
   */
  inline iterator lower_bound( const Key& key ) {
    return tree.lower_bound(key);
  }

  inline const_iterator lower_bound( const Key& key ) const {
    return tree.lower_bound(key);
  }

  /*
   * Returns an iterator pointing to the first element that is
   * greater than key.
   */
  inline iterator upper_bound( const Key& key ) {
    return tree.upper_bound(key);
  }

  inline const_iterator upper_bound( const Key& key ) const {
    return tree.upper_bound(key);
  }

  key_compare key_comp() const {
    return tree.key_cmp;
  }

  value_compare value_comp() const {
    return value_cmp;
  }
  
}; // class ft::map

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& x,
                 const ft::map<Key,T,Compare,Alloc>& y )
{
  return x.size() == y.size()
         && ft::equal(x.begin(), x.end(), y.begin());
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& x,
                 const ft::map<Key,T,Compare,Alloc>& y )
{
  return !(x == y);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& x,
                const ft::map<Key,T,Compare,Alloc>& y )
{
  return ft::lexicographical_compare(x.begin(), x.end(),
                                     y.begin(), y.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& x,
                const ft::map<Key,T,Compare,Alloc>& y )
{
  return y < x;
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& x,
                 const ft::map<Key,T,Compare,Alloc>& y )
{
  return !(x > y);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& x,
                 const ft::map<Key,T,Compare,Alloc>& y )
{
  return !(x < y);
}

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& x,
           ft::map<Key,T,Compare,Alloc>& y )
{
  return x.swap(y);
}


} // namespace 

#endif /* CONTAINERS_MAP_HPP */