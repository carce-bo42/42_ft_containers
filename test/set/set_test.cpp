// mirror of map test. Without pairs
#include "ft/set.hpp"
#include <set>
#include <iostream>
#include "../test_utils.hpp"
#include "../test.hpp"
#include <cmath>

template <typename T>
inline bool Set_Equality_Check(std::set<T> u, ft::set<T> v) {
  if (!ft::equal(u.begin(), u.end(), v.begin())) {
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
static void insert_with_hint();
static void sponge_test();
static void frog_on_well();
static void constructors_test();
static void assignment_operator_test();
static void reverse_iteration();
static void range_and_bounds_test();

void set_test() {
  insert_no_fix();
  delete_no_fix();
  insert_random();
  erase_random();
  insert_with_hint();
  sponge_test();
  frog_on_well();
  constructors_test();
  reverse_iteration();
  assignment_operator_test();
  range_and_bounds_test();
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

  ft::set<int> ft_set;
  std::set<int> std_set;

  int matrix[15] = {4, 13, 0, -9, 2, -12, -4, 1, 3, 11, 60, 5, 12, 40, 80};

  for (int i = 0; i < 15; i++) {
    ft_set.insert(matrix[i]);
    std_set.insert(matrix[i]);
  }

  if (!Set_Equality_Check(std_set, ft_set)) {
    return SET_TEST_ERROR(KO_INSERT);
  }
  return SET_TEST_OK(INSERT_TAG);
}

// Same tree as before, now deleting just the base
// The others need fixing XD
static void delete_no_fix() {
// quick check for erasing unexisting numbers / root
{
  ft::set<int> ft_set;

  ft_set.erase(1);
  ft_set.erase(2);

  if (!ft_set.insert(1).second) {
    return SET_TEST_ERROR(KO_ERASE);
  }
  ft_set.erase(1);
  if (!ft_set.insert(1).second) {
    return SET_TEST_ERROR(KO_ERASE);
  }
}

  ft::set<int> ft_set;
  std::set<int> std_set;

  int matrix[15] = {4, 13, 0, -9, 2, -12, -4, 1, 3, 11, 60, 5, 12, 40, 80};

  for (int i = 0; i < 15; i++) {
    ft_set.insert(matrix[i]);
    std_set.insert(matrix[i]);
  }

  // 5, 12, 40, 80
  for (int i = 14; i >= 11; i--) {
    ft_set.erase(matrix[i]);
    std_set.erase(matrix[i]);
  }

  // -12, -4, 1, 3
  for (int i = 8; i >= 5; i--) {
    ft_set.erase(matrix[i]);
    std_set.erase(matrix[i]);
  }
  
  if (!Set_Equality_Check(std_set, ft_set)) {
    return SET_TEST_ERROR(KO_ERASE);
  }
  return SET_TEST_OK(ERASE_TAG);
}

static void insert_random() {

#define RANDOM_ITERATIONS_NBR 10000

  ft::set<int> ft_set;
  std::set<int> std_set;

  srand(time(NULL));

  for (int i = 0; i < RANDOM_ITERATIONS_NBR; i++) {
    int rand_nb = rand();
    ft_set.insert(rand_nb);
    std_set.insert(rand_nb);
  }

  if (!Set_Equality_Check(std_set, ft_set)) {
    return SET_TEST_ERROR(KO_INSERT);
  }
#undef RANDOM_ITERATIONS_NBR
return SET_TEST_OK(INSERT_TAG);
}

static void erase_random() {

#define RANDOM_ITERATIONS_NBR 10000

  ft::set<int> ft_set;
  std::set<int> std_set;

  int values[RANDOM_ITERATIONS_NBR] = {0};

  srand(time(NULL));

  for (int i = 0; i < RANDOM_ITERATIONS_NBR; i++) {
    int rand_nb = rand();
    ft_set.insert(rand_nb);
    std_set.insert(rand_nb);
    values[i] = rand_nb;
  }

  // erasing in order of insertion does not make it easier,
  // the values are randomly distributed
  for (int i = 0; i < RANDOM_ITERATIONS_NBR; i++) {
    ft_set.erase(values[i]);
    std_set.erase(values[i]);
  }

  if (!Set_Equality_Check(std_set, ft_set)) {
    return SET_TEST_ERROR(KO_ERASE);
  }
#undef RANDOM_ITERATIONS_NBR
  return SET_TEST_OK(ERASE_TAG);
}


static void insert_with_hint() {

  ft::set<int> ft_set;

  ft_set.insert(ft_set.end(), 3);
  ft_set.insert(ft_set.begin(), 4);
  ft_set.insert(++ft_set.begin(), 5);
  ft_set.insert(--ft_set.end(), 6);
  ft_set.insert(ft_set.begin(), 123);
  ft_set.insert(ft_set.end(), 32);
  ft_set.insert(++(++ft_set.begin()), 2);
  ft_set.insert(--(--ft_set.end()), -32);
  ft_set.insert(ft_set.begin(), -42);
  ft_set.insert(ft_set.end(), 23);
  ft_set.insert(++(++(++ft_set.begin())), 7);
  ft_set.insert(--(--(--ft_set.end())), 424242);

  std::set<int> std_set;

  std_set.insert(std_set.end(), 3);
  std_set.insert(std_set.begin(), 4);
  std_set.insert(++std_set.begin(), 5);
  std_set.insert(--std_set.end(), 6);
  std_set.insert(std_set.begin(), 123);
  std_set.insert(std_set.end(), 32);
  std_set.insert(++(++std_set.begin()), 2);
  std_set.insert(--(--std_set.end()), -32);
  std_set.insert(std_set.begin(), -42);
  std_set.insert(std_set.end(), 23);
  std_set.insert(++(++(++std_set.begin())), 7);
  std_set.insert(--(--(--std_set.end())), 424242);

  if (!Set_Equality_Check(std_set, ft_set)) {
    return SET_TEST_ERROR(KO_INSERT);
  }
  return SET_TEST_OK(INSERT_TAG);
}

static void assignment_operator_test() {

  int matrix[11] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};

  ft::set<int> ft_m_1;
  ft::set<int> ft_m_2;
  ft::set<int> ft_m_3;
  for (int i = 0; i < 8; i++) {
    ft_m_1.insert(matrix[i]);
    ft_m_2.insert(matrix[i + 1]);
    ft_m_2.insert(matrix[i + 2]);
  }
  ft::set<int> tmp = ft_m_1;
  ft_m_1 = ft_m_2;
  ft_m_2 = ft_m_3;
  ft_m_3 = tmp;

  std::set<int> std_m_1;
  std::set<int> std_m_2;
  std::set<int> std_m_3;
  for (int i = 0; i < 8; i++) {
    std_m_1.insert(matrix[i]);
    std_m_2.insert(matrix[i + 1]);
    std_m_2.insert(matrix[i + 2]);
  }
  std::set<int> __tmp = std_m_1;
  std_m_1 = std_m_2;
  std_m_2 = std_m_3;
  std_m_3 = __tmp;

  if (!Set_Equality_Check(std_m_1, ft_m_1)) {
    return SET_TEST_ERROR(KO_ASSIGNMENT);
  }
  if (!Set_Equality_Check(std_m_2, ft_m_2)) {
    return SET_TEST_ERROR(KO_ASSIGNMENT);
  }
  if (!Set_Equality_Check(std_m_3, ft_m_3)) {
    return SET_TEST_ERROR(KO_ASSIGNMENT);
  }
  return SET_TEST_OK(ASSIGNMENT_TAG);
}

static void constructors_test() {
// empty
{
  ft::set<int> ft_m;
  std::set<int> std_m;

  if (!Set_Equality_Check(std_m, ft_m)) {
    return SET_TEST_ERROR(KO_CONSTRUCTOR);
  }
}
// range & copy
{
  ft::set<int> ft_m;
  std::set<int> std_m;

  int matrix[4] = {3, 4, 5, 6};

  for (int i = 0; i < 4; i++) {
    ft_m.insert(matrix[i]);
    std_m.insert(matrix[i]);
  }

  ft::set<int> ft_set(ft_m.begin(), ft_m.end());
  std::set<int> std_set(std_m.begin(), std_m.end());

  if (!Set_Equality_Check(std_set, ft_set)) {
    return SET_TEST_ERROR(KO_CONSTRUCTOR);
  }

  ft::set<int> ft_copy_map(ft_set);
  std::set<int> std_copy_map(std_set);

  if (!Set_Equality_Check(std_copy_map, ft_copy_map)) {
    return SET_TEST_ERROR(KO_CONSTRUCTOR);
  }
}
  return SET_TEST_OK(CONSTRUCTOR_TAG);
}

/*
 * Maps and sets do not allow key duplicates. This test does the
 * palyndrome check by having false duplicates as negative numbers.
 */
static void reverse_iteration() {
{
  ft::set<int> ft_set;

  int matrix[12] = {1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1};

  for (int i = 0; i < 12; i++) {
    ft_set.insert(matrix[i]);
  }

  ft::set<int>::iterator it_ = ft_set.begin();
  ft::set<int>::iterator it_end = ft_set.end();
  ft::set<int>::reverse_iterator ti_ = ft_set.rbegin();
  ft::set<int>::reverse_iterator ti_end = ft_set.rend();

  for (; ti_ != ti_end && it_ != it_end; ++it_, ++ti_) {
    if (*ti_ != (-1)*(*it_)) {
      std::cout << "expected : " <<  *it_
                << " actual : " << (-1)*(*ti_) << std::endl;
      return SET_TEST_ERROR(KO_ITERATORS);
    }
  }
  if (ti_ != ti_end
      || it_ != it_end)
  {
    return SET_TEST_ERROR(KO_ITERATORS);
  }
}
// same thing now from end to begin.
{
  ft::set<int> ft_set;

  int matrix[12] = {1, 2, 3, 4, 5, 6, -6, -5, -4, -3, -2, -1};

  for (int i = 0; i < 12; i++) {
    ft_set.insert(matrix[i]);
  }

  ft::set<int>::iterator it_begin = ft_set.begin();
  ft::set<int>::iterator it_end = ft_set.end();
  ft::set<int>::reverse_iterator ti_begin = ft_set.rbegin();
  ft::set<int>::reverse_iterator ti_end = ft_set.rend();

  --it_end;
  --ti_end;
  for (; ti_end != ti_begin && it_end != it_begin; --it_end, --ti_end) {
    if (*it_end != (-1)*(*ti_end)) {
      std::cout << "expected : " << *it_end
                << " actual : " << (-1)*(*ti_end) << std::endl;
      return SET_TEST_ERROR(KO_ITERATORS);
    }
  }
  if (it_end != it_begin
      || ti_end != ti_end)
  {
    return SET_TEST_ERROR(KO_ITERATORS);
  }
}
  return SET_TEST_OK(ITERATOR_TAG);
}

// inserts TREE_SPONGE_MAX_SIZE, then deletes it entirely. Does this
// <iterations> times. 
static void sponge_test() {

#define TREE_SPONGE_MAX_SIZE 8192

  int iterations = 100;
  int save_insertions[TREE_SPONGE_MAX_SIZE] = {0};

  ft::set<int> tree;
  std::set<int> map;

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
    tree.insert(random_number);
    map.insert(random_number);
    save_insertions[insertions++] = random_number;
  }
#undef TREE_SPONGE_MAX_SIZE
  return SET_TEST_OK(INSERT_TAG);
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

  ft::set<int> ft_set;
  std::set<int> std_set;

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
        ft_set.erase(save_insertions[k]);
        std_set.erase(save_insertions[k]);
      }
      step += 1;
      insertions = 0;
    }
    int random_number = rand();
    ft_set.insert(random_number);
    std_set.insert(random_number);
    save_insertions[insertions++] = random_number;
  }

  if (!Set_Equality_Check(std_set, ft_set)) {
    return SET_TEST_ERROR(KO_FROG);
  }
  
#undef TREE_SPONGE_MAX_SIZE
#undef ERASE_STEP
#undef ITERATIONS

  return SET_TEST_OK(FROG_ON_WELL);
}

static void range_and_bounds_test() {

  ft::set<int> ft_set;
  std::set<int> std_set;

  int matrix[15] = {4, 13, 0, -9, 2, -12, -4, 1, 3, 11, 60, 5, 12, 40, 80};

  for (int i = 0; i < 15; i++) {
    ft_set.insert(matrix[i]);
    std_set.insert(matrix[i]);
  }

  if (*ft_set.lower_bound(3) != *std_set.lower_bound(3)) {
    return SET_TEST_ERROR(KO_RANGE);
  }
  if (*ft_set.upper_bound(5) != *std_set.upper_bound(5)) {
    return SET_TEST_ERROR(KO_RANGE);
  }
  if (*(ft_set.equal_range(-4).first) != *(std_set.equal_range(-4).first)
      || *(ft_set.equal_range(-4).second) != *(std_set.equal_range(-4).second))
  {
    return SET_TEST_ERROR(KO_RANGE);
  }
  return SET_TEST_OK(RANGE_TAG);
}