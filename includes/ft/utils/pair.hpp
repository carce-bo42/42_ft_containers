#ifndef CONTAINERS_PAIR_HPP
# define CONTAINERS_PAIR_HPP
#pragma once

namespace ft {

template < class T1, class T2 >
struct pair {

  typedef T1  first_type;
  typedef T2  second_type;
  
  T1  first;
  T2  second;

  pair() {}
  
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
pair<T1,T2> make_pair( T1 t, T2 u ) {
  return pair<T1, T2>(t, u);
}

template <typename T1, typename T2>
bool operator==(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return (lhs.first == rhs.first) && (lhs.second == rhs.second); 
}

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return (lhs.first != rhs.first) && (lhs.second != rhs.second); 
}

template <typename T1, typename T2>
bool operator<(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return (lhs.first < rhs.first) && (lhs.second < rhs.second); 
}

template <typename T1, typename T2>
bool operator<=(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return (lhs.first <= rhs.first) && (lhs.second <= rhs.second); 
}

template <typename T1, typename T2>
bool operator>(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return (lhs.first > rhs.first) && (lhs.second > rhs.second); 
}

template <typename T1, typename T2>
bool operator>=(const pair<T1, T2>& lhs,
                const pair<T1, T2>& rhs)
{
  return (lhs.first >= rhs.first) && (lhs.second >= rhs.second); 
}

} /* namespace ft */

#endif /* CONTAINERS_PAIR_HPP */