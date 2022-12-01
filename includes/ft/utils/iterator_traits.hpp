#ifndef FT_CONTAINERS_ITERATOR_TRAITS_HPP
# define FT_CONTAINERS_ITERATOR_TRAITS_HPP
#pragma once

#include <cstddef> /* std::ptrdiff_t */

namespace ft {

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

/* ------------------- Iterator typedef structs ----------------- */

template < class T >
struct iterator_traits {

  typedef typename T::difference_type   difference_type;
  typedef typename T::value_type        value_type;
  typedef typename T::pointer           pointer;
  typedef typename T::reference         reference;
  typedef typename T::iterator_category iterator_category;

};

template < class T >
struct iterator_traits<T*> {

  typedef std::ptrdiff_t                 difference_type;
  typedef T                              value_type;
  typedef T*                             pointer;
  typedef T&                             reference;
  typedef ft::random_access_iterator_tag iterator_category;

};

template <class T>
struct iterator_traits< const T* > {

  typedef std::ptrdiff_t                 difference_type;
  typedef T                              value_type;
  typedef const T*                       pointer;
  typedef const T&                       reference;
  typedef ft::random_access_iterator_tag iterator_category;

};

  /* ---------------------------------------------------------------*/
}

#endif /* FT_CONTAINERS_ITERATOR_TRAITS_HPP */