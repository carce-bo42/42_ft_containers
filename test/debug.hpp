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
 * when using ft::vector<T> as the argument.
 */

/* This are my solutions, the three of them work, but apparently,
 * 1 and 2 are equivalent and the compiler complains. (3) would 
 * compile with 1 or 2 set, but it is chosen before them but
 * is not fun because it is too specific.
 */

/* (1)
template < typename U, template <typename, typename> class T >
void print_vector(T<U, std::allocator<U> >& vec) {
  size_t i = 0;
  for (typename T<U, std::allocator<U> >::iterator it = vec.begin();
      it != vec.end(); it++)
  {
    std::cout << "vector[" << i++ << "] = " << *it << std::endl;
  }
}*/

// (2)
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

// (3)
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