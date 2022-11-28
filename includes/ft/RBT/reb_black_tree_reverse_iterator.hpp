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

  typedef Iterator                                iterator_type;
  typedef typename iterator_type::value_type      value_type;
  typedef typename iterator_type::difference_type difference_type;
  typedef typename iterator_type::reference       reference;
  typedef typename iterator_type::pointer         pointer;
  typedef typename iterator_type::node_ptr        node_ptr;
  typedef typename iterator_type::size_type       size_type;

  iterator_type iter;

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
    iter(x.iter)
  {}

  virtual ~rb_tree_reverse_iterator() {}

  iterator_type base() const {
    return iter;
  }

  node_ptr get_node_end() const {
    return iter.get_node_end();
  }

  rb_tree_reverse_iterator& operator=(const rb_tree_reverse_iterator& other) {
    if (this != &other) {
      iter = other.iter;
    }
    return *this;
  }

  reference operator*() const {
    iterator_type _tmp = iter;
    return (--_tmp).operator*();
  }

  pointer operator->() const {
    iterator_type _tmp = iter;
    return (--_tmp).operator->();
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