#ifndef UTILS_42_HPP
# define UTILS_42_HPP
# pragma once

#include <cstddef> /* std::ptrdiff_t */
#include <iterator>
#include "ft_containers/utils/iterator_tags.hpp"

/* 
 * INFO : REFS
 * 
 * vector c++98 : https://www.cplusplus.com/reference/vector/vector/
 * 
 * reverse_iterator : https://en.cppreference.com/w/cpp/iterator/reverse_iterator
 *                    https://en.cppreference.com/w/cpp/iterator/reverse_iterator/reverse_iterator
 * 
 */

namespace ft {

  /* ------------------- Iterator typedef structs ----------------- */

  template < class Iter >
    struct iterator_traits {

      using difference_type   = typename Iter::difference_type;
      using value_type        = typename Iter::value_type;
      using pointer           = typename Iter::pointer;
      using reference         = typename Iter::reference;
      using iterator_category = typename Iter::iterator_category;
    };

  template < class T >
    struct iterator_traits< T* > {

      using difference_type   = std::ptrdiff_t;
      using value_type        = T;
      using pointer           = T*;
      using reference         = T&;
      using iterator_category = std::random_access_iterator_tag;
    };

  template < class T >
    struct iterator_traits< const T* > {

      using difference_type     = std::ptrdiff_t;
      using value_type          = T;
      using pointer             = const T*;
      using reference           = const T&;
      using iterator_category   = std::random_access_iterator_tag;
    };

  /* ---------------------------------------------------------------*/


  /* Followed : https://en.cppreference.com/w/cpp/iterator/reverse_iterator */
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
         * From https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator*,
         * Return value : Reference or pointer to the element previous to current.
         */
        reference operator*() const {
          iterator_type tmp = _ptr;
          return *(--tmp) ;
        }

        pointer operator->() const {
          iterator_type tmp = _ptr;
          return --tmp ;
        }

        /*
         * From https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator_at
         * Return value : A reference to the element at relative location, that is, base()[-n-1].
         */
        reference operator[] (difference_type n) {
          return base()[-n-1];
        }

    };
}

#endif /* UTILS_42_HPP */