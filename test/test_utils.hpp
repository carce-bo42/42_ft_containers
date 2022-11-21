#ifndef CONTAINERS_TEST_UTILS_HPP
# define CONTAINERS_TEST_UTILS_HPP
# pragma once

#include <iostream>
#include <map>
#include <utility>

#define VECTOR_TAG "VECTOR"
#define STACK_TAG "STACK"
#define MAP_TAG "MAP"
#define SET_TAG "SET"

#define CONSTRUCTOR_TAG "CONSTRUCTOR"
#define INSERT_TAG "INSERT"
#define ERASE_TAG "ERASE"

static std::map<int, std::string> vector_errors;
static std::map<std::string, std::map<int, std::string> > error_map;

typedef enum {
  OK = 0,
  KO_INSERT = 1,
  KO_ERASE = 2,
  KO_CONSTRUCTOR = 3
} VECTOR_TEST_RESULT;

# define BLUE_BOLD "\e[1;34m"
# define GREEN_BOLD "\e[1;32m"
# define MAG_BOLD "\e[1;35m"
# define RED_BOLD "\e[1;31m"
# define UNSET "\033[0m"

// why static:
// https://stackoverflow.com/questions/53335887/
static void printTestError(int result, const char* container,
                          int line, const char* file)
{
  // ToDo finish error mappper (test_utils.cpp)
  (void)result;
  std::cout << BLUE_BOLD << "["<< container << "]: "
            << UNSET << RED_BOLD << " ERROR at "
            << file << ":" << line << UNSET << std::endl;
}

static void printTestOk(const char* tag, const char* container) {
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

#endif