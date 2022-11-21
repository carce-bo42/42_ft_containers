#include "ft/vector.hpp"
#include "ft/utils/utils.hpp"
#include <vector>
#include "../test_utils.hpp"

static void constructors_test();
static void insert_point_test();
static void insert_range_value_test();
static void insert_range_iterators_test();
static void erase_range_test();
static void erase_pos_test();

void vector_test() {
  constructors_test();
  insert_point_test();
  insert_range_value_test();
  insert_range_iterators_test();
  erase_range_test();
  erase_pos_test();
}

// operator == would not work with ft vector and std one. This does,
// and also allows me to add capacity comparison.
template <typename T>
inline bool Vector_Equality_Check(std::vector<T> v, ft::vector<T> u) {
  if (!ft::equal(u.begin(), u.end(), v.begin())) {
    return ft::equal_diff(u.begin(), u.end(), v.begin());
  }
  if (u.capacity() != v.capacity()) {
    return ft::show_diff(u.capacity(), v.capacity());
  }
  if (u.size() != v.size()) {
    return ft::show_diff(u.size(), v.size());
  }
  return true;
}

static void constructors_test() {
// constructor with range from matrix
{
  int matrix[5] = { 1, 2, 3, 4, 5};

  ft::vector<int> ft_v(matrix, matrix + 5);
  std::vector<int> std_v(matrix, matrix + 5);

  if (!Vector_Equality_Check(std_v, ft_v)) {
    return VECTOR_TEST_ERROR(KO_CONSTRUCTOR);
  }
}
// construct with range from other iterators.
{
  int matrix[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  ft::vector<int> ft_v_1(matrix, matrix + 10);
  std::vector<int> std_v_1(matrix, matrix + 10);

  ft::vector<int> ft_v_2(ft_v_1.begin(), ft_v_1.end());
  std::vector<int> std_v_2(std_v_1.begin(), std_v_1.end());

  if (!Vector_Equality_Check(std_v_2, ft_v_2)) {
    return VECTOR_TEST_ERROR(KO_CONSTRUCTOR);
  }
}
// int fill constructor dispatcher
{
  ft::vector<int> ft_v(1000, 10);
  std::vector<int> std_v(1000, 10);

  if (!Vector_Equality_Check(std_v, ft_v)) {
    return VECTOR_TEST_ERROR(KO_CONSTRUCTOR);
  }
}
  return VECTOR_TEST_OK(CONSTRUCTOR_TAG);
}

/*
 * Inserts the value 1 into all possible positions in
 * all vectors from size 0 to 24.
 */
static void insert_point_test() {
  for (int vector_size = 0; vector_size < 25; vector_size++) {
    for (int insert_point = 0; insert_point < vector_size; insert_point++) {
      
      ft::vector<int> ft_vec(vector_size);
      ft_vec.insert(ft_vec.begin() + insert_point, 1);

      std::vector<int> std_vec(vector_size);
      std_vec.insert(std_vec.begin() + insert_point, 1);

      if (!Vector_Equality_Check(std_vec, ft_vec)) {
        return VECTOR_TEST_ERROR(KO_ERASE);
      }
    }
  }

  // weird test i wanted to do. It works so I wont complain.
  ft::vector<int> ft_vec;
  std::vector<int> std_vec;
  int size = 0;
  for (int insert_point = 0; insert_point < size + 1; insert_point++) {
    
    ft_vec.insert(ft_vec.begin() + insert_point, 1);
    std_vec.insert(std_vec.begin() + insert_point, 1);

    if (!Vector_Equality_Check(std_vec, ft_vec)) {
      return VECTOR_TEST_ERROR(KO_ERASE);
    }
    size = (int)ft_vec.size(); // since vectors are equal, all sizes are the same.
    // this is an infinite loop, this helps it stop.
    if (size > 1000) {
      break;
    }
  }
  return VECTOR_TEST_OK(INSERT_TAG);
}

/* 
 * inserts vectors of size 1 to 3 full of 1's into vectors
 * of size 0 to 25 at any position possible.
 * This test also helps check if insert is protected against
 * 0 length insertions for insert(const iterator, size_type, const T&).
 */
static void insert_range_value_test() {
  for (int vector_size = 0; vector_size < 25; vector_size++) {
    for (int insert_point = 0; insert_point < vector_size + 1; insert_point++) {
      for (int insert_length = 0; insert_length < 3; insert_length++) {
      
        ft::vector<int> ft_vec(vector_size, 0);
        ft_vec.insert(ft_vec.begin() + insert_point, insert_length, 1); 

        std::vector<int> std_vec(vector_size, 0);
        std_vec.insert(std_vec.begin() + insert_point, insert_length, 1);

        if (!Vector_Equality_Check(std_vec, ft_vec)) {
          return VECTOR_TEST_ERROR(KO_ERASE);
        }
      }
    }
  }
  return VECTOR_TEST_OK(INSERT_TAG);
}

/*
 * Inserts vector 0 1 2 3 .. 20 into vectors of
 * size from 0 to 25 at all possible positions.
 */
static void insert_range_iterators_test() {
  std::vector<int> std_vec_input;
  for (int i = 0; i < 20; i++) {
      std_vec_input.push_back(i);
  }
  ft::vector<int> ft_vec_input;
  for (int i = 0; i < 20; i++) {
      ft_vec_input.push_back(i);
  }
  for (int vector_size = 0; vector_size < 25; vector_size++) {
    for (int insert_point = 0; insert_point < vector_size + 1; insert_point++) {
      
      ft::vector<int> ft_vec;
      for (int i = 0; i < vector_size; i++) {
        ft_vec.push_back(i);  
      }
      ft_vec.insert(ft_vec.begin() + insert_point,
                   ft_vec_input.begin(), ft_vec_input.end());

      std::vector<int> std_vec;
      for (int i = 0; i < vector_size; i++) {
        std_vec.push_back(i);
      }
      std_vec.insert(std_vec.begin() + insert_point,
                   std_vec_input.begin(), std_vec_input.end());

      if (!Vector_Equality_Check(std_vec, ft_vec)) {
        return VECTOR_TEST_ERROR(KO_ERASE);
      }
    }
  }

  return VECTOR_TEST_OK(INSERT_TAG);
}

/*
 * Tests erase with an iterator range for vectors
 * with size between 1 and 25, and erase intervals from 1 to size.
 */
static void erase_range_test() {

  for (int vector_size = 1; vector_size < 25; vector_size++) {
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
        return VECTOR_TEST_ERROR(KO_ERASE);
      }
    }
  }
  return VECTOR_TEST_OK(ERASE_TAG);
}

/*
 * Tests erase ona single position 
 * with size between 1 and 25, and erase intervals from 1 to size.
 */
static void erase_pos_test() {
  for (int vector_size = 1; vector_size < 25; vector_size++) {
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
        return VECTOR_TEST_ERROR(KO_ERASE);
      }
    }
  }
  return VECTOR_TEST_OK(ERASE_TAG);
}