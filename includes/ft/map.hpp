#ifndef CONTAINERS_MAP_HPP
# define CONTAINERS_MAP_HPP
#pragma once

#include <ft/RBT/red_black_tree.hpp>
#include <ft/utils/pair.hpp>
#include <ft/utils/utils.hpp>

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

  tree_type tree;

  public:

  map()
  :
    tree()
  {}

  explicit map( const Compare& comp,
                const Allocator& alloc = Allocator())
  :
    tree(comp, alloc)
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
    tree(comp, alloc)
  {
    while (first != last) {
      tree.insert(*first);
      first++;
    }
  }

  map( const map& other )
  :
    tree(other.tree)
  {}

  

  
}; // class ft::map

} // namespace 

#endif /* CONTAINERS_MAP_HPP */