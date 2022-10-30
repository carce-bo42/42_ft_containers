#include <iostream>

#include "ft/RBT/red_black_tree.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"
#include "ft/utils/pair.hpp"
#include <map>
#include <sys/time.h>

// from https://stackoverflow.com/questions/3756323/how-to-get-the-current-time-in-milliseconds-from-c-in-linux
long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long milliseconds = te.tv_sec*1000L + te.tv_usec/1000;
    return milliseconds;
}

typedef enum {
  OK = 0,
  KO_INSERT = 1,
  KO_ERASE = 2
} RBTREE_TEST_RESULT;

int insert_hardcode() {
  return OK;
}
  //std::map<int, std::string> map;

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
/*
  map.insert(std::pair<int, std::string>(3, "hello)"));
  map.insert(std::pair<int, std::string>(5, "hello)"));
  map.insert(std::pair<int, std::string>(4, "hello)"));
  map.insert(std::pair<int, std::string>(2, "hello)"));
  map.insert(std::pair<int, std::string>(1, "hello)"));
  map.insert(std::pair<int, std::string>(0, "hello)"));
  map.insert(std::pair<int, std::string>(11, "hello)"));
  map.insert(std::pair<int, std::string>(13, "hello)"));
  map.insert(std::pair<int, std::string>(-12, "hello)"));
  map.insert(std::pair<int, std::string>(-9, "hello)"));
  map.insert(std::pair<int, std::string>(-4, "hello)"));
  map.insert(std::pair<int, std::string>(12, "hello)"));
  map.insert(std::pair<int, std::string>(40, "hello)"));
  map.insert(std::pair<int, std::string>(60, "hello)"));
  map.insert(std::pair<int, std::string>(80, "hello)"));

  ft::rb_tree<
    int,
    ft::pair<int, std::string> > tree;

  // root.
  ft::rb_tree_node<ft::pair<int, std::string> > *_root =
      tree.construct_node(ft::pair<int, std::string>(4, "hello"),
                          NULL, root, black);
  // root right/left
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_r =
      tree.construct_node(ft::pair<int, std::string>(13, "hello"),
                          _root, right_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_l =
      tree.construct_node(ft::pair<int, std::string>(0, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_ll =
      tree.construct_node(ft::pair<int, std::string>(-9, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lr =
      tree.construct_node(ft::pair<int, std::string>(2, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lll =
      tree.construct_node(ft::pair<int, std::string>(-12, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_llr =
      tree.construct_node(ft::pair<int, std::string>(-4, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lrl =
      tree.construct_node(ft::pair<int, std::string>(1, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_lrr =
      tree.construct_node(ft::pair<int, std::string>(3, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rl =
      tree.construct_node(ft::pair<int, std::string>(11, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rr =
      tree.construct_node(ft::pair<int, std::string>(60, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rll =
      tree.construct_node(ft::pair<int, std::string>(5, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rlr =
      tree.construct_node(ft::pair<int, std::string>(12, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rrl =
      tree.construct_node(ft::pair<int, std::string>(40, "hello"),
                          _root, left_child, black);
  ft::rb_tree_node<ft::pair<int, std::string> > *_root_rrr =
      tree.construct_node(ft::pair<int, std::string>(80, "hello"),
                          _root, left_child, black);

  _root->assign_left_child(_root_l);
  _root->assign_right_child(_root_r);
  _root_l->assign_parent(_root);
  _root_r->assign_parent(_root);

  _root_l->assign_left_child(_root_ll);
  _root_l->assign_right_child(_root_lr);
  _root_ll->assign_parent(_root_l);
  _root_lr->assign_parent(_root_l);

  _root_ll->assign_left_child(_root_lll);
  _root_ll->assign_right_child(_root_llr);
  _root_lll->assign_parent(_root_ll);
  _root_llr->assign_parent(_root_ll);

  _root_lr->assign_left_child(_root_lrl);  
  _root_lr->assign_right_child(_root_lrr);
  _root_lrl->assign_parent(_root_lr);
  _root_lrr->assign_parent(_root_lr);

  _root_r->assign_left_child(_root_rl);
  _root_r->assign_right_child(_root_rr);
  _root_rl->assign_parent(_root_r);
  _root_rr->assign_parent(_root_r);

  _root_rr->assign_left_child(_root_rrl);
  _root_rr->assign_right_child(_root_rrr);
  _root_rrl->assign_parent(_root_rr);
  _root_rrr->assign_parent(_root_rr);

  _root_rl->assign_left_child(_root_rll);  
  _root_rl->assign_right_child(_root_rlr);
  _root_rll->assign_parent(_root_rl);
  _root_rlr->assign_parent(_root_rl);

  tree.pure_insert(_root, NULL, right_child);

  // check wether map iterates the same as my tree implementation.
  for (std::map<int, std::string>::iterator it = map.begin();
       it != map.end(); it++)
  {
    std::cout << it->first << std::endl;
  }

  std::cout << std::endl;
  // iterate from min to max
  ft::rb_tree_iterator<ft::pair<int, std::string> > it(_root_lll);
  for (int i = 0; i < 16; i++) {
    std::cout << it->first << std::endl;
    it++;
  }
  std::cout << std::endl;
  ft::rb_tree_iterator<ft::pair<int, std::string> > it_(_root_rrr);
  for (int i = 0; i < 16; i++) {
    std::cout << it_->first << std::endl;;
    it_--;
  }
  return OK;
}
*/

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
int insert_no_fix() {

  ft::rb_tree<
    int,
    ft::pair<int, std::string> > tree;

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
  // until here i studied each insertion carefully. After I debugged
  // this first 10 numbers, everything else worked.
  tree.insert(ft::pair<int, std::string>(3, "hello"));
  tree.insert(ft::pair<int, std::string>(11, "hello"));
  tree.insert(ft::pair<int, std::string>(5, "hello"));
  tree.insert(ft::pair<int, std::string>(4, "hello"));
  tree.insert(ft::pair<int, std::string>(80, "hello"));
  for (ft::rb_tree<int, ft::pair<int, std::string> >::iterator it = tree.get_minimum();
        it != tree.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
  std::cout << "----------------" << std::endl;
  for (ft::rb_tree<int, ft::pair<int, std::string> >::iterator it(tree.get_maximum());
        it != tree.end(); it--)
  {
    std::cout << it->first << std::endl;
  }
  return OK;
}

int empty_tree_iteration() {
  ft::rb_tree<int, ft::pair<int, std::string> > tree; 
  for (ft::rb_tree<int, ft::pair<int, std::string> >::iterator it = tree.get_minimum();
        it != tree.end(); it++)
  {
    std::cout << it->first << std::endl;
  }
  std::cout << "----------------" << std::endl;
  for (ft::rb_tree<int, ft::pair<int, std::string> >::iterator it(tree.get_maximum());
        it != tree.end(); it--)
  {
    std::cout << it->first << std::endl;
  }
  return OK;
}

/*
 * Inserting a range form (1, n) in order is essentially fucking up 
 * the tree every 2 insertions (0 chill insertion). 
 */
int insert_with_fix_1() {

  int nbr_insertions = 10000;

  time_t ft_start = current_timestamp();
  ft::rb_tree<int, std::pair<int, std::string> > tree;

  for (int i = 0; i < nbr_insertions; i++) {
    tree.insert(std::pair<int, std::string>(i, "hello"));
  }
  time_t ft_end = current_timestamp();
  std::cout << "ft::rb_tree total_time for "
            << nbr_insertions << " insertions : "
            << (double)((ft_end - ft_start)/1000.0) << " s" << std::endl;
  
  time_t std_start = current_timestamp();
  std::map<int, std::string> map;

  for (int i = 0; i < nbr_insertions; i++) {
    map.insert(std::pair<int, std::string>(i, "hello"));
  }
  time_t std_end = current_timestamp();
  std::cout << "std::rb_tree total_time for "
            << nbr_insertions << " insertions : "
            << (double)((std_end - std_start)/1000.0) << " s" << std::endl;
  return OK;
}