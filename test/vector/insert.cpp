#include "ft/vector.hpp"
#include <vector>
#include <iostream>
#include "ft/utils/utils.hpp"

typedef enum {
  OK = 0,
  KO_INSERT = 1
} VECTOR_TEST_RESULT;

#define TEST_ERROR(result) \
        Test_Error(result, __LINE__, __FILE__);

inline int Test_Error(int result, int line, const char* file) {
  std::cout << "ERROR at line " << line << " from test "
            << file << std::endl;
  return result;
}

template <typename T>
inline bool After_Insert_Check(std::vector<T> v, ft::vector<T> u) {
  return ft::equal(u.begin(), u.end(), v.begin())
         && u.capacity() == v.capacity();
}


int insert_single_test() {
{
  ft::vector<int> ft_vec(3, 4); // 4 4 4 
  ft_vec.push_back(3);
  ft::vector<int>::iterator it = ft_vec.begin(); // ft_vec = 4 4 4 3
  ++it;
  ft_vec.insert(it, 12);
  // shoudl be now 4 12 4 4 3
  // iterator invalidated !.
  ft_vec.insert(ft_vec.begin(), 21);
  //print_vector<int>(vec_1);
  std::vector<int> std_vec(3, 4); // 4 4 4 
  std_vec.push_back(3);
  std::vector<int>::iterator _it = std_vec.begin(); // std_vec = 4 4 4 3
  ++_it;
  std_vec.insert(_it, 12);
  // shoudl be now 4 12 4 4 3
  // iterator invalidated !.
  std_vec.insert(std_vec.begin(), 21);
  if (!After_Insert_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several at last position by inserting 1 each time
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    ft::vector<int>::iterator it = ft_vec.begin();
    for(; it != ft_vec.end(); it++) {}
    ft_vec.insert(it, 21);
  }
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    std::vector<int>::iterator it = std_vec.begin();
    for(; it != std_vec.end(); it++) {}
    std_vec.insert(it, 21);
  }
  if (!After_Insert_Check(std_vec, ft_vec)) {
    std::cout << "ft_vec capacity :" << ft_vec.capacity()
              << " std_vec capacity :" << std_vec.capacity()
              << std::endl;
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several at last position at once
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  ft::vector<int>::iterator it = ft_vec.begin();
  for(; it != ft_vec.end(); it++) {}
  ft_vec.insert(it, 10, 21);
  //print_vector(ft_vec);  
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  std::vector<int>::iterator it_ = std_vec.begin();
  for(; it_ != std_vec.end(); it_++) {}
  std_vec.insert(it_, 10, 21);
  if (!After_Insert_Check(std_vec, ft_vec)) {
    std::cout << "ft_vec capacity :" << ft_vec.capacity()
              << " std_vec capacity :" << std_vec.capacity()
              << std::endl;
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several before last position by inserting 1 each time
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    ft::vector<int>::iterator it = ft_vec.begin();
    for(; it != ft_vec.end(); it++) {}
    it--;
    ft_vec.insert(it, 21);
  }
  //print_vector(ft_vec);
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  for (int i = 0; i < 10; i++) {
    std::vector<int>::iterator it = std_vec.begin();
    for(; it != std_vec.end(); it++) {}
    it--;
    std_vec.insert(it, 21);
  }
  if (!After_Insert_Check(std_vec, ft_vec)) {
    std::cout << "ft_vec capacity :" << ft_vec.capacity()
              << " std_vec capacity :" << std_vec.capacity()
              << std::endl;
    return TEST_ERROR(KO_INSERT);
  }
}
{ // insert several before last position by inserting 1 each time,
  // this time reserving 200 before inserting, to check for capacity variations.
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  ft_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    ft::vector<int>::iterator it = ft_vec.begin();
    for(; it != ft_vec.end(); it++) {}
    it--;
    ft_vec.insert(it, 21);
  }
  std::vector<int> std_vec(4,5);
  std_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    std::vector<int>::iterator it = std_vec.begin();
    for(; it != std_vec.end(); it++) {}
    it--;
    std_vec.insert(it, 21);
  }
  if (!After_Insert_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
  //print_vector(vec);
}
{ // insert several before last position by inserting 1 each time,
  // this time reserving 200 before inserting, to check for capacity variations.
  ft::vector<int> ft_vec(4, 5); // 5 5 5 5 
  ft_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    ft::vector<int>::iterator it = ft_vec.begin();
    for(; it != ft_vec.end(); it++) {}
    it--;
    ft_vec.insert(it, 21);
  }
  //print_vector(vec);
  std::vector<int> std_vec(4, 5); // 5 5 5 5 
  std_vec.reserve(200);
  for (int i = 0; i < 194; i++) {
    std::vector<int>::iterator it = std_vec.begin();
    for(; it != std_vec.end(); it++) {}
    it--;
    std_vec.insert(it, 21);
  }
  if (!After_Insert_Check(std_vec, ft_vec)) {
    return TEST_ERROR(KO_INSERT);
  }
}
  return OK;
}