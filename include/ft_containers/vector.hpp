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
 *                 
 * vector : https://en.cppreference.com/w/cpp/container/vector/vector
 * 
 * extra : https://www.youtube.com/watch?v=LIb3L4vKZ7U
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
      pointer         _d_start; /* start of data */
      pointer         _d_end;   /* end of data */
      size_type       _size;    /* end of memory allocation */

    public:

    /* Default constructor. Constructs an empty container
     * with a default-constructed allocator.
     */
    vector ()
    :
      _alloc(),
      _d_start(NULL),
      _d_end(NULL), /* where the non-empty data ends */
      _size(0) /* number of bytes allocated */
    {}
    
    /* Constructs an empty container with the given allocator alloc.
     */
  	explicit vector (const allocator_type& alloc = allocator_type())
    :
      _alloc(alloc),
      _size(0)
    {
				_d_start = _alloc.allocate(0);
        _d_end = _d_start + 0;
		}
    
    /* Constructs the container with count copies of elements
     * with value value.
     */
    explicit vector(size_type count, const T& value = T(),
                    const Allocator& alloc = Allocator())
    :
      _alloc(alloc),
      _size(count)
    {
      _d_start = _alloc.allocate(count);
      _d_end = _d_start;
      while (count--) {
        _alloc.construct(_d_end, value);
        ++_d_end;
      }
    }

    /* Constructs the container with the contents of the
     * range [first, last).
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
     */
    template< class InputIt >
    vector(InputIt first, InputIt last,
          const Allocator& alloc = Allocator(),
          typename enable_if<is_integral<InputIt>::value, InputIt>::type = InputIt)
    :
      _alloc(alloc),
      _size(std::distance(first, last))
    {
      _d_start = _alloc.allocate(_size);
    }
  
  }; /* class vector */
} /* namespace ft */

#endif /* CONTAINERS_VECTOR_HPP */
