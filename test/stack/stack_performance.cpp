#include "ft/stack.hpp"
#include "ft/utils/utils.hpp"
#include <stack>
#include "../test.hpp"
#include <cmath>
#include "../colors.hpp"

void stack_performance() {

  std::cout << BLUE_BOLD
            << "///////////// [ STACK PERFORMANCE ] ///////////// "
            << UNSET << std::endl;

  int iterations = 100;
#define STACK_SPONGE_MAX_SIZE 100000

  int insertions = 0;

  ft::stack<int> ft_stack;
  time_t ft_start = current_timestamp();

  for (int i = 0; i < iterations * STACK_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == STACK_SPONGE_MAX_SIZE) {
      for (int k = 0; k < insertions; k++) {
        ft_stack.pop();
      }
      insertions = 0;
    }
    ft_stack.push(42);
  }

  time_t ft_end = current_timestamp();
  double ft_time = (double)((ft_end - ft_start)/1000.0);

  ////////////////// STD ///////////////////////////
  insertions = 0;

  std::stack<int> std_stack;
  time_t std_start = current_timestamp();

  for (int i = 0; i < iterations * STACK_SPONGE_MAX_SIZE; i++) {
    // delete all entries 
    if (insertions == STACK_SPONGE_MAX_SIZE) {
      for (int k = 0; k < insertions; k++) {
        std_stack.pop();
      }
      insertions = 0;
    }
    std_stack.push(42);
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
            << "/////////////////////////////////////////////////"
            << std::endl;
}