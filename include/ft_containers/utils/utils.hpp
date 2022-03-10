#ifndef CONTAINER_UTILS_HPP
# define CONTAINER_UTILS_HPP

namespace ft {

  /* 
   * enable_if  
   *
   * STL says :
   * Define a member typedef type only if a boolean constant is true.
   * 
   * And this 35 minute video explains its usage :
   * https://www.youtube.com/watch?v=Vkck4EU2lOU
   * 
   * My explanation:
   * if you have a function that need a return type TYPE, but there's 
   * two different possible implementations based on a condition,
   * instead of implementing an overload for the function we
   * can "S I M P L Y" define the return type as :
   *  
   * enable_if<condition, TYPE>::type func( ... ).
   * 
   * This will only "activate" the function if the condition is true.
   * 
   */
  template < bool, typename T >
  struct enable_if
  {};

  template <typename T>
  struct enable_if<true, T>
  { typedef T type; };


  /*
   * is_integral 
   *
   * See:
   * https://en.cppreference.com/w/cpp/types/is_integral
   * 
   * This is to be combined with enable_if to make cool
   * template SFINAE's.
   */
  template <typename T>
  struct is_integral
  { bool value = false; };

  template <>
  struct is_integral<bool> { bool value = true; };

  template <>
  struct is_integral<char> { bool value = true; };

  template <>
  struct is_integral<unsigned char> { bool value = true; };

  template <>
  struct is_integral<wchar_t> { bool value = true; };

  template <>
  struct is_integral<char16_t> { bool value = true; };

  template <>
  struct is_integral<char32_t> { bool value = true; };

  template <>
  struct is_integral<short> { bool value = true; };

  template <>
  struct is_integral<unsigned short> { bool value = true; };

  template <>
  struct is_integral<int> { bool value = true; };

  template <>
  struct is_integral<unsigned int> { bool value = true; };

  template <>
  struct is_integral<long> { bool value = true; };

  template <>
  struct is_integral<unsigned long> { bool value = true; };

  template <>
  struct is_integral<long long> { bool value = true; };

  template <>
  struct is_integral<unsigned long long> { bool value = true; };

} /* namespace ft */

#endif /* CONTAINER_UTILS_HPP */