#include "ft/map.hpp"
#include <map>
#include <cmath>
#include <stdlib.h>
#include "../test_utils.hpp"

// inserts TREE_SPONGE_MAX_SIZE, then deletes it entirely. Does this
// <iterations> times. 
void insert_delete_sponge_test() {

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