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
    if (u.top() != v.top()) {
      return ft::show_diff(u.top(), v.top());
    }
    u.pop();
    v.pop();
  }
  if (u.size() != v.size()) {
    return ft::show_diff(u.top(), v.top());
  }
  return true;
}

static void constructor_test();
static void assignment_operator_test();
static void frog_on_well();

void stack_test() {
  constructor_test();
  assignment_operator_test();
  frog_on_well();
}

static void constructor_test() {

  ft::stack<int> ft_s;
  std::stack<int> std_s;

  int matrix[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

  for (int i = 0; i < 9; i++) {
    ft_s.push(matrix[i]);
    std_s.push(matrix[i]);
  }

  ft::stack<int> ft_s_copy(ft_s);
  std::stack<int> std_s_copy(std_s);

  if (!Stack_Equality_Check(std_s_copy, ft_s_copy)) {
    return STACK_TEST_ERROR(KO_CONSTRUCTOR);
  }
  return STACK_TEST_OK(CONSTRUCTOR_TAG);
}

static void assignment_operator_test() {
  ft::stack<int> ft_s;
  std::stack<int> std_s;

  int matrix[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

  for (int i = 0; i < 9; i++) {
    ft_s.push(matrix[i]);
    std_s.push(matrix[i]);
  }

  ft::stack<int> ft_s_assign;
  std::stack<int> std_s_assign;

  ft_s_assign = ft_s;
  std_s_assign = std_s;

  if (!Stack_Equality_Check(std_s_assign, ft_s_assign)) {
    return STACK_TEST_ERROR(KO_ASSIGNMENT);
  }
  return STACK_TEST_OK(ASSIGNMENT_TAG);
}

static void frog_on_well() {

#define WELL_HEIGHT 2000

  ft::stack<int> ft_stack;
  std::stack<int> std_stack;

  int size = ft_stack.size();

  while ( size < WELL_HEIGHT ) {
    ft_stack.push(666);
    ft_stack.push(999);
    ft_stack.pop();
    std_stack.push(666);
    std_stack.push(999);
    std_stack.pop();
    if (!Stack_Equality_Check(std_stack, ft_stack)) {
      std::cout << "at size : " << size << std::endl;
      return STACK_TEST_ERROR(KO_FROG);
    }
    size = ft_stack.size();
  }
  if (!Stack_Equality_Check(std_stack, ft_stack)) {
    return STACK_TEST_ERROR(KO_FROG);
  }
  return STACK_TEST_OK(FROG_ON_WELL);
}