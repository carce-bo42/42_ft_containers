#ifndef VECTOR_42_HPP
# define VECTOR_42_HPP
#pragma once

#include <memory> /* std::allocator, std::allocator_traits. */
#include <cstddef> /* std::size_t, std::ptrdiff_t */

/*
 * INFO : REFS
 * explicit keyword : https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
 * 
 * 
 */

namespace ft {

  template < class T, class Allocator = std::allocator<T> >
  class vector {

    public:

      using allocator_type          = Allocator;
      using pointer                 = allocator_type::pointer;
      using const_pointer           = allocator_type::const_pointer;
      using size_type               = std::size_t;
      using difference_type         = std::ptrdiff_t;
      using iterator                = ; // this will be MY own implementation of iterators.
      using const_iterator          = ;
      using reverse_iterator        = ;
      using const_reverse_iterator  = ;

    /* Constructors before C++11 */
    vector ();
    explicit vector ( const Allocator& alloc );
    explicit vector ( size_type count, const T& value = T(), const Allocator& alloc = Allocator() );
  
  }; /* class vector */
} /* namespace ft */

#endif /* VECTOR_42_HPP */
