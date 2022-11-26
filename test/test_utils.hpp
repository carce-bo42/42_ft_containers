#ifndef CONTAINERS_TEST_UTILS_HPP
# define CONTAINERS_TEST_UTILS_HPP
# pragma once

#include <iostream>
#include <map>
#include <utility>
#include "colors.hpp"

#define VECTOR_TAG "VECTOR"
#define STACK_TAG "STACK"
#define MAP_TAG "MAP"
#define SET_TAG "SET"

#define CONSTRUCTOR_TAG "CONSTRUCTOR"
#define ITERATOR_TAG "ITERATOR"
#define ASSIGNMENT_TAG "OPERATOR="
#define ASSIGN_TAG "ASSIGN"
#define FROG_ON_WELL "🐸 on 🚰"
#define RESERVE_TAG "RESERVE"
#define INSERT_TAG "INSERT"
#define ERASE_TAG "ERASE"
#define RANGE_TAG "RANGE"

extern std::map<int, std::string> error_map;

typedef enum {
  OK = 0,
  KO_INSERT,
  KO_ERASE,
  KO_CONSTRUCTOR,
  KO_ITERATORS,
  KO_ASSIGNMENT,
  KO_ASSIGN,
  KO_FROG,
  KO_RESERVE,
  KO_RANGE
} TEST_RESULT;

// why static:
// https://stackoverflow.com/questions/53335887/
static inline void printTestError(int result, const char* container,
                          int line, const char* file)
{
  (void)result;
  std::cout << BLUE_BOLD << "["<< container << "]: "
            << UNSET << RED_BOLD << error_map[result]
            << " ERROR at "
            << file << ":" << line << UNSET << std::endl;
}

static inline void printTestOk(const char* tag, const char* container) {
  std::cout << BLUE_BOLD << "["<< container << "]: "
            << UNSET << GREEN_BOLD << tag << " TEST OK"
            << UNSET << std::endl; 
}

#define VECTOR_TEST_ERROR(result) \
        printTestError(result, VECTOR_TAG, __LINE__, __FILE__);
#define VECTOR_TEST_OK(test_tag) \
        printTestOk(test_tag, VECTOR_TAG);

#define STACK_TEST_ERROR(result) \
        printTestError(result, STACK_TAG, __LINE__, __FILE__);
#define STACK_TEST_OK(test_tag) \
        printTestOk(test_tag, STACK_TAG);

#define MAP_TEST_ERROR(result) \
        printTestError(result, MAP_TAG, __LINE__, __FILE__);
#define MAP_TEST_OK(test_tag) \
        printTestOk(test_tag, MAP_TAG);

#define SET_TEST_ERROR(result) \
        printTestError(result, SET_TAG, __LINE__, __FILE__);
#define SET_TEST_OK(test_tag) \
        printTestOk(test_tag, SET_TAG);

namespace ft {

  template< class InputIt1, class InputIt2 >
  bool equal_diff( InputIt1 first1, InputIt1 last1,
                   InputIt2 first2 )
  {
    while (first1 != last1) {
      if (*first1 != *first2) {
        std::cout << "expected : " << *first1
                  << " actual : " << *first2
                  << " at iteration " << std::endl;
        return false;
      }
      ++first1;
      ++first2;
    }
    return true;
  }

  template < typename T >
  bool show_diff( T cap1, T cap2) {
    std::cout << "expected : " << cap1
              << " actual : " << cap2
              << " at iteration " << std::endl;
    return false;
  }

  template < typename T >
  void fuck_unused_functions(const T& value) {
    (void)value;
    (void)&printTestOk;
    (void)&printTestError;
  }

  template< class InputIt1, class InputIt2 >
  bool equal_map( InputIt1 first1, InputIt1 last1,
                  InputIt2 first2 )
  {
    while (first1 != last1) {
      if (first1->first != first2->first) {
        return show_diff(first1->first, first2->first);
      }
      ++first1;
      ++first2;
    }
    return true;
  }
}

#endif