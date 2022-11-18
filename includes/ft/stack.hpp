#ifndef CONTAINERS_STACK_HPP
# define CONTAINERS_STACK_HPP
#pragma once

#include "ft/vector.hpp"

/*
 * This class is simple, this reference was enough to implement it :
 * https://en.cppreference.com/w/cpp/container/stack
 * It is a vector wrapper, with very limited methods that consist
 * on calling the underlying container methods.
 * List, vector and dequeue are suitable to be the underlying container.
 */

namespace ft {

template < class T, class Container = ft::vector<T> >
class stack {

  public:
  typedef Container                                    container_type;
  typedef typename container_type::value_type               value_type;
  typedef typename container_type::size_type                size_type;
  typedef typename container_type::reference                reference;
  typedef typename container_type::const_reference          const_reference;

  protected:

  container_type   c;
  
  public:

  explicit stack (const container_type& cont = container_type() )
  :
    c(cont)
  {}

  stack( const stack& other )
  :
    c(other.c)
  {}

  ~stack() {
    //c.~container_type(); should be called implicitly.
  }

  stack& operator=( const stack& other ) {
    if (this != &other) {
      c = other.c;
    }
    return (*this);
  }

  reference top() {
    return c.back();
  }

  const_reference top() const {
    return c.back();
  }

  bool empty() const {
    return c.empty();
  }

  size_type size() const {
    return c.size();
  }

  void push( const value_type& value ) {
    c.push_back(value);
  }

  void pop() {
    c.pop_back();
  }

  /* These two outter functions MUST have acces to the inner container.
   * The rest of the comparison operators can be written
   * in terms of these two.
   */
  template<class A, class B>
  friend bool	operator==(const ft::stack<A, B> &lhs,
                         const ft::stack<A, B> &rhs);

  template<class A, class B>
  friend bool	operator<(const ft::stack<A, B> &lhs,
                        const ft::stack<A, B> &rhs);

}; // class stack

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return x.c == y.c;
}

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& x,
                const ft::stack<T,Container>& y )
{
  return x.c < y.c;
}

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return !(x == y);
}

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return !(x > y);
}    

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& x,
                const ft::stack<T,Container>& y )
{
  return !(x < y || x == y);
}  

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return !(x < y);
}

} // namespace ft


#endif /* CONTAINERS_STACK_HPP */