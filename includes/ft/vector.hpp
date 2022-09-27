#ifndef CONTAINERS_VECTOR_HPP
# define CONTAINERS_VECTOR_HPP
#pragma once

#include <memory> /* std::allocator, std::allocator_traits. */
#include <cstddef> /* std::size_t, std::ptrdiff_t */
#include <stdexcept>
#include <limits>
#include "limits.h"

#include "ft/utils/utils.hpp"
#include "ft/utils/reverse_iterator.hpp"

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
 * Explanation for the
 *     typename enable_if<is_integral<T>::value, T>::type = T :
 * This function is only to be used in case the type is integral.
 * enable_if<cond, T> accepts a boolean that, in case it is true,
 * gives a value of T to its inner variable type.
 * It is essentially saying that "If this T is an integral
 * type, enable_if should have an inside type of T". So
 * forcing here that enable_if< ... >::type = T is like 
 * saying "I only want this to be looked into in case the enable_if
 * type is T", which only happens if indeed the T is
 * an integral type.
 * Edit : 
 * So the syntax for C++98 is
 *     typename enable_if<!is_integral<T>::value, T>::type* = 0,
 * which is basically, taking into account the logic explained earlier,
 * negating that a pointer to enable_if<...>::type does not exist.
 * Which means if a pointer to enable_if<...>::type exists, is then
 * not 0, so T is integral. 
 * the pointer 
 */

namespace ft {

  template < class T, class Allocator = std::allocator<T> >
  class vector {

    public:
    typedef T                                             value_type;
    typedef Allocator                                     allocator_type;
    typedef typename Allocator::pointer                   pointer;
    typedef typename Allocator::const_pointer             const_pointer;
    typedef typename Allocator::reference                 reference;
    typedef typename Allocator::const_reference           const_reference;
    typedef typename Allocator::size_type                 size_type;
    typedef typename Allocator::difference_type           difference_type;
    /*
    typedef typename ft::vector_iterator<pointer>         iterator;
    typedef typename ft::vector_iterator<const_pointer>   const_iterator;
    typedef typename ft::reverse_iterator<iterator>       reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
    */

    private:

      allocator_type  _alloc;   // shortcut
      pointer         _d_start; // where the non-empty data begins
      pointer         _d_end;   // where the empty data begins
      size_type       _capacity;  // allocated objects

    /* 
     * Function that returns the smallest size_type number higher than 
     * new_capacity that is a power of two.
     * 
     * Check out: 
     * https://stackoverflow.com/questions/364985
     * 
     * __builtin_clz Counts Leading Zero bits on a variable, its 
     * a gcc builtin, check:
     * https://stackoverflow.com/questions/9353973
     * 
     * The -1 at the argument in __builtin_clz is to return new_capacity
     * in case the number is already a power of 2.
     */
    static size_type compute_new_capacity( size_type new_capacity ) {

      if (!new_capacity) {
        return 0;
      }
      // using uint as size_type (32-bit)
      if (sizeof(size_type) == 4) {
        return 1 << ((sizeof(size_type)*CHAR_BIT)
                        - __builtin_clz(new_capacity-1));
      // using ulong as size_type (64-bit)
      } else {
        return 1UL << ((sizeof(size_type)*CHAR_BIT)
                        - __builtin_clz(new_capacity-1));
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
    
    explicit vector ( const allocator_type& alloc = allocator_type() )
    :
      _alloc(alloc),
      _d_start(0),
      _d_end(0),
      _capacity(0)
    {}
    
    /* Constructs the container with count copies of elements
     * with value value.
     */
    explicit vector( size_type count, const T& value = T(),
                    const Allocator& alloc = Allocator() )
    :
      _alloc(alloc),
      _d_start(0),
      _d_end(0),
      _capacity(compute_new_capacity(count))
    {
      if (_capacity) {
        _d_start = _alloc.allocate(_capacity);
        _d_end = _d_start;
        while (count--) {
          _alloc.construct(_d_end, value);
          ++_d_end;
        }
      }
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
          const Allocator& alloc = Allocator(),
          typename enable_if<!is_integral<InputIt>::value,
                             InputIt>::type* = 0 )
    :
      _alloc(alloc),
      _d_start(0),
      _d_end(0),
      _capacity(compute_new_capacity(distance(first, last)))
    {
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

    vector( const vector& other )
    :
      _alloc(other.alloc),
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
        _alloc.deallocate(_d_start, _capacity);
        /* allocate and construct all new elements */
        _d_start = _alloc.allocate(other._capacity);
        _d_end = _d_start;
        _capacity = other._d_end - other._d_start;
        size_type current = 0;
        while (_d_end != _d_start + _capacity) {
          _alloc.construct(_d_end, other[current]);
          ++_d_end;
          ++current;
        }
        /* finally assign correct size */
        _capacity = other._capacity;
      }
    }

    /* Replaces the contents of the container. 
     * Replaces the contents with count copies of value value.
     */
    void assign( size_type count, const T& value ) {
      clear();
      if (count > _capacity) {
        _alloc.deallocate(_d_start, _capacity);
        _capacity = compute_new_capacity(count);
        _alloc.allocate(_capacity);
      }
      while (count) {
        _alloc.construct(_d_end, value);
        ++_d_end;
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
    void assign( InputIt first, InputIt last,
                 typename enable_if<!is_integral<InputIt>::value,
                                    InputIt>::type* = 0 )
    {
      clear();
      size_type diff = distance(first, last);
      if (diff > _capacity) {
        _alloc.deallocate(_d_start, _capacity);
        _capacity = compute_new_capacity(diff);
        _alloc.allocate(_capacity);
      }
      while (first != last) {
        _alloc.construct(*first);
        ++first;
        ++_d_end;
      }
    }

    allocator_type get_allocator() const {
      return _alloc;
    }

    /* ------------------------------------------
     * Element access 
     */

    reference at( size_type pos ) {
      return this[pos];
    }

    const_reference at( size_type pos ) const {
      return this[pos];
    }

    reference operator[]( size_type pos ) {
      if (pos >= size()) {
        throw std::out_of_range();
      }
      return _d_start[pos];
    }

    const_reference operator[]( size_type pos ) const {
      if (pos >= size()) {
        throw std::out_of_range();
      }
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
     * Returns the number of elements that the container has
     * currently allocated space for.
     */
    size_type capacity() const {
      return _capacity;
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
        throw std::length_error();
      }
      if (new_cap <= _capacity) {
        return ;
      }
      // save current content on aux
      vector aux(*this);
      // free then assign and allocate new capacity
      clear();
      _capacity = compute_new_capacity(new_cap);
      _alloc.allocate(_capacity);
      // copy contents back
      size_type current = 0;
      while (_d_end != _d_start + aux.size()) {
        _alloc.construct(_d_end, aux[current]);
        ++_d_end;
        ++current;
      }
    } 












    /*
     * Erases all elements from the container.
     * After this call, size() returns zero.
     */
    void clear() {
      while (_d_end != _d_start) {
        _d_end--;
        _alloc.destroy(_d_end);
      }
    }
  
  }; /* class vector */
} /* namespace ft */

#endif /* CONTAINERS_VECTOR_HPP */
