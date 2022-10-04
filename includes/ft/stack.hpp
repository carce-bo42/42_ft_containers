#ifndef CONTAINERS_STACK_HPP
# define CONTAINERS_STACK_HPP
#pragma once

#include "ft/vector.hpp"
#include <map>

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
  typedef typename Container::value_type               value_type;
  typedef typename Container::size_type                size_type;
  typedef typename Container::reference                reference;
  typedef typename Container::const_reference          const_reference;

  private:
  Container   c;
  
  public:

  explicit stack (const Container& cont = Container() )
  :
    c(cont)
  {}

  stack( const stack& other )
  :
    c(other.c)
  {}

  ~stack() {
    //c.~Container(); should be called implicitly.
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

}; // class stack

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return x.c == y.c;
}

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return !(x.c == y.c);
}

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& x,
                const ft::stack<T,Container>& y )
{
  return x.c < x.y;
}

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return !(x.c > y.c);
}    

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& x,
                const ft::stack<T,Container>& y )
{
  return !(x.c < y.c);
}  

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& x,
                 const ft::stack<T,Container>& y )
{
  return !(x.c < y.c);
}

} // namespace ft


#endif /* CONTAINERS_STACK_HPP */