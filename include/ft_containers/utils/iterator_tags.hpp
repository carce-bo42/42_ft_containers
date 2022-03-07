#ifndef ITERATOR_TAGS_HPP
# define ITERATOR_TAGS_HPP
# pragma once

namespace ft {

  /**
   *  Directly from stl_iterator_base_types.h :
   *  
   *  @defgroup iterator_tags Iterator Tags
   *  These are empty types, used to distinguish different iterators.  The
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

  /* 
   * nullptr_t implementation,
   * from https://stackoverflow.com/questions/13675203/implementation-safe-nullptr
   */
  const class nullptr_t {

    public:

      /* Return 0 for any class pointer */
      template<typename T>
      operator T*() const { return 0; }

      /* Return 0 for any member pointer */
      template<typename T, typename U>
      operator T U::*() const { return 0; }

      /* Safe boolean conversion */
      operator void*() const { return 0; }

    private:

      /* Not allowed to get the address */
      void operator&() const;

  } nullptr_t = {}; /* const class defines the only constructor */

} /* namespace ft */

#endif /*ITERATOR_TRAITS_HPP */