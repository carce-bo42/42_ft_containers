#include "ft/vector.hpp"
#include <vector>
#include <iostream>
#include "ft/utils/utils.hpp"
#include "../debug.hpp"

typedef enum {
  OK = 0,
  KO_INSERT = 1,
  KO_ERASE = 2
} VECTOR_TEST_RESULT;

template <typename T>
inline bool Vector_Equality_Check(std::vector<T> v, ft::vector<T> u) {
  return ft::equal(u.begin(), u.end(), v.begin())
         && u.capacity() == v.capacity();
}

int insert_single_test() {
{
  ft::vector<int> ft_vec(3, 4); // 4 4 4 
  ft_vec.push_back(3);
  ft_vec.insert(ft_vec.begin() + 1, 12);
  // shoudl be now 4 12 4 4 3
  // iterator invalidated !.
  ft_vec.insert(ft_vec.begin(), 21);
  //print_vector<int>(vec_1);
  std::vector<int> std_vec(3, 4); // 4 4 4 
  std_vec.push_back(3);
  std_vec.insert(std_vec.begin() + 1, 12);
  // shoudl be now 4 12 4 4 3
  // iterator invalidated !.
  std_vec.insert(std_vec.begin(), 21);
  if (!Vector_Equality_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several at last position by inserting 1 each time
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    ft::vector<int>::iterator it = ft_vec.begin();
    ft_vec.insert(it + ft_vec.size(), 21);
  }
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    std::vector<int>::iterator it = std_vec.begin();
    std_vec.insert(it + std_vec.size(), 21);
  }
  if (!Vector_Equality_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several at last position at once
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  ft_vec.insert(ft_vec.begin() + ft_vec.size(), 10, 21);
  //print_vector(ft_vec);  
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  std_vec.insert(std_vec.begin() + std_vec.size(), 10, 21);
  if (!Vector_Equality_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several before last position by inserting 1 each time
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    ft_vec.insert(ft_vec.begin() + ft_vec.size() - 1, 21);
  }
  //print_vector(ft_vec);
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    std_vec.insert(std_vec.begin() + std_vec.size() - 1, 21);
  }
  if (!Vector_Equality_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several before last position by inserting 1 each time,
  // this time reserving 200 before inserting, to check for capacity variations.
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  ft_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    ft_vec.insert(ft_vec.begin() + ft_vec.size() - 1, 21);
  }
  std::vector<int> std_vec(4,5);
  std_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    std_vec.insert(std_vec.begin() + std_vec.size() - 1, 21);
  }
  if (!Vector_Equality_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
  //print_vector(vec);
}
{ // insert several before last position by inserting 1 each time,
  // this time reserving 200 before inserting, to check for capacity variations.
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  ft_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    ft_vec.insert(ft_vec.begin() + ft_vec.size() - 1, 21);
  }
  //print_vector(vec);
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  std_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    std_vec.insert(std_vec.begin() + std_vec.size() - 1, 21);
  }
  if (!Vector_Equality_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert with iterators.
  ft::vector<int> ft_vec(10, 3); // 3 3 3 3 3 3 3 3 3 3
  ft::vector<int> ft_vec_input;

  ft_vec_input.push_back(9);
  ft_vec_input.push_back(8);
  ft_vec_input.push_back(7);

  ft_vec.insert(ft_vec.end() - 1, ft_vec_input.begin(), ft_vec_input.end());

  std::vector<int> std_vec(10, 3); // 3 3 3 3 3 3 3 3 3 3
  std::vector<int> std_vec_input;

  std_vec_input.push_back(9);
  std_vec_input.push_back(8);
  std_vec_input.push_back(7);

  std_vec.insert(std_vec.end() - 1, std_vec_input.begin(), std_vec_input.end());

  //print_vector(ft_vec);
  if (!Vector_Equality_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
  return OK;
}

/*
 * Tests erase with an iterator range for vectors
 * with size between 1 and 100, and erase intervals from 1 to size.
 */
int erase_range_single_test() {

  for (int vector_size = 1; vector_size < 100; vector_size++) {
    for (int erase_end = 0; erase_end < vector_size; erase_end++) {
      ft::vector<int> ft_vec;
      for (int i = 0; i < vector_size; i++) {
        ft_vec.push_back(i);
      }
      ft_vec.erase(ft_vec.begin(), ft_vec.end() - erase_end);

      std::vector<int> std_vec;

      for (int i = 0; i < vector_size; i++) {
        std_vec.push_back(i);
      }
      std_vec.erase(std_vec.begin(), std_vec.end() - erase_end);

      if (!Vector_Equality_Check(std_vec, ft_vec)) {
        return TEST_ERROR(KO_ERASE);
      }
    }
  }
  return OK;
}

int erase_pos_single_test() {
  for (int vector_size = 1; vector_size < 100; vector_size++) {
    for (int erase_pos = 0; erase_pos < vector_size; erase_pos++) {
      ft::vector<int> ft_vec;
      for (int i = 0; i < vector_size; i++) {
        ft_vec.push_back(i);
      }
      ft_vec.erase(ft_vec.begin() + erase_pos);

      std::vector<int> std_vec;

      for (int i = 0; i < vector_size; i++) {
        std_vec.push_back(i);
      }
      std_vec.erase(std_vec.begin() + erase_pos);

      if (!Vector_Equality_Check(std_vec, ft_vec)) {
        return TEST_ERROR(KO_ERASE);
      }
    }
  }
  return OK;
}