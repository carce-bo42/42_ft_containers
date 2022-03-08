#ifndef UTILS_42_HPP
# define UTILS_42_HPP
# pragma once

#include <iterator>
#include "ft_containers/utils/iterator_traits.hpp"

/* 
 * See
 * - https://en.cppreference.com/w/cpp/iterator/reverse_iterator
 */

namespace ft {

  template < class Iter >
  class reverse_iterator {

    public :
    
      using iterator_type       = Iter;
      using iterator_category   = typename ft::iterator_traits<Iter>::iterator_category;
      using value_type          = typename ft::iterator_traits<Iter>::value_type;
      using difference_type     = typename ft::iterator_traits<Iter>::difference_type;
      using pointer             = typename ft::iterator_traits<Iter>::pointer;
      using reference           = typename ft::iterator_traits<Iter>::reference;
    
    private :

      iterator_type _ptr;
    
    public :

      reverse_iterator()
        :
          _ptr()
        {}

      explicit reverse_iterator(iterator_type x)
        :
          _ptr(x)
        {}

      template <class U>
      reverse_iterator(const reverse_iterator<U>& other)
        : 
          _ptr(other.base())
        {}
      
      virtual ~reverse_iterator() {}

      iterator_type base() const {
        return _ptr ;
      }

      /* 
        * From
        * https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator*
        * Return value : Reference or pointer to the element previous to current.
        */
      reference operator*() const {
        iterator_type _tmp = _ptr;
        return *(--_tmp) ;
      }

      pointer operator->() const {
        iterator_type _tmp = _ptr;
        return --_tmp ;
      }

      /*
       * From
       * https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator_at
       * Return value : A reference to the element at relative location,
       * that is, base()[-n-1].
       */
      reference operator[] (difference_type n) {
        return base()[-n-1];
      }

      /* Note :
       * When you tell a reverse_iterator to go forward, i.e. ++it / it++, 
       * it moves from greater memory addresses to smaller ones. The exact
       * opposite happens for --it / it-- . 
       */

      /* Also :
       * The following operators assume ++/--/+/-/+=/-=
       * are implemented in the iterator class it builds from. And that
       * iterator will have some memory address that will surely implement
       * these with sizeof(typename), in case you are wondering how does
       * this manages to work for any data type.
       */

      reverse_iterator& operator++() {
        --_ptr;
        return *this;
      }

      reverse_iterator& operator--() {
        ++_ptr;
        return *this;
      }

      reverse_iterator operator++(int) {
        reverse_iterator _tmp = *this;
        --_ptr;
        return _tmp;
      }

      reverse_iterator operator--(int) {
        reverse_iterator _tmp = *this;
        ++_ptr;
        return _tmp;
      }

      reverse_iterator operator+(difference_type n) const {
        return (reverse_iterator(_ptr - n));
      }

      reverse_iterator operator-(difference_type n) const {
        return (reverse_iterator(_ptr + n));
      }

      reverse_iterator& operator+=(difference_type n) {
        _ptr -= n;
        return *this;
      }

      reverse_iterator& operator-=(difference_type n) {
        _ptr += n;
        return *this;
      }

  }; /* class reverse_iterator */

} /* namespace ft */

#endif /* UTILS_42_HPP */
