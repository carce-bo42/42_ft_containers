#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "ft_containers/utils/iterator_traits.hpp"
#include <stddef.h> /* NULL */

/* Ref: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
 */

namespace ft {

  template < typename T >
  class random_access_iterator {

    public :

      using value_type        = typename ft::iterator_traits<T>::value_type;
      using difference_type   = typename ft::iterator_traits<T>::difference_type;
      using pointer           = typename ft::iterator_traits<T>::pointer;
      using reference         = typename ft::iterator_traits<T>::reference;
      using iterator_category = typename ft::random_access_iterator_tag;
      
    private :

      pointer   _ptr;

    public :

      random_access_iterator() : _ptr(NULL) {}

      template < typename U > 
      random_access_iterator(const random_access_iterator<U>& it)
      :
        _ptr(it.base())
      {}

      ~random_access_iterator() {}

  }; /* random_access_iterator */

} /* namespace ft */

#endif /* RANDOM_ACCESS_ITERATOR_HPP */