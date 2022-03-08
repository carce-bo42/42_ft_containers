#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <cstddef> /* std::ptrdiff_t */

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

  /**
   *  Directly from stl_iterator_base_types.h :
   *  
   *  @defgroup iterator_tags Iterator Tags
   *  These are empty types, used to distinguish different iterators. The
   *  distinction is not made by what they contain, but simply by what they
   *  are.  Different underlying algorithms can then be used based on the
   *  different operations supported by different iterator types.
   * 
   * Useful refs :
   * https://stackoverflow.com/questions/4688177/how-does-iterator-category-in-c-work
   * https://eel.is/c++draft/iterator.requirements
   * 
   * Output iterators definition :
   * https://www.geeksforgeeks.org/output-iterators-cpp/
   * 
   * Input iterators definition :
   * https://www.geeksforgeeks.org/input-iterators-in-cpp/
   * 
   */

  struct input_iterator_tag { };
  struct output_iterator_tag { };
  struct forward_iterator_tag : public input_iterator_tag { };
  struct bidirectional_iterator_tag : public forward_iterator_tag { };
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
}

#endif /* ITERATOR_TRAITS_HPP */