#ifndef CONTAINERS_VECTOR_HPP
# define CONTAINERS_VECTOR_HPP
#pragma once

#include <memory> /* std::allocator, std::allocator_traits. */
#include <cstddef> /* std::size_t, std::ptrdiff_t */
#include <vector>
#include <limits>

#include "ft_containers/utils/utils.hpp"

/*
 * INFO : REFS
 * explicit keyword :
 * https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
 * 
 * allocator : https://www.youtube.com/watch?v=HcESuwmlHEY
 *             https://www.youtube.com/watch?v=v-qePUHf8iU
 *             https://en.cppreference.com/w/cpp/memory/allocator
 *             https://stackoverflow.com/questions/59539057/c-does-it-lead-to-double-free-when-destroy-element-in-allocatorstring
 *             https://stackoverflow.com/questions/53610332/allocating-zero-objects-with-stdallocatorallocate0-in-c
 *                 
 * vector : https://en.cppreference.com/w/cpp/container/vector/vector
 * 
 * extra : https://www.youtube.com/watch?v=LIb3L4vKZ7U
 * 
 * On why size_type and difference_type are always the same (I use this a lot) :
 * https://www.codeguru.com/cplusplus/about-size_t-and-ptrdiff_t/#:~:text=The%20size%20of%20size_t%20and,of%20pointers%20and%20pointer%20arithmetic.
 * 
 */

namespace ft {

  template < class T, typename Allocator = std::allocator<T> >
  class vector {

    public:
    using allocator_type         = Allocator;
    using value_type             = typename allocator_type::value_type;
    using pointer                = typename allocator_type::pointer;
    using const_pointer          = typename allocator_type::const_pointer;
    using reference              = typename allocator_type::reference;
    using const_reference        = typename allocator_type::const_reference;
    using size_type              = typename allocator_type::size_type;
    using difference_type        = typename allocator_type::difference_type;
    using iterator               = ft::random_access_iterator<pointer>;
    using const_iterator         = ft::random_access_iterator<const_pointer>;
    using reverse_iterator       = ft::reverse_iterator<iterator>;
    using const_reverse_iterator = ft::reverse_iterator<const_iterator>;

    private:

      allocator_type  _alloc;   /* shortcut */
      pointer         _d_start; /* where the non-empty data begins */
      pointer         _d_end;   /* where the empty data begins */
      size_type       _capacity;    /* allocated objects */

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
    
  	explicit vector (const allocator_type& alloc = allocator_type())
    :
      _alloc(alloc),
      _capacity(0)
    {
      _d_start = _alloc.allocate(0);
      _d_end = _d_start;
    }
    
    /* Constructs the container with count copies of elements
     * with value value.
     */
    explicit vector(size_type count, const T& value = T(),
                    const Allocator& alloc = Allocator())
    :
      _alloc(alloc),
      _capacity(count)
    {
      _d_start = _alloc.allocate(count);
      _d_end = _d_start;
      while (count--) {
        _alloc.construct(_d_end, value);
        ++_d_end;
      }
    }

    /* Constructs the container with the contents of the
     * range [ first, last ).
     *
     * Explanation for the last argument :
     * This function is only to be used in case the type is integral.
     * enable_if<cond, T> accepts a boolean that, in case it is true,
     * gives a value of T to its inner variable type.
     * It is essentially saying that "If this InputIt is an integral
     * type, enable_if should have an inside type of InputIt". So
     * forcing here that enable_if< ... >::type = InputIt is like 
     * saying "I only want this to be looked into in case the enable_if
     * type is InputIt", which only happens if indeed the InputIt is
     * an integral type.
     * See:
     * https://en.cppreference.com/w/cpp/memory/allocator/allocate
     * https://en.cppreference.com/w/cpp/memory/allocator/construct
     */
    template< class InputIt >
    vector(InputIt first, InputIt last,
          const Allocator& alloc = Allocator(),
          typename enable_if<is_integral<InputIt>::value,
                            InputIt>::type = InputIt)
    :
      _alloc(alloc),
      _capacity(std::distance(first, last))
    {
      _d_start = _alloc.allocate(_capacity);
      _d_end = _d_start;
      while (first != last) {
        _alloc.construct(_d_end, *first);
        ++_d_end;
        ++first;
      }
    }

    vector( const vector& other )
    :
      _alloc(other.alloc)
    {
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

    /*
     * Destructs the vector.
     * The destructors of the elements are called and the used
     * storage is deallocated. Note, that if the elements are
     * pointers, the pointed-to objects are not destroyed.
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
        /* Change allocators !!!!! (important) */
        _alloc = other._alloc;
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








    /* Checks if the container has no elements. */
    bool empty() const {
      return _d_start == _d_end;
    }

    /*
     * Returns the number of elements in the container,
     * i.e. std::distance(begin(), end()).
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
     */
    void reserve( size_type new_cap ) {
      ;
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
