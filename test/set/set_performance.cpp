#include "ft/set.hpp"
#include <set>
#include <cmath>
#include <string.h>
#include "../test_utils.hpp"
#include "../test.hpp"

// Timing sponge test is about right for a performance test
void set_performance() {

  std::cout << BLUE_BOLD
            << "////////////// [ MAP PERFORMANCE ] ////////////// "
            << UNSET << std::endl;

#define TREE_SPONGE_MAX_SIZE 10000
  int iterations = 100;
  int save_insertions[TREE_SPONGE_MAX_SIZE] = {0};

  ft::set<int> ft_set;
  time_t ft_start = current_timestamp();

  srand(time(NULL));

  int insertions = 0;
  bool invert_deletion = false; // alternates between deleting from 0 -> TREE_SPONGE_MAX_SIZE
                                // and TREE_SPONGE_MAX_SIZE -> 0.
  for (int i = 0; i < iterations * TREE_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == TREE_SPONGE_MAX_SIZE) {
      if (!invert_deletion) {
        for (int k = insertions - 1; k >= 0; k--) {
          ft_set.erase(save_insertions[k]);
        }
        invert_deletion = true;
      } else {
        for (int k = 0; k < insertions; k++) {
          ft_set.erase(save_insertions[k]);
        }
        invert_deletion = false;
      }
      insertions = 0;
    }
    int random_number = rand();
    ft_set.insert(random_number);
    save_insertions[insertions++] = random_number;
  }

  time_t ft_end = current_timestamp();
  double ft_time = (double)((ft_end - ft_start)/1000.0);

  memset(save_insertions, 0, sizeof(save_insertions));

  // std
  std::set<int> std_set;
  time_t std_start = current_timestamp();

  insertions = 0;
  invert_deletion = false;
  for (int i = 0; i < iterations * TREE_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == TREE_SPONGE_MAX_SIZE) {
      if (!invert_deletion) {
        for (int k = insertions - 1; k >= 0; k--) {
          std_set.erase(save_insertions[k]);
        }
        invert_deletion = true;
      } else {
        for (int k = 0; k < insertions; k++) {
          std_set.erase(save_insertions[k]);
        }
        invert_deletion = false;
      }
      insertions = 0;
    }
    int random_number = rand();
    std_set.insert(random_number);
    save_insertions[insertions++] = random_number;
  }

  time_t std_end = current_timestamp();
  double std_time = (double)((std_end - std_start)/1000.0);

  std::cout << "ft time : " << ft_time << std::endl;
  std::cout << "std time : " << std_time << std::endl;
  std::cout << "RESULT : ft " << (fabs(std_time - ft_time)/std_time)*100.0;
  if (ft_time < std_time) {
    std::cout << "% faster than stl" << std::endl;
  } else {
    std::cout << "% slower than stl" << std::endl;
  }
  std::cout << BLUE_BOLD
            << "////////////////////////////////////////////////"
            << std::endl;
}