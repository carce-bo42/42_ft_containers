#ifndef CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
# define CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#pragma once

#include "ft/utils/iterator_traits.hpp"
#include <stddef.h> /* NULL */

/* Ref: https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
 * This would inherit from bidirectional iterator, and implement only what
 * the bidirectional iterator does not have. My implementation will consider
 * random_access_iterator as the most atomized iterator.
 */

namespace ft {

template < typename T >
class random_access_iterator {

  public :
  typedef typename ft::iterator_traits<T>::value_type      value_type;
  typedef typename ft::iterator_traits<T>::difference_type difference_type;
  typedef typename ft::iterator_traits<T>::pointer         pointer;
  typedef typename ft::iterator_traits<T>::reference       reference;
  typedef typename ft::random_access_iterator_tag          iterator_category;

  private :

    pointer   _ptr;

  public :

    random_access_iterator()
    :
      _ptr(NULL)
    {}

    random_access_iterator(pointer ptr)
    :
      _ptr(ptr)
    {}

    template < typename U > 
    random_access_iterator(const random_access_iterator<U>& it)
    :
      _ptr(it.base())
    {}

    random_access_iterator &operator=(const random_access_iterator& rhs) {
      if(*this != rhs) {
        this->_ptr = rhs.base();
      }
      return *this;
    }

    virtual ~random_access_iterator() {}

    /* A more friendly class to access the internal pointer,
      * (we could just use the -> operator but it is weird 
      * syntax to write it.operator->() every time we want _ptr)
      */
    pointer base() const {
      return _ptr;
    }

    reference operator*() const {
      return *_ptr;
    }

    pointer operator->() const {
      return _ptr;
    }

    reference operator[](difference_type n) {
      return *(_ptr + n);
    }

    random_access_iterator& operator++() {
      ++_ptr;
      return *this;
    }

    random_access_iterator& operator--() {
      --_ptr;
      return *this;
    }

    random_access_iterator operator++(int) {
      random_access_iterator _tmp = *this;
      ++_ptr;
      return _tmp;
    }

    random_access_iterator operator--(int) {
      random_access_iterator _tmp = *this;
      --_ptr;
      return _tmp;
    }

    random_access_iterator operator+(difference_type n) const {
      return random_access_iterator(_ptr + n);
    }

    random_access_iterator operator-(difference_type n) const {
      return random_access_iterator(_ptr - n);
    }

    random_access_iterator& operator+=(difference_type n) const {
      _ptr += n;
      return *this;
    }

    random_access_iterator& operator-=(difference_type n) const {
      _ptr -= n;
      return *this;
    }

}; /* class random_access_iterator */

template < typename U, typename V >
bool operator!=(const random_access_iterator<U>& lhs,
                const random_access_iterator<V>& rhs)
{
  return lhs.base() != rhs.base();
}

template < typename U, typename V >
bool operator==(const random_access_iterator<U>& lhs,
                const random_access_iterator<V>& rhs)
{
  return lhs.base() == rhs.base();
}

template < typename U, typename V >
bool operator>(const random_access_iterator<U>& lhs,
                const random_access_iterator<V>& rhs)
{
  return lhs.base() > rhs.base();
}

template < typename U, typename V >
bool operator<(const random_access_iterator<U>& lhs,
                const random_access_iterator<V>& rhs)
{
  return lhs.base() < rhs.base();
}

template < typename U, typename V >
bool operator>=(const random_access_iterator<U>& lhs,
                const random_access_iterator<V>& rhs)
{
  return lhs.base() >= rhs.base();
}

template < typename U, typename V >
bool operator<=(const random_access_iterator<U>& lhs,
                const random_access_iterator<V>& rhs)
{
  return lhs.base() <= rhs.base();
}

} /* namespace ft */

#endif /* CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP */