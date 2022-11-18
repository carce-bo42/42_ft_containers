#ifndef CONTAINERS_VECTOR_HPP
# define CONTAINERS_VECTOR_HPP
#pragma once

#include <memory> /* std::allocator, std::allocator_traits. */
#include <cstddef> /* std::size_t, std::ptrdiff_t */
#include <stdexcept>
#include <limits>
#include "limits.h"

#include <iostream>

#include "ft/utils/utils.hpp"
#include "ft/utils/reverse_iterator.hpp"
#include "ft/utils/random_access_iterator.hpp"

/*
 * INFO : REFS
 * explicit keyword :
 * https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
 * 
 * allocator : 
 * https://www.youtube.com/watch?v=HcESuwmlHEY
 * https://www.youtube.com/watch?v=v-qePUHf8iU
 * https://en.cppreference.com/w/cpp/memory/allocator
 * https://stackoverflow.com/questions/59539057
 * https://stackoverflow.com/questions/53610332
 *                 
 * vector :
 * https://en.cppreference.com/w/cpp/container/vector/vector
 * 
 * extra :
 * https://www.youtube.com/watch?v=LIb3L4vKZ7U
 * 
 * On why size_type and difference_type are always the same (I use this a lot):
 * https://www.codeguru.com/cplusplus/about-size_t-and-ptrdiff_t/
 * 
 * How capacity works in vectors :
 * https://stackoverflow.com/questions/3167272/
 * https://stackoverflow.com/questions/24846348/
 * https://news.ycombinator.com/item?id=20872696
 * 
 * Summary: 
 * The vector MUST double its size to fulfill amortized constant
 * time insertion and deletion at the end. BUT the initial capacity
 * is implementation dependent.
 * 
 * 
 * On the <method>_dispatch : 
 * methods with a signature
 * 
 * ret func name(size_type, const value_type&)   (1)
 * 
 * that have an overload of the kind:
 *
 * template <typename InputIt>
 * ret func_name(InputIt, InputIt)     (2)
 * 
 * represent a problem when value_type = int, and the method is called
 * like so :
 * 
 * vector.func_name(10, 3); (3) // for a vector<int>. 
 * 
 * Because 10 has the same type as 3, and both are integers, the compiler
 * substitutes (2) in expression (3), when it should call (1). Notice how
 * SFINAE constructions of the type
 * 
 *    typename enable_if<is_integral<typename InputIt::value_type>::value,
 *                        InputIt>::type* = 0
 * 
 * Do not work on a general way, because the argument for is_integral does not
 * make sense when InputIt = int. One could then suggest the following other
 * SFINAE argument constructior : 
 * 
 *    typename enable_if<is_integral<It>::value, It>::type* = 0
 * 
 * But this wont work with iterators because iterators are not themselves integral,
 * it is its internal typedef value_type which is.
 * The problem is solved with the dispatch method. When the wrong function is
 * called, there is a type resolution for InputIt. If it is of type int,
 * the call is dispatched to the normal "fill method (size_t, const value_type&)".
 * Else, the appropiate "range_method (InputIt, InputIt)" is called.
 */

namespace ft {

template < class T, class Allocator = std::allocator<T> >
class vector {

  public:
  typedef T                                            value_type;
  typedef Allocator                                    allocator_type;
  typedef T*                                           pointer;
  typedef const T*                                     const_pointer;
  typedef typename Allocator::reference                reference;
  typedef typename Allocator::const_reference          const_reference;
  typedef std::size_t                                  size_type;
  typedef ptrdiff_t                                    difference_type; 
  
  typedef ft::random_access_iterator<pointer>          iterator;
  typedef ft::random_access_iterator<const_pointer>    const_iterator;
  typedef ft::reverse_iterator<iterator>               reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;

  private:

    allocator_type  _alloc;   // shortcut
    pointer         _d_start; // where the non-empty data begins
    pointer         _d_end;   // where the empty data begins
    size_type       _capacity;  // allocated objects

  /*
    * This function is assumed to never be called when
    * new_capacity = 0 or new_capacity < _capacity.
    * Doubles the current capacity until its greater than
    * new_capacity.
    * Does it have to deal with size_type overflow ?
    */
  size_type get_new_capacity( size_type new_capacity) {
    
    if (!_capacity) {
      return new_capacity;
    }

    if (!new_capacity || _capacity > new_capacity) {
      return _capacity;
    }
    
    if (new_capacity > _capacity) {
      if (size() * 2 >= new_capacity) {
        return size() * 2;
      } else if (_capacity * 2 >= new_capacity) {
        return _capacity * 2;
      } else {
        return new_capacity;
      }
    }
    return _capacity;
  }

  /* constructor that reserves capacity, but allocs empty 
   * size elements
   */
  vector( size_type capacity, size_type size, const T& value = T()) {
    if (capacity == size) {
      init_fill_vector(size);
    } else {
      _capacity = capacity;
      _d_start = _alloc.allocate(_capacity);
      _d_end = _d_start;
      while (--size) {
        _alloc.construct(_d_end, value);
        ++_d_end;
      }
    }
  }

  /* 
   * Creates a memory hole inside the vector. Used for 
   * insertion.
   */
  void create_mem_hole_at( size_type pos, size_type hole_size ) {
    
    if (hole_size == 0) {
      return ;
    }

    size_type new_size = size() + hole_size;

    if (new_size > _capacity) {
      size_type new_capacity = get_new_capacity(new_size);
      reserve(new_capacity);
    }
    /* shift end contents hole_size positions positions,
     * starting from the end to pos
     */
    for (size_type i = new_size - 1; i >= pos + hole_size; i--) {
      _alloc.construct(_d_start + i, _d_start[i - hole_size]);
      _alloc.destroy(_d_start + i - hole_size);
    }
    _d_end += hole_size; // resize
  }

  // Must See assign(InputIt first, InputIt last) comment
  template <typename InputIt>
  void assign_dispatch(InputIt first, InputIt last, false_type) {
    clear();
    size_type diff = ft::distance(first, last);
    if (diff > _capacity) {
      reserve(diff);
    }
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }

  template <typename InputIt>
  void assign_dispatch(InputIt first, InputIt last, true_type) {
    assign((size_type)first, last);
  }

  template <typename InputIt>
  iterator insert_dispatch(const_iterator pos,
                       InputIt first, InputIt last, false_type)
  {
    difference_type value_pos = pos.base() - _d_start;
    create_mem_hole_at(value_pos, ft::distance(first, last));
    for (size_type i = value_pos; first != last; first++) {
      _alloc.construct(_d_start + i, *first);
      i++;
    }
    return _d_start + value_pos;
  }

  template <typename InputIt>
  iterator insert_dispatch(const_iterator pos,
                           InputIt first, InputIt last, true_type)
  {
    return insert(pos, (size_type)first, last);
  }

  template <typename InputIt>
  void constructor_dispatch(InputIt first, InputIt last, false_type) {
    _capacity = (size_type)ft::distance(first, last);
    if (_capacity) {
      _d_start = _alloc.allocate(_capacity);
      _d_end = _d_start;
      while (first != last) {
        _alloc.construct(_d_end, *first);
        ++_d_end;
        ++first;  
      }
    }
  }

  template <typename InputIt>
  void constructor_dispatch(InputIt first, InputIt last, true_type) {
    init_fill_vector((size_type)first, last);
  }

  void init_fill_vector(size_type count, const T& value = T()) {
    _capacity = count;
    if (_capacity) {
      _d_start = _alloc.allocate(_capacity);
      _d_end = _d_start;
      while (count--) {
        _alloc.construct(_d_end, value);
        ++_d_end;
      }
    }
  }

  public:

  /* Default constructor. Constructs an empty container
    * with a default-constructed allocator.
    */
  vector ()
  :
    _alloc(allocator_type()),
    _d_start(0),
    _d_end(0),
    _capacity(0)
  {}
  
  /* Constructs the container with count copies of elements
    * with value value.
    */
  explicit vector( size_type count, const T& value = T(),
                  const Allocator& alloc = Allocator() )
  {
    _alloc = alloc;
    _d_start = 0;
    _d_end = 0;
    init_fill_vector(count, value);
  }

  /* Constructs the container with the contents of the
  * range [ first, last ).
  *
  * See:
  * https://en.cppreference.com/w/cpp/memory/allocator/allocate
  * https://en.cppreference.com/w/cpp/memory/allocator/construct
  */
  template< class InputIt >
  vector( InputIt first, InputIt last,
        const Allocator& alloc = Allocator())
  {
    _alloc = alloc;
    _d_start = 0;
    _d_end = 0;
    typedef typename ft::is_integer<InputIt> Integer;
    constructor_dispatch(first, last, Integer());
  }

  vector( const vector& other )
  :
    _alloc(other._alloc),
    _d_start(0),
    _d_end(0),
    _capacity(other._capacity)
  {
    if (_capacity) {
      _d_start = _alloc.allocate(other._capacity);
      _d_end = _d_start;
      _capacity = other._d_end - other._d_start;
      size_type current = 0;
      while (_d_end != _d_start + _capacity) {
        _alloc.construct(_d_end, other[current]);
        ++_d_end;
        ++current;
      }
    }
  }

  /*
  * Destructs the vector.
  * The destructors of the elements are called and the used
  * storage is deallocated. Note, that if the elements are
  * pointers, the pointed-to objects are not destroyed.
  * 
  * Note: Because this vector is strictly defined to use
  * Allocator = std::allocator, there is no need to change
  * the allocator.
  */
  ~vector() {
    clear();
    _alloc.deallocate(_d_start, _capacity);
  }

  vector& operator=( const vector& other ) {
    if (this != &other) {
      /* destroy all elements constructed and deallocate */
      clear();
      if (other.capacity() > _capacity) {
        _alloc.deallocate(_d_start, _capacity);
        _capacity = other.capacity();
        /* allocate and construct all new elements */
        _d_start = _alloc.allocate(_capacity);
      }
      _d_end = _d_start;
      size_type current = 0;
      while (_d_end != _d_start + other.size()) {
        _alloc.construct(_d_end, other[current]);
        ++_d_end;
        ++current;
      }
    }
    return *this;
  }

  /* Replaces the contents of the container. 
   * Replaces the contents with count copies of value value.
   */
  void assign( size_type count, const value_type& value ) {
    clear();
    if (count > _capacity) {
      reserve(count);
    }
    while (count) {
      push_back(value);
      --count;
    }
  }

  /* Replaces the contents of the container. 
    * Replaces the contents with copies of those in the range
    * [first, last). The behavior is undefined if either
    * argument is an iterator into *this.
    * Once again this only makes sense if the iterator
    * is of an integral type.
    */
  template< class InputIt >
  void assign( InputIt first, InputIt last) {
    typedef typename ft::is_integer<InputIt> Integer;
    assign_dispatch(first, last, Integer());
  }

  allocator_type get_allocator() const {
    return _alloc;
  }

  /* ------------------------------------------
    * Element access 
    */
  
  reference at( size_type pos ) {
    if (!(pos < size())) {
      throw std::out_of_range("ft::vector::at( size_type )");
    }
    return *(_d_start + pos);
  }

  const_reference at( size_type pos ) const {
    if (!(pos < size())) {
      throw std::out_of_range("ft::vector::at( size_type ) const");
    }
    return *(_d_start + pos);
  }

  reference operator[]( size_type pos ) {
    return _d_start[pos];
  }

  const_reference operator[]( size_type pos ) const {
    return _d_start[pos];
  }

  /* returns first element */
  reference front() {
    return _d_start[0];
  }

  const_reference front() const {
    return _d_start[0];
  }

  /* returns last element */
  reference back() {
    return _d_start[_d_end - _d_start - 1];
  }

  const_reference back() const {
    return _d_start[_d_end - _d_start - 1];
  }

  /* returns pointer to the underlying array serving as element
    * storage.
    */
  pointer data() {
    return _d_start;
  }

  const_pointer data() const {
    return _d_start;
  }

  /* ------------------------------------------
    * Iterators 
    */

  /*
    * Begin :
    * Returns an iterator to the first element of the vector.
    * If the vector is empty, the returned iterator will be equal to end().
    */
  iterator begin() {
    return iterator(_d_start);
  }

  const_iterator begin() const {
    return const_iterator(_d_start);
  }

  /*
    * End :
    * Returns an iterator to the element following the last element
    * of the vector. This element acts as a placeholder; attempting
    * to access it results in undefined behavior.
    */
  iterator end() {
    return iterator(_d_end);
  }

  const_iterator end() const {
    return const_iterator(_d_end);
  }

  /*
    * Returns a reverse iterator to the first element of the reversed vector.
    * It corresponds to the last element of the non-reversed vector.
    * If the vector is empty, the returned iterator is equal to rend().
    */
  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  /*
    * Returns a reverse iterator to the element following the last element
    * of the reversed vector. It corresponds to the element preceding the
    * first element of the non-reversed vector. 
    * This element acts as a placeholder, attempting to access it results
    * in undefined behavior.
    */
  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  /* Checks if the container has no elements. */
  bool empty() const {
    return _d_start == _d_end;
  }

  /*
    * Returns the number of elements in the container,
    * i.e. ft::distance(begin(), end()).
    */
  size_type size() const {
    return _d_end - _d_start;
  }
  
  /*
    * Returns the maximum number of elements the container is
    * able to hold due to system or library implementation limitations
    */
  size_type max_size() const {
    return _alloc.max_size();
  }

  /*
    * Increase the capacity of the vector (the total number of
    * elements that the vector can hold without requiring
    * reallocation) to a value that's greater or equal to new_cap.
    * If new_cap is greater than the current capacity(), new
    * storage is allocated, otherwise the function does nothing.
    * See :
    * https://en.cppreference.com/w/cpp/container/vector/reserve
    */
  void reserve( size_type new_cap ) {
    if (new_cap > max_size()) {
      throw std::length_error("42");
    }
    if (new_cap < _capacity) {
      return ;
    }
    // save current content on aux
    vector aux(*this);
    // free then assign and allocate new capacity
    clear();
    _alloc.deallocate(_d_start, _capacity);
    _capacity = new_cap;
    _d_start = _alloc.allocate(_capacity);
    _d_end = _d_start;
    // copy contents back
    size_type current = 0;
    while (_d_end != _d_start + aux.size()) {
      _alloc.construct(_d_end, aux[current]);
      ++_d_end;
      ++current;
    }
  }

  /*
    * Returns the number of elements that the container has
    * currently allocated space for.
    */
  size_type capacity() const {
    return _capacity;
  }

  /*
    * Erases all elements from the container.
    * After this call, size() returns zero.
    */
  void clear() {
    while (_d_end != _d_start) {
      --_d_end;
      _alloc.destroy(_d_end);
    }
  }

  /*
    * inserts value at pos. It does not
    * replace the current value.
    */
  iterator insert( const_iterator pos, const T& value ) {
    difference_type value_pos = pos.base() - _d_start;
    create_mem_hole_at(value_pos, 1);
    _alloc.construct(_d_start + value_pos, value);
    return _d_start + value_pos; 
  }

  /*
    * Inserts count values at pos.
    */
  iterator insert( const_iterator pos, size_type count, const T& value ) {
    difference_type value_pos = pos.base() - _d_start;
    create_mem_hole_at(value_pos, count);
    for ( ; count > 0; count--) {
      _alloc.construct(_d_start + value_pos + count - 1, value);
    }
    return _d_start + value_pos;
  }

  /*
    * Inserts values from first to last starting at pos.
    */
  template< class InputIt >
  iterator insert( const_iterator pos, InputIt first, InputIt last) {
    typedef typename ft::is_integer<InputIt> Integer;
    return insert_dispatch(pos, first, last, Integer());
  }

  /*
   * Removes the element at position pos.
   * Experimentally, capacity does never change with an erase call.
   */
  iterator erase( iterator pos ) {
    difference_type value_pos = pos.base() - _d_start;
    size_type current_size = size();

    // erase element at position 
    _alloc.destroy(_d_start + value_pos);
    // shift all elements after pos
    for (size_type i = value_pos; i < current_size - 1; i++) {
      _alloc.construct(_d_start + i, _d_start[i + 1]);
      _alloc.destroy(_d_start + i + 1);
    }
    --_d_end; // resize
    return _d_start + value_pos;
  }

  /*
    * Removes elements in range [first, last).
    */
  iterator erase( iterator first, iterator last ) {
    difference_type start = first.base() - _d_start;
    size_type erase_size = ft::distance(first, last);

    // erase all elements from [first, last)
    for (size_type i = start; first != last; first++) {
      _alloc.destroy(_d_start + i);
      ++i;
    }
    // protect from first == last
    if (erase_size != 0) {
      // shift all elements after pos erase_size positions
      for (size_type i = start; i < size() - erase_size; i++) {
        _alloc.construct(_d_start + i, _d_start[i + erase_size]);
        _alloc.destroy(_d_start + i + erase_size);
      }
    }
    _d_end -= erase_size;
    return _d_start + start;
  }
  
  /* 
    * Creates a new element at the last position
    * available on the vector.
    * Changes capacity if necessary.
    */
  void push_back( const T& value ) {
    if (size() + 1 >= _capacity) {
      size_type new_capacity = get_new_capacity(size() + 1);
      reserve(new_capacity);
    }
    _alloc.construct(_d_end, value);
    ++_d_end;
  }
  
  /* 
    * Destroys the last element from the vector.
    * Never changes capacity.
    */
  void pop_back() {
    if (size()) {
      --_d_end;
      _alloc.destroy(_d_end);
    }
  }

  /*
    * Forces size to be count. Adds new empzty elements 
    * or removes elements stored.
    */
  void resize( size_type count, T value = T() ) {
    if (count == size()) {
      return ;
    } else if (count < size()) {
      for (size_type i = count; i < size(); i++) {
        _alloc.destroy(_d_start + i);
      }
      _d_end -= size() - count;
    } else {
      if (count > _capacity) {
        size_type new_capacity = get_new_capacity(count);
        reserve(new_capacity);
      }
      for (size_type i = size(); i < count; i++) {
        _alloc.construct(_d_start + i, value);
      }
      _d_end += count - size();
    }
  }

  /*
    * Literally swap everything with some other vector.
    * Without swapping memory addresses of each vector, i.e.
    * vector* before_swap == vector* after_swap
    */
  void swap( vector& other ) {
    if (this != &other) {
      ft::swap(_alloc, other._alloc);
      ft::swap(_d_start, other._d_start);
      ft::swap(_d_end, other._d_end);
      ft::swap(_capacity, other._capacity);
    }
  }

}; /* class vector */

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& x,
                  const ft::vector<T,Alloc>& y )
{
  return x.size() == y.size()
          && ft::equal(x.begin(), x.end(), y.begin());
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& x,
                  const ft::vector<T,Alloc>& y )
{
  return !(x == y);
}

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& x,
                const ft::vector<T,Alloc>& y )
{
  return ft::lexicographical_compare(x.begin(), x.end(),
                                      y.begin(), y.end());
}

// (x <= y) == !(x > y).
template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& x,
                  const ft::vector<T,Alloc>& y )
{
  return !(x > y);
}

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& x,
                const ft::vector<T,Alloc>& y )
{
  return y < x;
}

// (x >= y) == !(x < y)
template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& x,
                  const ft::vector<T,Alloc>& y )
{
  return !(x < y);
}

template< class T, class Alloc >
void swap( ft::vector<T,Alloc>& x,
            ft::vector<T,Alloc>& y )
{
  x.swap(y);
}

} /* namespace ft */

#endif /* CONTAINERS_VECTOR_HPP */