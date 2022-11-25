#include <iostream>

#include "ft/RBT/red_black_tree.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"
#include "ft/utils/pair.hpp"
#include "ft/RBT/reb_black_tree_reverse_iterator.hpp"
#include <map>
#include <cmath>
#include <stdlib.h>
#include "../test.hpp"
#include "../test_utils.hpp"

/*
 * The following tree insertions creates this tree:
 * 
 *                      4
 *                  /      \
 *               /            \
 *            /                  \
 *           0                   13
 *       /       \           /       \
 *      -9        2         11       60
 *    /   \     /   \     /   \     /   \
 *  -12   -4   1    3    5    12  40    80
 */
void insert_no_fix() {

  ft::rb_tree<int,ft::pair<int, std::string>,
    ft::map_get_key<int, ft::pair<int, std::string> > > tree;

  /*
  tree.insert(ft::pair<int, std::string>(4, "hello"));
  tree.insert(ft::pair<int, std::string>(13, "hello"));
  tree.insert(ft::pair<int, std::string>(0, "hello"));
  tree.insert(ft::pair<int, std::string>(-9, "hello"));
  tree.insert(ft::pair<int, std::string>(2, "hello"));
  tree.insert(ft::pair<int, std::string>(-12, "hello"));
  tree.insert(ft::pair<int, std::string>(-4, "hello"));
  tree.insert(ft::pair<int, std::string>(1, "hello"));
  tree.insert(ft::pair<int, std::string>(3, "hello"));
  tree.insert(ft::pair<int, std::string>(11, "hello"));
  tree.insert(ft::pair<int, std::string>(60, "hello"));
  tree.insert(ft::pair<int, std::string>(5, "hello"));
  tree.insert(ft::pair<int, std::string>(12, "hello"));
  tree.insert(ft::pair<int, std::string>(40, "hello"));
  tree.insert(ft::pair<int, std::string>(80, "hello"));
  */

 /*                     13
  *                   1   60
  *                 0
  */
  tree.insert(ft::pair<int, std::string>(13, "hello"));
  tree.insert(ft::pair<int, std::string>(1, "hello"));
  tree.insert(ft::pair<int, std::string>(60, "hello"));
  tree.insert(ft::pair<int, std::string>(0, "hello"));
  tree.insert(ft::pair<int, std::string>(-9, "hello"));
  tree.insert(ft::pair<int, std::string>(2, "hello"));
  tree.insert(ft::pair<int, std::string>(40, "hello"));
  tree.insert(ft::pair<int, std::string>(-12, "hello"));
  tree.insert(ft::pair<int, std::string>(-4, "hello"));
  tree.insert(ft::pair<int, std::string>(12, "hello"));
  tree.insert(ft::pair<int, std::string>(3, "hello"));
  tree.insert(ft::pair<int, std::string>(11, "hello"));
  tree.insert(ft::pair<int, std::string>(5, "hello"));
  tree.insert(ft::pair<int, std::string>(4, "hello"));
  tree.insert(ft::pair<int, std::string>(80, "hello"));
  for (ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator it = tree.begin();
        it != tree.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
  std::cout << "----------------" << std::endl;
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator a = tree.end();
  a++;
  a++;
  std::cout << "end after 2 increments : " << a->first << std::endl;
  std::cout << "----------------" << std::endl;
  MAP_TEST_OK(MAP_TAG);
}

void empty_tree_iteration() {
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > tree; 
  for (ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator it = tree.begin();
        it != tree.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
  std::cout << "----------------" << std::endl;
  MAP_TEST_OK(MAP_TAG);
}

/*
 * Inserting a range form (1, n) in order is essentially fucking up 
 * the tree every 2 insertions (0 chill insertion). 
 */
void insert_performance() {

  int nbr_insertions = 50000;
  int nbr_insertions_mid = 25000;

  time_t ft_start = current_timestamp();
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > tree;

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = 0; i < nbr_insertions; i++) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  time_t ft_end = current_timestamp();
  double ft_time = (double)((ft_end - ft_start)/1000.0);
  std::cout << "ft::rb_tree total_time for "
            << nbr_insertions << " insertions : "
            << ft_time << " s" << std::endl;
  
  time_t std_start = current_timestamp();
  std::map<int, std::string> map;

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = 0; i < nbr_insertions; i++) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }

  time_t std_end = current_timestamp();
  double std_time = (double)((std_end - std_start)/1000.0);
  std::cout << "std::rb_tree total_time for "
            << nbr_insertions << " insertions : "
            << std_time << " s" << std::endl;

  std::cout << "ft was " << (fabs(std_time - ft_time)/std_time)*100.0
            << "% slower than stl" << std::endl;
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++)  {
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  MAP_TEST_OK(MAP_TAG);
}

void insert_with_hint() {

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > tree;

  tree.insert_with_hint(tree.begin(), ft::pair<int, std::string>(3, "hello"));
  tree.insert_with_hint(tree.begin(), ft::pair<int, std::string>(4, "hello"));
  tree.insert_with_hint(tree.begin(), ft::pair<int, std::string>(5, "he ,mllo"));
  tree.insert_with_hint(tree.begin(), ft::pair<int, std::string>(6, "hello"));
  tree.insert_with_hint(tree.begin() + 2, ft::pair<int, std::string>(123, "hello"));
  tree.insert_with_hint(tree.begin() + 3, ft::pair<int, std::string>(32, "hello"));
  tree.insert_with_hint(tree.begin() + 1, ft::pair<int, std::string>(2, "hello"));
  tree.insert_with_hint(tree.begin() + 3, ft::pair<int, std::string>(-32, "hello"));
  tree.insert_with_hint(tree.begin() + 2, ft::pair<int, std::string>(-42, "hello"));
  tree.insert_with_hint(tree.begin() + 7, ft::pair<int, std::string>(23, "hello"));
  tree.insert_with_hint(tree.begin() + 9, ft::pair<int, std::string>(7, "hello"));

  MAP_TEST_OK(MAP_TAG);
}

/*
 *                      4
 *                  /      \
 *               /            \
 *            /                  \
 *           0                   13
 *       /       \           /       \
 *      -9        2         11       60
 *    /   \     /   \     /   \     /   \
 *  -12   -4   1    3    5    12  40    80
 *
 */
void erase_1() {

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > tree;

  tree.insert(ft::pair<int, std::string>(4, "hello"));
  tree.insert(ft::pair<int, std::string>(13, "hello"));
  tree.insert(ft::pair<int, std::string>(0, "hello"));
  tree.insert(ft::pair<int, std::string>(-9, "hello"));
  tree.insert(ft::pair<int, std::string>(2, "hello"));
  tree.insert(ft::pair<int, std::string>(-12, "hello"));
  tree.insert(ft::pair<int, std::string>(-4, "hello"));
  tree.insert(ft::pair<int, std::string>(1, "hello"));
  tree.insert(ft::pair<int, std::string>(3, "hello"));
  tree.insert(ft::pair<int, std::string>(11, "hello"));
  tree.insert(ft::pair<int, std::string>(60, "hello"));
  tree.insert(ft::pair<int, std::string>(5, "hello"));
  tree.insert(ft::pair<int, std::string>(12, "hello"));
  tree.insert(ft::pair<int, std::string>(40, "hello"));
  tree.insert(ft::pair<int, std::string>(80, "hello"));

  std::map<int, std::string> map;

  map.insert(std::pair<int, std::string>(4, "hello"));
  map.insert(std::pair<int, std::string>(13, "hello"));
  map.insert(std::pair<int, std::string>(0, "hello"));
  map.insert(std::pair<int, std::string>(-9, "hello"));
  map.insert(std::pair<int, std::string>(2, "hello"));
  map.insert(std::pair<int, std::string>(-12, "hello"));
  map.insert(std::pair<int, std::string>(-4, "hello"));
  map.insert(std::pair<int, std::string>(1, "hello"));
  map.insert(std::pair<int, std::string>(3, "hello"));
  map.insert(std::pair<int, std::string>(11, "hello"));
  map.insert(std::pair<int, std::string>(60, "hello"));
  map.insert(std::pair<int, std::string>(5, "hello"));
  map.insert(std::pair<int, std::string>(12, "hello"));
  map.insert(std::pair<int, std::string>(40, "hello"));
  map.insert(std::pair<int, std::string>(80, "hello"));

  tree.erase(0);
  tree.erase(-4);
  tree.erase(-9);
  tree.erase(13);
  tree.erase(1);
  tree.erase(11);
  tree.erase(60);
  tree.erase(40);
  tree.erase(5);
  tree.erase(2);

  map.erase(0);
  map.erase(-4);
  map.erase(-9);
  map.erase(13);
  map.erase(1);
  map.erase(11);
  map.erase(60);
  map.erase(40);
  map.erase(5);
  map.erase(2);

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++)  {
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  MAP_TEST_OK(MAP_TAG);
}

void erase_2() {

  int nbr_insertions = 50000;
  int nbr_insertions_mid = 25000;

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > tree;

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = 0; i < nbr_insertions; i++) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }

  std::map<int, std::string> map;

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = 0; i < nbr_insertions; i++) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it_2 = tree.begin();
  std::map<int, std::string>::iterator std_it_2 = map.begin();
  for (int i = 0; i < (int)map.size(); i++) {
    //std::cout << "i : " << i << std::endl;
    if (ft_it_2->first != std_it_2->first) {
      std::cout << "expected : " << std_it_2->first
                << " actual : " << ft_it_2->first
                << " at iterator pos " << i << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it_2;
    ++std_it_2;
  }
  time_t ft_start = current_timestamp();

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    tree.erase(i);
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    tree.erase(i);
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    tree.erase(i);
  }
  for (int i = 0; i < nbr_insertions; i++) {
    tree.erase(i);
  }

  time_t ft_end = current_timestamp();
  double ft_time = (double)((ft_end - ft_start)/1000.0);
  std::cout << "ft::rb_tree total_time for "
            << 2*nbr_insertions << " deletions : "
            << ft_time << " s" << std::endl;
  
  time_t std_start = current_timestamp();

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    map.erase(i);
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    map.erase(i);
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    map.erase(i);
  }
  for (int i = 0; i < nbr_insertions; i++) {
    map.erase(i);
  }

  time_t std_end = current_timestamp();
  double std_time = (double)((std_end - std_start)/1000.0);
  std::cout << "std::rb_tree total_time for "
            << 2*nbr_insertions << " deletions : "
            << std_time << " s" << std::endl;

  std::cout << "ft was " << (fabs(std_time - ft_time)/std_time)*100.0
            << "% slower than stl" << std::endl;
  MAP_TEST_OK(MAP_TAG);
}


void erase_performance() {

  int nbr_insertions = 50000;
  int nbr_insertions_mid = 25000;

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > tree;
  std::map<int, std::string> map;

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = 0; i < nbr_insertions; i++) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    tree.insert(ft::pair<int, std::string>(i, "hello"));
  }

  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = 0; i < nbr_insertions; i++) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  {
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++)  {
    //std::cout << "i : " << i << std::endl;
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i
                << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  }
  // erase step, comparison step.
  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    tree.erase(i);
  }
  for (int i = nbr_insertions_mid; i < nbr_insertions; i++) {
    map.erase(i);
  }
  {
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++)  {
    //std::cout << "i : " << i << std::endl;
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i
                << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  }
  // erase step, then delete
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    tree.erase(i);
  }
  for (int i = -nbr_insertions_mid; i > -nbr_insertions; i--) {
    map.erase(i);
  }
  {
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++) {
    //std::cout << "i : " << i << std::endl;
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i
                << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  }
  // erase step, then delete
  for (int i = -1; i > -nbr_insertions; i--) {
    tree.erase(i);
  }
  for (int i = -1; i > -nbr_insertions; i--) {
    map.erase(i);
  }
  {
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++)  {
    //std::cout << "i : " << i << std::endl;
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i
                << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  }
  // erase step, then delete
  for (int i = 0; i < nbr_insertions; i++) {
    tree.erase(i);
  }
  for (int i = 0; i < nbr_insertions; i++) {
    map.erase(i);
  }
  {
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++)  {
    //std::cout << "i : " << i << std::endl;
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i
                << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  }
  MAP_TEST_OK(MAP_TAG);
}

// inserts TREE_SPONGE_MAX_SIZE, then deletes it entirely. Does this
// <iterations> times. 
void insert_delete_sponge_test() {

#define TREE_SPONGE_MAX_SIZE 8192

  int iterations = 100;
  int save_insertions[TREE_SPONGE_MAX_SIZE] = {0};

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > tree;
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

  // Last loop ends up iterations at size = 8192.
  std::cout << map.size() << std::endl;

  // check equality between maps.
  
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator ft_it = tree.begin();
  std::map<int, std::string>::iterator std_it = map.begin();
  for (int i = 0; i < (int)map.size(); i++) {
    if (ft_it->first != std_it->first) {
      std::cout << "expected : " << std_it->first
                << " actual : " << ft_it->first
                << " at iterator pos " << i
                << std::endl;
      return MAP_TEST_ERROR(TREE_KO_INSERT);
    }
    ++ft_it;
    ++std_it;
  }
  MAP_TEST_OK(MAP_TAG);
}