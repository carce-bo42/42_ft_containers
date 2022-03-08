#ifndef ITERATOR_TAGS_HPP
# define ITERATOR_TAGS_HPP
# pragma once

namespace ft {

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