#include "ft/vector.hpp"
#include "ft/stack.hpp"
#include "ft/map.hpp"
#include "ft/set.hpp"

#include <vector>
#include <map>
#include <stdio.h>
#include <iostream>
#include "map/rbtree_test.hpp"
#include "map/map_test.hpp"

// static declarations and unused functions :
// #include "test_utils.hpp"

#include "test.hpp"

#include "ft/RBT/red_black_tree.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"
#include "ft/utils/pair.hpp"
#include "ft/utils/utils.hpp"
#include "ft/RBT/reb_black_tree_reverse_iterator.hpp"

/*
int rbtree_test() {
  if (insert_hardcode() != 0
      || reverse_iteration() != 0
      //|| insert_no_fix() != 0
      //|| insert_with_fix_1() != 0
      //|| insert_performance() != 0
      //|| erase_1() != 0
      //|| erase_2() != 0
      //|| erase_performance() != 0
      //|| insert_delete_sponge_test() != 0
      || map_reverse_iteration() != 0)
  {
    return 1;
  }
  return 0;
}
*/

int main() {

  vector_test();
  vector_performance();
  /*
  int myints[] = {75,23,65,42,13};
  ft::set<int> myset (myints,myints+5);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;
  */
  //ft::map<int, std::string> ft_map;
  //ft_map.find(2);
  /*int a = 4;
  std::vector<int> vec(10, a);
  ft::vector<int> asd;

  asd.assign(3, 7);*/


  /*
{
	ft::pair<int, std::string> my_pair(8, "salut");
	ft::map<int, std::string>	 test;
	ft::map<int, std::string>::iterator	it;

	test.insert(my_pair);
	test.insert(ft::pair<int, std::string>(-4, "bar"));
	test.insert(ft::pair<int, std::string>(2, "machin"));
	test.insert(ft::pair<int, std::string>(3, "foo"));
	test.insert(ft::pair<int, std::string>(746, "Marcel"));
	test.insert(ft::pair<int, std::string>(1, "truc"));
  it = test.begin();
	std::cout << '\n';

  std::cout << "size : " << test.size() << std::endl;
	while (it != test.end())
	{
		// std::cout << "start of while\n";
		std::cout << it->first << ", " << it->second << '\n';
		it++;
// 		std::cout << "iterator incremented\n";

// #ifndef STD
// 		std::cout << it.getPointer() << '\n';
// 		std::cout << test.end().getPointer() << '\n';
// #endif

	}
	std::cout << "End of display loop\n";


  for (ft::map<int, std::string>::const_iterator a = test.begin();
       a != test.end(); a++)
  {
    std::cout << a->first << std::endl;
  }
}*/
/*
{
  ft::map<char,int> mymap;


	if (mymap.begin() != mymap.end())
		std::cout << "This should not happen\n";

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

	if (mymap.begin() == mymap.end())
		std::cout << "This is wrong\n";
  // show content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';

	std::cout << "Hello there\n";
	for (ft::map<char,int>::const_iterator it=mymap.begin(); it!=mymap.end(); it++)
    std::cout << it->first << " => " << it->second << '\n';
	std::cout << "General Kenobi\n";

	ft::map<char, int>::const_iterator it = mymap.begin();
	ft::map<char, int>::const_iterator ti = mymap.end();
	std::cout << "Wupwup\n";

	it++;
	++it;
	it--;
	--it;
	std::cout << "marker1\n";

	ti--;
	--ti;
	++ti;
	ti++;

	ti = it;

	std::cout << "Trump is a kiddo\n";
	ft::map<char, int>::iterator end = mymap.end();
	while(it != end)
	{
    	std::cout << it->first << " => " << it->second << '\n';
		it++;
	}

}
{
  std::cout << std::endl;
  std::cout << std::endl;
  ft::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

std::cout << "\n\n========\n\n";

  ft::map<char,int>::iterator it = mymap.end();
  std::cout << "end : " << it->first << '\n';
  it--;
  std::cout << "end - 1 " << it->first << '\n';
  for (it = --mymap.end(); it!=mymap.begin(); --it)
    std::cout << it->first << " => " << it->second << '\n';
  std::cout << it->first << " => " << it->second << '\n';

  return 0;

}
*/
/*
{
  ft::map<char,int> foo,bar;
  foo['a']=100;
  foo['b']=200;
  bar['a']=10;
  bar['z']=1000;

  // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}
*/
/*
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  std::cout << "found b\n";
  mymap.erase (it);                   // erasing by iterator
  // OK:
  //for (it=mymap.begin(); it!=mymap.end(); ++it)
  //  std::cout << it->first << " => " << it->second << '\n';

  std::cout << "erase iterator to b\n";
  mymap.erase ('c');                  // erasing by key
  std::cout << "erase by key 'c'\n";
  it=mymap.find ('e');
  std::cout << "erase by range 'e' to end\n";
  mymap.erase ( it, mymap.end() );    // erasing by range
  std::cout << " display :\n";
  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
*/
/*
  ft::map<char,int> foo,bar;
  foo['a']=100;
  foo['b']=200;
  bar['a']=10;
  bar['z']=1000;

  // foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
  return 0;
*/
}
  //printf("%lu \n", vec.capacity());
  //printf("%lu \n", vec.size());

  //printf("%lu \n", vec.capacity());
  //printf("%lu \n", vec.size());
  //printf("%i \n", vec.front()); segfaultea.
  /*
  if (vector_test() != 0) {
    return 1;
  }
  if (rbtree_test() != 0) {
    return 1;
  } */
/*
  {
  // ITERATORS FOR MAP DEMONSTRATION
  std::map<int, std::string> a;
  std::map<int, std::string>::iterator i = a.begin();
  std::map<int, std::string>::iterator j = a.end();
  std::map<int, std::string>::reverse_iterator k = a.rbegin();
  std::map<int, std::string>::reverse_iterator l = a.rend();
  std::cout << " aaaaaaaaa " << i->first << std::endl;
  if (j != i) {
    std::cout << "begin != end in map of " << a.size() << " elements" << std::endl;
  } else {
    std::cout << "begin == end in map of " << a.size() << " elements" << std::endl;
  } 
  if (k != l) {
    std::cout << "rbegin != rend in map of " << a.size() << " elements " << std::endl;
  } else {
    std::cout << "rbegin = rend in map of " << a.size() << " elements " << std::endl;
  }
  }

  // ITERATORS FOR MAP DEMONSTRATION
  std::map<int, std::string> a;
  a.insert(std::pair<int, std::string>(3, "aa"));
  std::map<int, std::string>::iterator i = a.begin();
  std::map<int, std::string>::iterator j = a.end();
  std::map<int, std::string>::reverse_iterator k = a.rbegin();
  std::map<int, std::string>::reverse_iterator l = a.rend();
  std::cout << " aaaaaaaaa " << i->first << std::endl;
  if (j != i) {
    std::cout << "begin != end in map of " << a.size() << " elements" << std::endl;
  } else {
    std::cout << "begin == end in map of " << a.size() << " elements" << std::endl;
  } 
  if (k != l) {
    std::cout << "rbegin != rend in map of " << a.size() << " elements " << std::endl;
  } else {
    std::cout << "rbegin = rend in map of " << a.size() << " elements " << std::endl;
  }

  std::cout << "MAP : " << std::endl;

  std::cout << "rbegin ptr : " << k->first << std::endl;
  std::cout << "rend ptr : " << l->first << std::endl;
  std::cout << "end ptr : " << j->first << std::endl;

  ft::vector<int> lol;
  ft::vector<int>::iterator xd = lol.begin();
  ft::vector<int>::reverse_iterator dx = lol.rend();

  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > > aa;
  aa.insert(ft::pair<int, std::string>(3, "aa"));
  //ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator i_ = aa.begin();
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::iterator j_ = aa.end();
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::reverse_iterator k_ = aa.rbegin();
  ft::rb_tree<int, ft::pair<int, std::string>, ft::map_get_key<int, ft::pair<int, std::string> > >::reverse_iterator l_ = aa.rend();
  //ft::vector<char>::iterator char_it(int_it); // Substitution failure
  std::cout << "TREE : " << std::endl;

  std::cout << "rbegin ptr : " << k_->first << std::endl;
  std::cout << "rend ptr : " << l_->first << std::endl;
  std::cout << "end ptr : " << j_->first << std::endl;
}
  return 0;
}
*/
