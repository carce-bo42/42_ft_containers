#include "ft/map.hpp"
#include <map>
#include <iostream>
#include "../test_utils.hpp"
#include "../test.hpp"
#include <cmath>

template <typename T, typename U>
inline bool Map_Equality_Check(std::map<T, U> v, ft::map<T, U> u) {
  if (!ft::equal_map(u.begin(), u.end(), v.begin())) {
    return false;
  }
  if (u.size() != v.size()) {
    return ft::show_diff(u.size(), v.size());
  }
  return true;
}

static void insert_delete_sponge_test();
static void constructors_test();
static void reverse_iteration();


void map_test() {

  insert_delete_sponge_test();
  constructors_test();
  reverse_iteration();
}


/* 
 * All map constructors that are not the empty one use insert.
 * Because of this, insert is tested first.
 */


static void constructors_test() {
// empty
{
  ft::map<int, std::string> ft_m;
  std::map<int, std::string> std_m;

  if (!Map_Equality_Check(std_m, ft_m)) {
    return MAP_TEST_ERROR(KO_CONSTRUCTOR);
  }
}
// range & copy
{
  ft::map<int, std::string> ft_m;
  std::map<int, std::string> std_m;

  int matrix[4] = {3, 4, 5, 6};

  for (int i = 0; i < 5; i++) {
    ft_m.insert(ft::pair<int, std::string>(matrix[i], "hello"));
    std_m.insert(std::pair<int, std::string>(matrix[i], "hello"));
  }

  ft::map<int, std::string> ft_map(ft_m.begin(), ft_m.end());
  std::map<int, std::string> std_map(std_m.begin(), std_m.end());

  if (!Map_Equality_Check(std_map, ft_map)) {
    return MAP_TEST_ERROR(KO_CONSTRUCTOR);
  }

  ft::map<int, std::string> ft_copy_map(ft_map);
  std::map<int, std::string> std_copy_map(std_map);

  if (!Map_Equality_Check(std_copy_map, ft_copy_map)) {
    return MAP_TEST_ERROR(KO_CONSTRUCTOR);
  }
}
  return MAP_TEST_OK(CONSTRUCTOR_TAG);
}


static void reverse_iteration() {
{
  ft::map<int, std::string> ft_map;

  int matrix[11] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};

  for (int i = 0; i < 11; i++) {
    ft_map.insert(ft::pair<int, std::string>(matrix[i], "hello"));
  }

  ft::map<int, std::string>::iterator it_ = ft_map.begin();
  ft::map<int, std::string>::iterator it_end = ft_map.end();
  ft::map<int, std::string>::reverse_iterator ti_ = ft_map.rbegin();
  ft::map<int, std::string>::reverse_iterator ti_end = ft_map.rend();

  for (; ti_ != ti_end && it_ != it_end; ++it_, ++ti_) {
    if (*ti_ != *it_) {
      return VECTOR_TEST_ERROR(KO_ITERATORS);
    }
  }
  if (ti_ != ti_end
      || it_ != it_end)
  {
    return VECTOR_TEST_ERROR(KO_ITERATORS);
  }
}
// same thing now from end to begin.
{
  ft::map<int, std::string> ft_map;

  int matrix[11] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};

  for (int i = 0; i < 11; i++) {
    ft_map.insert(ft::pair<int, std::string>(matrix[i], "hello"));
  }

  ft::map<int, std::string>::iterator it_begin = ft_map.begin();
  ft::map<int, std::string>::iterator it_end = ft_map.end();
  ft::map<int, std::string>::reverse_iterator ti_begin = ft_map.rbegin();
  ft::map<int, std::string>::reverse_iterator ti_end = ft_map.rend();

  --it_end;
  --ti_end;
  for (; ti_end != ti_begin && it_end != it_end; --it_end, --ti_end) {
    if (it_end->first != ti_end->first) {
      return VECTOR_TEST_ERROR(KO_ITERATORS);
    }
  }
  if (it_end != it_begin
      || ti_end != ti_end)
  {
    return VECTOR_TEST_ERROR(KO_ITERATORS);
  }
}

  return MAP_TEST_OK(MAP_TAG);
}


// inserts TREE_SPONGE_MAX_SIZE, then deletes it entirely. Does this
// <iterations> times. 
static void insert_delete_sponge_test() {

#define TREE_SPONGE_MAX_SIZE 8192

  int iterations = 100;
  int save_insertions[TREE_SPONGE_MAX_SIZE] = {0};

  ft::map<int, std::string> tree;
  std::map<int, std::string> map;

  srand(time(NULL));

  int insertions = 0;
  bool invert_deletion = false; // alternates between deleting from 0 -> TREE_SPONGE_MAX_SIZE
                                // and TREE_SPONGE_MAX_SIZE -> 0.
  for (int i = 0; i < iterations * TREE_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == TREE_SPONGE_MAX_SIZE) {
      if (!invert_deletion) {
        for (int k = insertions - 1; k >= 0; k--) {
          tree.erase(save_insertions[k]);
          map.erase(save_insertions[k]);
        }
        invert_deletion = true;
      } else {
        for (int k = 0; k < insertions; k++) {
          tree.erase(save_insertions[k]);
          map.erase(save_insertions[k]);
        }
        invert_deletion = false;
      }
      insertions = 0;
    }
    int random_number = rand();
    tree.insert(ft::pair<int, std::string>(random_number, "hello"));
    map.insert(std::pair<int, std::string>(random_number, "hello"));
    save_insertions[insertions++] = random_number;
  }
}