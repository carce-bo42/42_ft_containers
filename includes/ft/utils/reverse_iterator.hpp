#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
#pragma once

#include "ft/utils/iterator_traits.hpp"

/* 
 * See
 * - https://en.cppreference.com/w/cpp/iterator/reverse_iterator
 * 
 * Cool explanation of reverse_iterator functionality:
 * - https://stackoverflow.com/questions/16609041/c-stl-what-does-base-do
 */

namespace ft {

template < class I >
class reverse_iterator {

  public :

  typedef I                                                  iterator_type;
  typedef typename ft::iterator_traits<I>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<I>::value_type        value_type;
  typedef typename ft::iterator_traits<I>::difference_type   difference_type;
  typedef typename ft::iterator_traits<I>::pointer           pointer;
  typedef typename ft::iterator_traits<I>::reference         reference;

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

  template <typename U>
  reverse_iterator(const reverse_iterator<U>& other,
                   typename ft::enable_if<
                              ft::is_same_type<
                       typename reverse_iterator<U>::value_type,
                                value_type>::value,
                              value_type>::type* = 0 )
  : 
    _ptr(other.base())
  {}
  
  virtual ~reverse_iterator() {}

  iterator_type base() const {
    return _ptr ;
  }

  reverse_iterator& operator=( const reverse_iterator& other) {
    if (this != &other) {
      _ptr = other._ptr;
    }
    return *this;
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
    return reverse_iterator(_ptr - n);
  }

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(_ptr + n);
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

template < typename U, typename V >
bool operator!=(const reverse_iterator<U>& lhs,
                const reverse_iterator<V>& rhs)
{
  return lhs.base() != rhs.base();
}

template < typename U, typename V >
bool operator==(const reverse_iterator<U>& lhs,
                const reverse_iterator<V>& rhs)
{
  return lhs.base() == rhs.base();
}

template < typename U, typename V >
bool operator>(const reverse_iterator<U>& lhs,
                const reverse_iterator<V>& rhs)
{
  return lhs.base() > rhs.base();
}

template < typename U, typename V >
bool operator<(const reverse_iterator<U>& lhs,
                const reverse_iterator<V>& rhs)
{
  return lhs.base() < rhs.base();
}

template < typename U, typename V >
bool operator>=(const reverse_iterator<U>& lhs,
                const reverse_iterator<V>& rhs)
{
  return lhs.base() >= rhs.base();
}

template < typename U, typename V >
bool operator<=(const reverse_iterator<U>& lhs,
                const reverse_iterator<V>& rhs)
{
  return lhs.base() <= rhs.base();
}

/*
 * Allows :
 * (rit1 +/- rit2) to work as an arithmetic value.
 * Two typenames are included for const T / T workarounds.
 */

template < typename U, typename V > 
typename reverse_iterator<U>::difference_type
operator+(const reverse_iterator<U>& lhs,
          const reverse_iterator<V>& rhs)
{
  return (lhs.base() + rhs.base());
}

template < typename U, typename V > 
typename reverse_iterator<U>::difference_type
operator-(const reverse_iterator<U>& lhs,
          const reverse_iterator<V>& rhs)
{
  return (lhs.base() - rhs.base());
}

// Reorder arguments to call inner operator- (iterator at left)
template <typename T>
reverse_iterator<T>
operator-(typename ft::reverse_iterator<T>::difference_type n,
          reverse_iterator<T> it)
{
  return (it - n);
}

template <typename T>
reverse_iterator<T>
operator+(typename ft::reverse_iterator<T>::difference_type n,
          reverse_iterator<T> it)
{
  return (it + n);
}

} /* namespace ft */

#endif /* REVERSE_ITERATOR_HPP */
