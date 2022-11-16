#include <ft/map.hpp>
#include <map>
#include <iostream>
#include "../debug.hpp"

typedef enum {
  OK = 0,
  KO_INSERT = 1,
  KO_ERASE = 2
} MAP_TEST_RESULT;

int map_reverse_iteration() {

  ft::map<int, std::string> mymap;
  
  std::map<int, std::string> map;

  mymap.insert(ft::pair<int, std::string>(13, "hello"));
  mymap.insert(ft::pair<int, std::string>(1, "hello"));
  mymap.insert(ft::pair<int, std::string>(60, "hello"));
  mymap.insert(ft::pair<int, std::string>(0, "hello"));
  mymap.insert(ft::pair<int, std::string>(-9, "hello"));
  mymap.insert(ft::pair<int, std::string>(2, "hello"));
  mymap.insert(ft::pair<int, std::string>(40, "hello"));
  mymap.insert(ft::pair<int, std::string>(-12, "hello"));
  mymap.insert(ft::pair<int, std::string>(-4, "hello"));
  mymap.insert(ft::pair<int, std::string>(12, "hello"));
  mymap.insert(ft::pair<int, std::string>(3, "hello"));
  mymap.insert(ft::pair<int, std::string>(11, "hello"));
  mymap.insert(ft::pair<int, std::string>(5, "hello"));
  mymap.insert(ft::pair<int, std::string>(4, "hello"));
  mymap.insert(ft::pair<int, std::string>(80, "hello"));

  map.insert(std::pair<int, std::string>(13, "hello"));
  map.insert(std::pair<int, std::string>(1, "hello"));
  map.insert(std::pair<int, std::string>(60, "hello"));
  map.insert(std::pair<int, std::string>(0, "hello"));
  map.insert(std::pair<int, std::string>(-9, "hello"));
  map.insert(std::pair<int, std::string>(2, "hello"));
  map.insert(std::pair<int, std::string>(40, "hello"));
  map.insert(std::pair<int, std::string>(-12, "hello"));
  map.insert(std::pair<int, std::string>(-4, "hello"));
  map.insert(std::pair<int, std::string>(12, "hello"));
  map.insert(std::pair<int, std::string>(3, "hello"));
  map.insert(std::pair<int, std::string>(11, "hello"));
  map.insert(std::pair<int, std::string>(5, "hello"));
  map.insert(std::pair<int, std::string>(4, "hello"));
  map.insert(std::pair<int, std::string>(80, "hello"));

  ft::map<int, std::string>::reverse_iterator it = mymap.rbegin();

  std::cout << "reverse iteration : " << std::endl;

  int i = 0;
  std::map<int, std::string>::reverse_iterator it_ = map.rbegin();
  for (ft::map<int, std::string>::reverse_iterator it = mymap.rbegin();
       it != mymap.rend(); it++)
  {
    if (it->first != it_->first) {
      std::cout << "expected : " << it_->first
                << " actual : " << it->first
                << " at iteration " << i << std::endl;
      return TEST_ERROR(KO_INSERT);
    }
    it_++;
    i++;
  }

  std::cout << std::endl;
  std::cout << "normal iteration : " << std::endl;

  for (ft::map<int, std::string>::iterator it = mymap.begin();
       it != mymap.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
  
  return OK;
}