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

/* 
 * All map constructors that are not the empty one use insert.
 * Because of this, insert is tested first.
 */

static void insert_no_fix();
static void delete_no_fix();
static void insert_random();
static void erase_random();
static void sponge_test();
static void frog_on_well();
static void constructors_test();
static void assignment_operator_test();
static void reverse_iteration();

void map_test() {
  insert_no_fix();
  delete_no_fix();
  insert_random();
  erase_random();
  sponge_test();
  frog_on_well();
  constructors_test();
  reverse_iteration();
  assignment_operator_test();
}

/*
 *                      4                      -> Black
 *                  /      \
 *               /            \
 *            /                  \
 *           0                   13            -> Red
 *       /       \           /       \
 *      -9        2         11       60        -> Black
 *    /   \     /   \     /   \     /   \
 *  -12   -4   1    3    5    12  40    80     -> Red
 */
static void insert_no_fix() {

  ft::map<int, std::string> ft_map;
  std::map<int , std::string> std_map;

  int matrix[15] = {4, 13, 0, -9, 2, -12, -4, 1, 3, 11, 60, 5, 12, 40, 80};

  for (int i = 0; i < 15; i++) {
    ft_map.insert(ft::pair<int, std::string>(matrix[i], "a"));
    std_map.insert(std::pair<int, std::string>(matrix[i], "a"));
  }

  if (!Map_Equality_Check(std_map, ft_map)) {
    return MAP_TEST_ERROR(KO_INSERT);
  }
  return MAP_TEST_OK(INSERT_TAG);
}

// Same tree as before, now deleting just the base
// The others need fixing XD
static void delete_no_fix() {
  ft::map<int, std::string> ft_map;
  std::map<int , std::string> std_map;

  int matrix[15] = {4, 13, 0, -9, 2, -12, -4, 1, 3, 11, 60, 5, 12, 40, 80};

  for (int i = 0; i < 15; i++) {
    ft_map.insert(ft::pair<int, std::string>(matrix[i], "a"));
    std_map.insert(std::pair<int, std::string>(matrix[i], "a"));
  }

  // 5, 12, 40, 80
  for (int i = 14; i >= 11; i--) {
    ft_map.erase(matrix[i]);
    std_map.erase(matrix[i]);
  }

  // -12, -4, 1, 3
  for (int i = 8; i >= 5; i--) {
    ft_map.erase(matrix[i]);
    std_map.erase(matrix[i]);
  }
  
  if (!Map_Equality_Check(std_map, ft_map)) {
    return MAP_TEST_ERROR(KO_ERASE);
  }
  return MAP_TEST_OK(ERASE_TAG);
}

static void insert_random() {

#define RANDOM_ITERATIONS_NBR 10000

  ft::map<int, std::string> ft_map;
  std::map<int , std::string> std_map;

  srand(time(NULL));

  for (int i = 0; i < RANDOM_ITERATIONS_NBR; i++) {
    int rand_nb = rand();
    ft_map.insert(ft::pair<int, std::string>(rand_nb, "a"));
    std_map.insert(std::pair<int, std::string>(rand_nb, "a"));
  }

  if (!Map_Equality_Check(std_map, ft_map)) {
    return MAP_TEST_ERROR(KO_INSERT);
  }
#undef RANDOM_ITERATIONS_NBR
return MAP_TEST_OK(INSERT_TAG);
}

static void erase_random() {

#define RANDOM_ITERATIONS_NBR 10000

  ft::map<int, std::string> ft_map;
  std::map<int , std::string> std_map;

  int values[RANDOM_ITERATIONS_NBR] = {0};

  srand(time(NULL));

  for (int i = 0; i < RANDOM_ITERATIONS_NBR; i++) {
    int rand_nb = rand();
    ft_map.insert(ft::pair<int, std::string>(rand_nb, "a"));
    std_map.insert(std::pair<int, std::string>(rand_nb, "a"));
    values[i] = rand_nb;
  }

  // erasing in order of insertion does not make it easier,
  // the values are randomly distributed
  for (int i = 0; i < RANDOM_ITERATIONS_NBR; i++) {
    ft_map.erase(values[i]);
    std_map.erase(values[i]);
  }

  if (!Map_Equality_Check(std_map, ft_map)) {
    return MAP_TEST_ERROR(KO_ERASE);
  }
#undef RANDOM_ITERATIONS_NBR
  return MAP_TEST_OK(ERASE_TAG);
}

static void assignment_operator_test() {

  int matrix[11] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};

  ft::map<int, std::string> ft_m_1;
  ft::map<int, std::string> ft_m_2;
  ft::map<int, std::string> ft_m_3;
  for (int i = 0; i < 8; i++) {
    ft_m_1.insert(ft::pair<int, std::string>(matrix[i], "a"));
    ft_m_2.insert(ft::pair<int, std::string>(matrix[i + 1], "a"));
    ft_m_2.insert(ft::pair<int, std::string>(matrix[i + 2], "a"));
  }
  ft::map<int, std::string> tmp = ft_m_1;
  ft_m_1 = ft_m_2;
  ft_m_2 = ft_m_3;
  ft_m_3 = tmp;

  std::map<int, std::string> std_m_1;
  std::map<int, std::string> std_m_2;
  std::map<int, std::string> std_m_3;
  for (int i = 0; i < 8; i++) {
    std_m_1.insert(std::pair<int, std::string>(matrix[i], "a"));
    std_m_2.insert(std::pair<int, std::string>(matrix[i + 1], "a"));
    std_m_2.insert(std::pair<int, std::string>(matrix[i + 2], "a"));
  }
  std::map<int, std::string> __tmp = std_m_1;
  std_m_1 = std_m_2;
  std_m_2 = std_m_3;
  std_m_3 = __tmp;

  if (!Map_Equality_Check(std_m_1, ft_m_1)) {
    return MAP_TEST_ERROR(KO_ASSIGNMENT);
  }
  if (!Map_Equality_Check(std_m_2, ft_m_2)) {
    return MAP_TEST_ERROR(KO_ASSIGNMENT);
  }
  if (!Map_Equality_Check(std_m_3, ft_m_3)) {
    return MAP_TEST_ERROR(KO_ASSIGNMENT);
  }
  return MAP_TEST_OK(ASSIGNMENT_TAG);
}


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

  for (int i = 0; i < 4; i++) {
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

/*
 * Maps and sets do not allow key duplicates. This test does the
 * palyndrome check by having false duplicates as negative numbers.
 */
static void reverse_iteration() {
{
  ft::map<int, std::string> ft_map;

  int matrix[12] = {1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1};

  for (int i = 0; i < 12; i++) {
    ft_map.insert(ft::pair<int, std::string>(matrix[i], "hello"));
  }

  ft::map<int, std::string>::iterator it_ = ft_map.begin();
  ft::map<int, std::string>::iterator it_end = ft_map.end();
  ft::map<int, std::string>::reverse_iterator ti_ = ft_map.rbegin();
  ft::map<int, std::string>::reverse_iterator ti_end = ft_map.rend();

  for (; ti_ != ti_end && it_ != it_end; ++it_, ++ti_) {
    if (ti_->first != (-1)*(it_->first)) {
      std::cout << "expected : " << it_->first
                << " actual : " << (-1)*(ti_->first) << std::endl;
      return MAP_TEST_ERROR(KO_ITERATORS);
    }
  }
  if (ti_ != ti_end
      || it_ != it_end)
  {
    return MAP_TEST_ERROR(KO_ITERATORS);
  }
}
// same thing now from end to begin.
{
  ft::map<int, std::string> ft_map;

  int matrix[12] = {1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1};

  for (int i = 0; i < 12; i++) {
    ft_map.insert(ft::pair<int, std::string>(matrix[i], "hello"));
  }

  ft::map<int, std::string>::iterator it_begin = ft_map.begin();
  ft::map<int, std::string>::iterator it_end = ft_map.end();
  ft::map<int, std::string>::reverse_iterator ti_begin = ft_map.rbegin();
  ft::map<int, std::string>::reverse_iterator ti_end = ft_map.rend();

  --it_end;
  --ti_end;
  for (; ti_end != ti_begin && it_end != it_begin; --it_end, --ti_end) {
    if (it_end->first != (-1)*(ti_end->first)) {
      std::cout << "expected : " << it_end->first
                << " actual : " << (-1)*(ti_end->first) << std::endl;
      return MAP_TEST_ERROR(KO_ITERATORS);
    }
  }
  if (it_end != it_begin
      || ti_end != ti_end)
  {
    return MAP_TEST_ERROR(KO_ITERATORS);
  }
}
  return MAP_TEST_OK(ITERATOR_TAG);
}

// inserts TREE_SPONGE_MAX_SIZE, then deletes it entirely. Does this
// <iterations> times. 
static void sponge_test() {

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
#undef TREE_SPONGE_MAX_SIZE
  return MAP_TEST_OK(INSERT_TAG);
}

/*
 * If we insert one by one, which we do, it is impossible to achieve
 * some red black tree configurations. BUT by inserting-N and erasing-M
 * where N > M interesting configurations can appear.
 * This cannot ensure 100% that all possible erase scenarios will be met,
 * but it does get close.
 * Example : 
 *
 *         R
 *     /      \      
 *    B        B     ==> unachievable by insertion.  
 *  /  \     /  \
 * nil nil nil nil
 */
static void frog_on_well() {

#define TREE_SPONGE_MAX_SIZE 8400
#define ERASE_STEP (TREE_SPONGE_MAX_SIZE / 10)
#define ITERATIONS 100

  int save_insertions[TREE_SPONGE_MAX_SIZE * ITERATIONS] = {0};

  ft::map<int, std::string> ft_map;
  std::map<int, std::string> std_map;

  srand(time(NULL));

  int insertions = 0;
  int step = 1;
  // deletes TREE_SPONGE_MAX_SIZE / 40 nodes every TREE_SPONGE_MAX_SIZE / 10,
  // then adds TREE_SPONGE_MAX_SIZE / 10 more, etc, ITERATIONS times.
  for (int i = 0; i < ITERATIONS * TREE_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == ERASE_STEP) {
      // 1st erase [0, (1/4) * ERASE_STEP]
      // 2nd erase [ERASE_STEP, (1 + 1/4) * ERASE_STEP]
      // 3d erase [2 * ERASE_STEP, (2 + 1/4) * ERASE_STEP]
      // ...
      for (int k = ERASE_STEP * (step - 1);
           k < (insertions / 4) + (ERASE_STEP * (step - 1)); k++)
      {
        ft_map.erase(save_insertions[k]);
        std_map.erase(save_insertions[k]);
      }
      step += 1;
      insertions = 0;
    }
    int random_number = rand();
    ft_map.insert(ft::pair<int, std::string>(random_number, "hello"));
    std_map.insert(std::pair<int, std::string>(random_number, "hello"));
    save_insertions[insertions++] = random_number;
  }

  if (!Map_Equality_Check(std_map, ft_map)) {
    return MAP_TEST_ERROR(KO_FROG);
  }
  
#undef TREE_SPONGE_MAX_SIZE
#undef ERASE_STEP
#undef ITERATIONS

  return MAP_TEST_OK(FROG_ON_WELL);
}