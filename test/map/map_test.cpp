#include <ft/map.hpp>
#include <map>
#include <iostream>
#include "../test_utils.hpp"

typedef enum {
  MAP_OK = 0,
  MAP_KO_INSERT = 1,
  MAP_KO_ERASE = 2
} MAP_TEST_RESULT;

template <typename T, typename U>
inline bool Map_Equality_Check(std::map<T, U> v, ft::map<T, U> u) {
  if (!ft::equal_map(u.begin(), u.end(), v.begin())) {
    return ft::equal_diff(u.begin(), u.end(), v.begin());
  }
  if (u.size() != v.size()) {
    return ft::show_diff(u.size(), v.size());
  }
  return true;
}

void map_reverse_iteration() {

  ft::map<int, std::string> ft_map;
  std::map<int, std::string> std_map;

  ft_map.insert(ft::pair<int, std::string>(13, "hello"));
  ft_map.insert(ft::pair<int, std::string>(1, "hello"));
  ft_map.insert(ft::pair<int, std::string>(60, "hello"));
  ft_map.insert(ft::pair<int, std::string>(0, "hello"));
  ft_map.insert(ft::pair<int, std::string>(-9, "hello"));
  ft_map.insert(ft::pair<int, std::string>(2, "hello"));
  ft_map.insert(ft::pair<int, std::string>(40, "hello"));
  ft_map.insert(ft::pair<int, std::string>(-12, "hello"));
  ft_map.insert(ft::pair<int, std::string>(-4, "hello"));
  ft_map.insert(ft::pair<int, std::string>(12, "hello"));
  ft_map.insert(ft::pair<int, std::string>(3, "hello"));
  ft_map.insert(ft::pair<int, std::string>(11, "hello"));
  ft_map.insert(ft::pair<int, std::string>(5, "hello"));
  ft_map.insert(ft::pair<int, std::string>(4, "hello"));
  ft_map.insert(ft::pair<int, std::string>(80, "hello"));

  std_map.insert(std::pair<int, std::string>(13, "hello"));
  std_map.insert(std::pair<int, std::string>(1, "hello"));
  std_map.insert(std::pair<int, std::string>(60, "hello"));
  std_map.insert(std::pair<int, std::string>(0, "hello"));
  std_map.insert(std::pair<int, std::string>(-9, "hello"));
  std_map.insert(std::pair<int, std::string>(2, "hello"));
  std_map.insert(std::pair<int, std::string>(40, "hello"));
  std_map.insert(std::pair<int, std::string>(-12, "hello"));
  std_map.insert(std::pair<int, std::string>(-4, "hello"));
  std_map.insert(std::pair<int, std::string>(12, "hello"));
  std_map.insert(std::pair<int, std::string>(3, "hello"));
  std_map.insert(std::pair<int, std::string>(11, "hello"));
  std_map.insert(std::pair<int, std::string>(5, "hello"));
  std_map.insert(std::pair<int, std::string>(4, "hello"));
  std_map.insert(std::pair<int, std::string>(80, "hello"));

  ft::map<int, std::string>::reverse_iterator it = ft_map.rbegin();

  int i = 0;
  std::map<int, std::string>::reverse_iterator it_ = std_map.rbegin();
  for (ft::map<int, std::string>::reverse_iterator it = ft_map.rbegin();
       it != ft_map.rend(); it++)
  {
    if (it->first != it_->first) {
      return MAP_TEST_ERROR (KO_INSERT);
    }
    it_++;
    i++;
  }

  std::cout << std::endl;
  std::cout << "normal iteration : " << std::endl;

  for (ft::map<int, std::string>::iterator it = ft_map.begin();
       it != ft_map.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
  
  return MAP_TEST_OK(MAP_TAG);
}