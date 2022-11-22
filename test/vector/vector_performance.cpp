#include "ft/vector.hpp"
#include "ft/utils/utils.hpp"
#include <vector>
#include "../test.hpp"
#include <cmath>

void vector_performance() {
  
  int iterations = 1000;
#define VECTOR_SPONGE_MAX_SIZE 8192

  int insertions = 0;
  bool invert_deletion = false;

  ft::vector<int> ft_vec;
  time_t ft_start = current_timestamp();

  for (int i = 0; i < iterations * VECTOR_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == VECTOR_SPONGE_MAX_SIZE) {
      if (!invert_deletion) {
        for (int k = insertions - 1; k >= 0; k--) {
          ft_vec.erase(ft_vec.begin());
        }
        invert_deletion = true;
      } else {
        for (int k = 0; k < insertions; k++) {
          ft_vec.erase(ft_vec.begin() + (ft_vec.size() / 2));
        }
        invert_deletion = false;
      }
      insertions = 0;
    }
    ft_vec.push_back(42);
  }

  time_t ft_end = current_timestamp();
  double ft_time = (double)((ft_end - ft_start)/1000.0);

  ////////////////// STD ///////////////////////////
  insertions = 0;

  std::vector<int> std_vec;
  time_t std_start = current_timestamp();

  for (int i = 0; i < iterations * VECTOR_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == VECTOR_SPONGE_MAX_SIZE) {
      if (!invert_deletion) {
        for (int k = insertions - 1; k >= 0; k--) {
          std_vec.erase(std_vec.begin());
        }
        invert_deletion = true;
      } else {
        for (int k = 0; k < insertions; k++) {
          std_vec.erase(std_vec.begin() + (std_vec.size() / 2));
        }
        invert_deletion = false;
      }
      insertions = 0;
    }
    std_vec.push_back(42);
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
}