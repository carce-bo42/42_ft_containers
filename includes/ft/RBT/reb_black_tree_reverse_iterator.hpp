#ifndef RBT_REVERSE_ITERATOR
# define RBT_REVERSE_ITERATOR

#include "ft/utils/iterator_traits.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/utils/utils.hpp"
#include "ft/RBT/red_black_tree.hpp"

namespace ft {

//  https://www.geeksforgeeks.org/implementing-forward-iterator-in-bst/ 
// why use nil https://cs.stackexchange.com/questions/44422/what-is-the-purpose-of-using-nil-for-representing-null-nodes
template < typename Iterator >
class rb_tree_reverse_iterator {

  public:

  typedef Iterator                            iterator_type;
  typedef typename iterator_type::value_type  value_type;
  typedef typename iterator_type::reference   reference;
  typedef typename iterator_type::pointer     pointer;
  typedef typename iterator_type::node_ptr    node_ptr;
  typedef typename iterator_type::size_type   size_type;

  private:

  iterator_type iter;

  public:

  rb_tree_reverse_iterator() {}

  explicit rb_tree_reverse_iterator(iterator_type x)
  :
    iter(x)
  {}

  template < typename U >
  rb_tree_reverse_iterator(const rb_tree_reverse_iterator<U>& x,
                  typename ft::enable_if<
                             ft::is_same_type<
                      typename rb_tree_reverse_iterator<U>::value_type,
                               value_type>::value,
                             value_type>::type* = 0)
  :
    iter(x)
  {}

  virtual ~rb_tree_reverse_iterator() {}

  node_ptr base() const {
    return iter.base();
  }

  rb_tree_reverse_iterator& operator=(const rb_tree_reverse_iterator& other) {
    if (this != &other) {
      iter = other.iter;
    }
    return *this;
  }

  /*
   * THIS IS A TRICK !!! I do not want to implement a super structure
   * over the red black tree to manage dumb fucking dereferences on
   * reverse iterators as they are on vectors. This will work the same
   * and save a thousand headaches. Reverse iterators on the red black tree
   * will just be normal iterators that call ++ when -- and viceversa.
   * Since the tree has an end at the left side of the minium and the
   * right side of the maximum, rend() can be initialized the same as
   * end(), as long as rbegin starts at the maximumm and begin at the
   * minimum. Se rb_tree implementation.
   */
  reference operator*() const {
    return iter.operator*();
  }

  pointer operator->() const {
    return iter.operator->();
  }

  rb_tree_reverse_iterator& operator++() {
    --iter;
    return *this;
  }

  // it++
  rb_tree_reverse_iterator operator++(int) {
    rb_tree_reverse_iterator tmp = *this;
    --iter;
    return tmp;
  }

  rb_tree_reverse_iterator& operator--() {
    ++iter;
    return *this;
  }

  rb_tree_reverse_iterator operator--(int) {
    rb_tree_reverse_iterator tmp = *this;
    ++iter;
    return tmp;
  }

  rb_tree_reverse_iterator operator+(size_type n) const {
    return rb_tree_reverse_iterator(iter - n);
  }

  rb_tree_reverse_iterator operator-(size_type n) const {
    return rb_tree_reverse_iterator(iter + n);
  }

};

template <typename X, typename Y>
bool	operator==(const rb_tree_reverse_iterator<X>& x,
                  const rb_tree_reverse_iterator<Y>& y)
{
  return x.base() == y.base();
}

template <typename X, typename Y>
bool	operator!=(const rb_tree_reverse_iterator<X>& x,
                  const rb_tree_reverse_iterator<Y>& y)
{
  return x.base() != y.base();
}

template <typename X, typename Y>
bool		operator>(const rb_tree_reverse_iterator<X>& x,
                  const rb_tree_reverse_iterator<Y>& y)
{
  return x.base() > y.base();
}

template <typename X, typename Y>
bool operator<(const rb_tree_reverse_iterator<X>& x,
                const rb_tree_reverse_iterator<Y>& y)
{
  return x.base() < y.base();
}

template <typename X, typename Y>
bool operator>=(const rb_tree_reverse_iterator<X>& x,
                const rb_tree_reverse_iterator<Y>& y)
{
  return !(x.base() < y.base());
}

template <typename X, typename Y>
bool operator<=(const rb_tree_reverse_iterator<X>& x,
                const rb_tree_reverse_iterator<Y>& y)
{
  return !(x.base() > y.base());
}

} // namespace ft


#endif /* # define RBT_REVERSE_ITERATOR */