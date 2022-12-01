#ifndef FT_CONTAINERS_PAIR_HPP
# define FT_CONTAINERS_PAIR_HPP
#pragma once

namespace ft {

template < class T1, class T2 >
struct pair {

  typedef T1  first_type;
  typedef T2  second_type;
  
  T1  first;
  T2  second;

  pair()
  :
    first(),
    second()
  {}
  
  pair( const T1& x, const T2& y)
  :
    first(x),
    second(y)
  {}

  ~pair() {}

  template < class U1, class U2 >
  pair( const pair<U1, U2>& p)
  :
    first(p.first),
    second(p.second)
  {}

  pair& operator=( const pair& other ) {
    first = other.first;
    second = other.second;
    return *this;
  }

}; /* struct pair */

template< class T1, class T2 >
pair<T1,T2> make_pair( const T1& t, const T2& u ) {
  return pair<T1, T2>(t, u);
}

template <typename T1, typename T2>
bool operator==(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return !(lhs == rhs);
}

/*
 * Note:
 * lhs.first < rhs.first is false if lhs == rhs.first. This is why,
 * one the second condition, !(rhs.first < lhs.first) makes sure
 * we are only comparing second in case lhs is equal to first.
 */
template <typename T1, typename T2>
bool operator<(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return lhs.first < rhs.first
         || (!(rhs.first < lhs.first) && lhs.second < rhs.second); 
}

template <typename T1, typename T2>
bool operator>(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return !(lhs < rhs);
}

template <typename T1, typename T2>
bool operator<=(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return !(lhs > rhs);
}

template <typename T1, typename T2>
bool operator>=(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return !(lhs < rhs);
}

/* 
 * This is garbage on C++98. Creates one more copy than 
 * just typing the code, and makes it less expressive. 
 * (sometimes the types in a pair are not trivial).
 * At least with rvalue references its faster. 
 */
template< class T1, class T2 >
ft::pair<T1, T2> make_pair( T1 t, T2 u ) {
  return ft::pair<T1, T2>(t, u);
}

} /* namespace ft */

#endif /* FT_CONTAINERS_PAIR_HPP */