#include "ft/vector.hpp"
#include <iostream>
#include "ft/utils/utils.hpp"
#include <vector>
#include "../debug.hpp"

typedef enum {
  OK = 0,
  KO_INSERT = 1,
  KO_ERASE = 2
} VECTOR_TEST_RESULT;

#define TEST_TYPE int

template <typename T>
inline bool Vector_Equality_Check(std::vector<T> v, ft::vector<T> u) {
  return ft::equal(u.begin(), u.end(), v.begin())
         && u.capacity() == v.capacity()
         && u.size() == v.size();
}

/*
 * Inserts the value 1 into all possible positions in
 * all vectors from size 0 to 24.
 */
int insert_point_single_test() {
  for (int vector_size = 0; vector_size < 25; vector_size++) {
    for (int insert_point = 0; insert_point < vector_size; insert_point++) {
      
      ft::vector<TEST_TYPE> ft_vec(vector_size);
      ft_vec.insert(ft_vec.begin() + insert_point, 1);

      std::vector<TEST_TYPE> std_vec(vector_size);
      std_vec.insert(std_vec.begin() + insert_point, 1);

      if (!Vector_Equality_Check(std_vec, ft_vec)) {
        return TEST_ERROR(KO_ERASE);
      }
    }
  }

  // weird test i wanted to do. It works so I wont complain.
  ft::vector<TEST_TYPE> ft_vec;
  std::vector<TEST_TYPE> std_vec;
  int size = 0;
  for (int insert_point = 0; insert_point < size + 1; insert_point++) {
    
    ft_vec.insert(ft_vec.begin() + insert_point, 1);
    std_vec.insert(std_vec.begin() + insert_point, 1);

    if (!Vector_Equality_Check(std_vec, ft_vec)) {
      return TEST_ERROR(KO_ERASE);
    }
    size = (int)ft_vec.size(); // since vectors are equal, all sizes are the same.
    // this is an infinite loop, this helps it stop.
    if (size > 1000) {
      break;
    }
  }
  return OK;
}

/* 
 * inserts vectors of size 1 to 3 full of 1's into vectors
 * of size 0 to 25 at any position possible.
 * This test also helps check if insert is protected against
 * 0 length insertions for insert(const iterator, size_type, const T&).
 */
int insert_range_value_single_test() {
  for (int vector_size = 0; vector_size < 25; vector_size++) {
    for (int insert_point = 0; insert_point < vector_size + 1; insert_point++) {
      for (size_t insert_length = 0; insert_length < 3; insert_length++) {
      
        ft::vector<TEST_TYPE> ft_vec(vector_size, 0);
        ft_vec.insert(ft_vec.begin() + insert_point, insert_length, 1); 

        std::vector<TEST_TYPE> std_vec(vector_size, 0);
        std_vec.insert(std_vec.begin() + insert_point, insert_length, 1);

        if (!Vector_Equality_Check(std_vec, ft_vec)) {
          return TEST_ERROR(KO_ERASE);
        }
      }
    }
  }
  return OK;
}

/*
 * Inserts vector 0 1 2 3 .. 20 into vectors of
 * size from 0 to 25 at all possible positions.
 */
int insert_range_iterators_single_test() {
  std::vector<TEST_TYPE> std_vec_input;
  for (int i = 0; i < 20; i++) {
      std_vec_input.push_back(i);
  }
  ft::vector<TEST_TYPE> ft_vec_input;
  for (int i = 0; i < 20; i++) {
      ft_vec_input.push_back(i);
  }
  for (int vector_size = 0; vector_size < 25; vector_size++) {
    for (int insert_point = 0; insert_point < vector_size + 1; insert_point++) {
      
      ft::vector<TEST_TYPE> ft_vec;
      for (int i = 0; i < vector_size; i++) {
        ft_vec.push_back(i);  
      }
      ft_vec.insert(ft_vec.begin() + insert_point,
                   ft_vec_input.begin(), ft_vec_input.end());

      std::vector<TEST_TYPE> std_vec;
      for (int i = 0; i < vector_size; i++) {
        std_vec.push_back(i);
      }
      std_vec.insert(std_vec.begin() + insert_point,
                   std_vec_input.begin(), std_vec_input.end());

      if (!Vector_Equality_Check(std_vec, ft_vec)) {
        return TEST_ERROR(KO_ERASE);
      }
    }
  }

  return OK;
}

/*
 * Tests erase with an iterator range for vectors
 * with size between 1 and 25, and erase intervals from 1 to size.
 */
int erase_range_single_test() {

  for (int vector_size = 1; vector_size < 25; vector_size++) {
    for (int erase_end = 0; erase_end < vector_size; erase_end++) {
      
      ft::vector<TEST_TYPE> ft_vec;
      for (int i = 0; i < vector_size; i++) {
        ft_vec.push_back(i);
      }
      ft_vec.erase(ft_vec.begin(), ft_vec.end() - erase_end);

      std::vector<TEST_TYPE> std_vec;
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

/*
 * Tests erase ona single position 
 * with size between 1 and 25, and erase intervals from 1 to size.
 */
int erase_pos_single_test() {
  for (int vector_size = 1; vector_size < 25; vector_size++) {
    for (int erase_pos = 0; erase_pos < vector_size; erase_pos++) {
      
      ft::vector<TEST_TYPE> ft_vec;
      for (int i = 0; i < vector_size; i++) {
        ft_vec.push_back(i);
      }
      ft_vec.erase(ft_vec.begin() + erase_pos);

      std::vector<TEST_TYPE> std_vec;
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