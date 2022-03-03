#ifndef VECTOR_42_HPP
# define VECTOR_42_HPP
#pragma once

#include <memory> // std::allocator, std::allocator_traits.
#include <cstddef> // std::size_t, std::ptrdiff_t

namespace ft {

  template < class T, class Allocator = std::allocator<T> >
  class vector {

    public:

    using allocator_type          = Allocator;
    using pointer                 = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer           = typename std::allocator_traits<Allocator>::const_pointer;
    using size_type               = std::size_t;
    using difference_type         = std::ptrdiff_t;
    using iterator                = ; // this will be MY own implementation of iterators.
    using const_iterator          = ;
    using reverse_iterator        = ;
    using const_reverse_iterator  = ; 

    // Constructors from before c++11. 
    vector ();
    explicit vector ( const Allocator& alloc );
    explicit vector ( size_type count, const T& value = T(), const Allocator& alloc = Allocator() );
  };
}

#endif /* VECTOR_42_HPP */
