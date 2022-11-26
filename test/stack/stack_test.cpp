#include "ft/stack.hpp"
#include "ft/utils/utils.hpp"
#include <stack>
#include "../test_utils.hpp"

// operator == would not work with ft vector and std one. This does,
// and also allows me to add capacity comparison.
template <typename T>
inline bool Stack_Equality_Check(std::stack<T> u, ft::stack<T> v) {

  if (u.size() != v.size()) {
    return ft::show_diff(u.size(), v.size());
  }
  if (u.top() != v.top()) {
    return ft::show_diff(u.top(), v.top());
  }
  // this is like iterating a vector. both stacks are a copy of original
  // so it is not changed outside this function.
  while (u.size() != 0) {
    u.pop();
    v.pop();
    if (u.top() != b.top()) {
      return ft::show_diff(u.top(), v.top());
    }
  }
  if (u.size() != v.size()) {
    return ft::show_diff(u.top(), v.top());
  }
  return true;
}