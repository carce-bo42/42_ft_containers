#ifndef CONTAINERS_DEBUG_HPP
# define CONTAINERS_DEBUG_HPP

#include "ft/vector.hpp"
#include <iostream>
#include <memory>


/*
 * Since ft::vector<T> is in reality 
 * ft::vector<T, typename U = std::alocator<T> >,
 * the compiler thinks it is a specialization for some
 * other template. This is why the following function is
 * not allowed :
 * 
 * template < typename U, template <typename> class T >
 * void print_vector(T<U>& container) {}
 * 
 * The compiler writes :
 * "error : default template arguments may not be
 * used in function templates without ‘-std=c++11’ or ‘-std=gnu++11’"
 */

// This are my solutions, kept because they look funny
// First one is commented because it apparently is the 
// same as the second one
/*
template < typename U, template <typename, typename> class T >
void print_vector(T<U, std::allocator<U> >& vec) {
  size_t i = 0;
  for (typename T<U, std::allocator<U> >::iterator it = vec.begin();
      it != vec.end(); it++)
  {
    std::cout << "vector[" << i++ << "] = " << *it << std::endl;
  }
}*/

// I leave this one because it feels the weirdest and works
// with print_vector<int>() and print_vector().
template < typename U,
           template < typename V = U,
                      typename Allocator = std::allocator<U> >
                      class T >
void print_vector(T<>& vec) {
  size_t i = 0;
  std::cout << "1" << std::endl;
  for (typename T<>::iterator it = vec.begin();
      it != vec.end(); it++)
  {
    std::cout << "vector[" << i++ << "] = " << *it << std::endl;
  }
}

/*
 * This is the one to use if you want to keep sanity from leaving
 */
/*template < typename T >
void print_vector(ft::vector<T> vec) {
  size_t i = 0;
  std::cout << "2" << std::endl;
  for (typename ft::vector<T>::iterator it = vec.begin();
      it != vec.end(); it++)
  { 
    std::cout << "vector[" << i++ << "] = " << *it << std::endl;
  }
}*/

#endif