#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP
#pragma once

#include <memory>
#include <functional>
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"

namespace ft {

// KeyOfVal functor for rb_tree
template < typename Key,
           typename Val /* = ft::pair<Key, typename T> */ >
struct get_key {

  Key operator()(const Val& value) {
    return value.first;
  }
};

/* To understand the allocator template :
 * https://gcc.gnu.org/bugzilla/attachment.cgi?id=34289
 * PD: search for '__alloc_traits'. Check the definition of 'struct rebind'
 * inside __alloc_traits, then search for 'struct rebind'.
 * Find the one inside class allocator. The STL tree calls the template inside __alloc_traits,
 * im calling the template inside std::allocator which is the same. 
 */

/* 
 * Things about optimization :
 * - Less code does not mean more optimized.
 * - Recursion is cool but runs terribly slow compared to loops.
 * - STL implements header, with which they can do cool things,
 *   such as access quickly to minimum/maximum, which is curcial
 *   when inserting, because you can skip checking if the key is
 *   already in the map by just checking if its outside of [min, max]
 *   interval.
 */

/*
 * Red black trees must hold :
 * (0) Nodes are either RED or BLACK (surprise)
 * (1) Root and nil leaves are BLACK.
 * (2) If a node is RED, its children are BLACK.
 * (3) All paths from a node (not counting the starting
 *     one) to its nil descendants contain the same number
 *     of black nodes.
 * 
 * This implementation's rules :
 * _root is the only node which has !node->parent.
 * A leaf of the tree will !have node->right && !node->left
 */

template < typename Key,
           typename Val, // Val is some implementation of a pair of values.
           typename KeyOfVal = ft::get_key<Key, Val>,
                              // In stl, this is used presumably to generalize
                              // Val to any structure containing Key. With this
                              // functor you are supposed to operate on Val
                              // types to extract Keys.
                              // I like how this also hints how there must
                              // be a Key inside Val (Key Of Val).
           typename Compare = std::less<Key>, // functor
           typename Alloc = std::allocator<Val> >
class rb_tree {

  protected:
  
  typedef rb_tree_node<Val>                  node_type;
  typedef node_type*                         node_ptr;
  typedef const node_type*                   const_node_ptr;
  typedef typename node_type::n_color        n_color;
  // get another allocator.
  typedef typename Alloc::
          template rebind<node_type >::other node_allocator;

  public:

  typedef Key                              key_type;
  typedef size_t                           size_type;
  typedef rb_tree_iterator<Val>            iterator;
  typedef rb_tree_iterator<const Val>      const_iterator;

  private:

  node_ptr       _root;
  // node end is the dummy node used for end() and rend().
  // it contains no parent, no childs, and is appended to
  // the right of the max and to the left of the min. If
  // the tree is empty, is equal to root.
  node_ptr       node_end;
  size_type      node_count;
  node_allocator node_alloc;
  Compare        key_cmp;
  KeyOfVal       key_of_val;

/*
 * red black tree interface  
 * 
 * get_node_from_key()
 * get_node_key is not implemented because get_key exists
 * get_node_data()
 * construct_node()
 * destroy_node()
 * search_node() given a key
 * get_minimum()
 * get_maximum()
 * /////// iterators go somewhere else
 * pure_insert() - insert a node on the tree 
 * pure_erase() - erase a node from the tree
 * after_insert_check() : will determine if a newly inserted
 *                        node is a problem and which problem
 *                        is it.
 * after_erase_check() : same but with deletion, in case theres
 *                       diferent conditions met. But will somehow
 *                       redirect it to rebalance in a way rebalance
 *                       is agnostic to wether an insertion or 
 *                       deletion happened.
 * rebalance() : will recieve a node and a problem to solve.
 *
 */

  public:

  rb_tree()
  :
    _root(0),
    node_count(0),
    node_alloc()
  {
    // iterator end. It goes at the right of the max
    // value and at the left of the min. Starts being root.
    node_end = construct_node(Val(), 0);
    node_end->assign_parent(0);
    node_end->assign_left_child(0);
    node_end->assign_right_child(0);
    node_end->color = black;
    _root = node_end;
  }

  ~rb_tree() {
    delete_subtree(_root);
    destroy_node(node_end);
  }

  private:

  node_ptr construct_node(const Val& value, node_ptr node_end) {
    node_ptr new_node = node_alloc.allocate(1);
    node_alloc.construct(new_node, node_type(value, node_end));
    return new_node;
  }

  void destroy_node(node_ptr node) {
    node_alloc.destroy(node);
    node_alloc.deallocate(node, 1);
  }

  /* 
   * this destructor had to be, lets say, inspired from STL
   * because the double recursive one made the stack explode
   * for large trees.
   * ulimit -a : shows system limits for a variety of `kernel shit`
   * ulimits -s ; the one we are interested in.
   */
  void delete_subtree(node_ptr node) {
    while (node != node_end) {
      delete_subtree(node->right);
      node_ptr save = node->left;
      destroy_node(node);
      node = save;
    }
  }

  /* 
   * Rotation helper, does:
   * 
   * if new_child_parent_o == right_child
   * 
   *      X                  X
   *      |                 |
   *      p                 n
   *    /        === >       \
   *   n                      p
   * 
   * else
   *  
   *     X                  X
   *     |                  |
   *     p                  n
   *      \      === >    /
   *       n            p
   */
  inline void switch_with_parent(node_ptr n, node_ptr parent) {
    if (parent == _root) {
      _root = n;  
    } else if (parent->is_left_child()) {
      parent->parent->assign_left_child(n);
    } else if (parent->is_right_child()) {
      parent->parent->assign_right_child(n);
    }
    n->assign_parent(parent->parent);
    parent->assign_parent(n);
  }

  /* 
   *        Parent                    Parent
   *          |                         |
   *         to                       from
   *     /       \       ===>      /        \
   *    A       from             to         fR
   *  /   \     /  \           /   \
   * AL   AR   fL  fR         A    fL
   *                        /  \
   *                      AL   AR
   */
  void rotate_left(node_ptr from) {

    node_ptr to = from->parent;

    switch_with_parent(from, to);

    to->assign_right_child(from->left);
    from->assign_left_child(to);
    if (to->right != node_end) {
      to->right->assign_parent(to);
    }
  }

  /* 
   *        Parent                    Parent
   *          |                         |
   *         to                       from
   *     /       \       ===>      /        \
   *   from       A              fL         to
   *  /   \     /  \                      /    \
   * fL   fR   AL  AR                   fR      A
   *                                          /   \
   *                                         AL   AR
   */
  void rotate_right(node_ptr from) {
    
    node_ptr to = from->parent;
    
    switch_with_parent(from, to);

    to->assign_left_child(from->right);
    from->assign_right_child(to);
    if (to->left != node_end) {
      to->left->assign_parent(from->right);
    }
  }

  inline void rotate(node_ptr n) {
    return n->is_left_child() ? rotate_right(n) : rotate_left(n);
  }

  void rebalance_after_insertion(node_ptr n) {

    while (n != _root
           && n->parent->color == red)
    {
      node_ptr u = n->uncle();
      if (u->color == red) {
        u->color = black;
        n->parent->color = black;
        u->parent->color = red;
        n = u->parent;
      } else {
        node_ptr p = n->parent;
        if (key_cmp(key_of_val(n->data), key_of_val(p->data))
            != key_cmp(key_of_val(p->data), key_of_val(p->parent->data)))
        {
          rotate(n); // this case ALWAYS ...
          n = p;
        }
        n->parent->color = black;
        n->parent->parent->color = red;
        rotate(n->parent); // ... ends up here.
        // 
        // PS: notice how rotating from n->parent before coloring
        // n->parent->color to black WILL get out of the loop
      }
    }
    _root->color = black; // RBT rule
  }

  node_ptr find_and_insert(node_ptr new_node, node_ptr init) {
  
    if (node_count == 0) {
      new_node->assign_parent(node_end);
      _root = new_node;
      ++node_count;
      return new_node;
    }

    node_ptr parent = (init != _root) ? init->parent : NULL;
    node_ptr start = init;
    bool at_right = false;

    // Iterate until we get to a leaf
    Key key = key_of_val(new_node->data);
    while (start != node_end) {
      parent = start;
      if (key_cmp(key, key_of_val(start->data))) {
        start = start->left;
        at_right = false;
      } else {
        // if duplicate, return already existing node
        if (key == key_of_val(start->data)) {
          return start;
        }
        start = start->right;
        at_right = true;
      }
    }
    // once start == node_end, insert after parent
    new_node->assign_parent(parent);
    if (at_right) {
      parent->assign_right_child(new_node);
    } else {
      parent->assign_left_child(new_node);
    }
    ++node_count;
    return new_node;
  }

  /*
   * Hints are cool, but bad hints must be avoided. 
   * If we are inserting at n, go check parent of n.
   * If n is left child, check if value < n->parent.
   * If n is right child, check if vlaue > n->parent.
   * In none of these conditions are met, the hint is
   * malicious and must be disregarded. 
   */
  bool check_insert_hint(const iterator hint, const Val& value) {

    node_ptr n = hint.base();
    
    if (n == _root) { // nice hint dumbass
      return false;
    }
    if (n->is_left_child()) { // n < parent
      if (key_of_val(value) > key_of_val(n->parent->data)) {
        return false;
      }
    } else { // n > parent
      if (key_of_val(value) < key_of_val(n->parent->data)) {
        return false;
      }
    }
    return true;
  }

 /*
  * Searched n's inorder predecessor and switches node entries.
  * 
  *            A                        A
  *            |                        |
  *            n                        r
  *          /  \                     /  \
  *         X   B       ===>         X    B
  *                   
  *        C                        C
  *        |                        |
  *        r                       n
  *      /                        /
  *     D                       D
  * 
  * - parent is GUARANTEED to have two childs.
  * - inorder predecessor has at most 1 left child
  * - inorder predecessor can be n's left child.
  */
  void switch_with_inorder_predecessor(node_ptr n) {
    
    node_ptr r = n->left;

    while (r->right != node_end) {
      r = r->right;
    }
    // B
    r->assign_right_child(n->right);
    n->right->assign_parent(r);
    if (r != n->left) {
      node_ptr tmp = n->left;
      // D
      n->assign_left_child(r->left);
      if (r->left != node_end) {
        r->left->assign_parent(n->left);
      }
      // X
      r->assign_left_child(tmp);
      tmp->assign_parent(r);

      tmp = r->parent;
      // A
      r->assign_parent(n->parent);
      if (n->is_left_child()) {
        n->parent->assign_left_child(r);
      } else if (n->is_right_child()) {
        n->parent->assign_right_child(r);
      } else {
        _root = r;
      }
      // C
      n->assign_parent(tmp);
      tmp->assign_right_child(n);
    } else {
      // no C or X in this case.
      // D
      n->assign_left_child(r->left);
      if (r->left != node_end) {
        r->left->assign_parent(n);
      }
      // A
      r->assign_parent(n->parent);
      if (n->is_left_child()) {
        n->parent->assign_left_child(r);
      } else if (n->is_right_child()) {
        n->parent->assign_right_child(r);
      } else {
        _root = r;
      }
      // n
      n->assign_parent(r);
      r->assign_left_child(n);
    }
    n->assign_right_child(node_end);
    // finally, change color
    n_color tmp_color = n->color;
    n->color = r->color;
    r->color = tmp_color;
  }

  public:

  node_ptr get_maximum() {
    if (_root == node_end) {
      return node_end;
    }
    node_ptr aux = _root;
    while (aux->right != node_end) {
    /*
    std::cout << "aux(" << iterator(aux)->first
              << "), aux->right(" << iterator(aux->right)->first
              << "), node_end(" << iterator(node_end)->first << ") : "
              << aux
              << ", " << aux->right
              << ", " << node_end
              << std::endl;
    */
      aux = aux->right;
    }
    return aux;
  }

  node_ptr get_minimum() {
    if (_root == node_end) {
      return node_end;
    }
    node_ptr aux = _root;
    while (aux->left != node_end) {
    /*
    std::cout << "aux(" << iterator(aux)->first
              << "), aux->left(" << iterator(aux->left)->first
              << "), node_end(" << iterator(node_end)->first << ") : "
              << aux
              << ", " << aux->left
              << ", " << node_end
              << std::endl;
    */
      aux = aux->left;
    }
    return aux;
  }

  iterator begin() {
    return iterator(get_minimum(), node_end);
  }

  const_iterator begin() const {
    return const_iterator(get_minimum(), node_end);
  }

  iterator end() {
    return iterator(node_end, node_end);
  }

  const_iterator end() const {
    return const_iterator(node_end, node_end);
  }

  bool insert(const Val& value) {

    node_ptr n = construct_node(value, node_end);
    node_ptr m = NULL;
    
    if ((m = find_and_insert(n, _root)) != n) {
      destroy_node(n);
      // return ft::pair<false, iterator(m); 
      return false;
    }
    rebalance_after_insertion(n);
    // return ft::pair<true, iterator(n)>
    return true;
  }

  bool insert_with_hint(const iterator hint, const Val& value) {

    node_ptr n = construct_node(value, node_end);
    node_ptr m = NULL;

    bool good_hint = check_insert_hint(hint, value);
    if (good_hint) {
      m = find_and_insert(n, hint.base());
    } else {
      m = find_and_insert(n, _root);
    }
    if (m != n) {
      destroy_node(n);
      // return ft::pair<false, iterator(m);
      return false;
    }
    rebalance_after_insertion(n);
    // return ft::pair<true, iterator(n)>;
    return true;
  }

  /* 
   * Edit: this needs to be reviewed. There are inconsistencies.
   *      The video I watched explaining this includes pseudocode that
   *      the explanation skips. Quite some important parts. Fuck
   * 
   * DOUBLE_BLACK vocabulary :
   *          
   *          z        p : Double black node
   *        /  \       y : sibling
   *      y     p      z : common parent
   *    /  \           x : sibling child (in the same orientation as y)
   *   xL  xR 
   * 
   * DB cases:
   * 
   * Case 1: y is BLACK and a sibling x of y is RED.
   *        Case 1.1 : x y z form a line. 
   *                   - rotate y -> z.
   *        Case 2.2 : x y z do not form a line.
   *                   - rotate x -> y, then rotate x -> z.
   *        The end structure is, not including symmetric cases :
   *     1.1                     1.2 
   * b -          y                       xR
   *            /  \                    /   \
   * a -      xL    z                  y     z
   * 
   * Note : line a will always be black, and line b will remain the same
   *         color as it was (z's color).
   * 
   * Case 2: y is BLACK (or does not exist) and has BLACK children
   *        - color p BLACK and y RED.
   *        - if z is RED, color it BLACK.
   *        - else if z is not the root, z is new double BLACK.
   * Case 3: y is RED
   *        - rotate y -> z 
   *        - color y BLACK and z RED.
   *        - repeat double black solve (p stays at same position,
   *          derives to case 1 or 2).
   * 
   * Double black acts as a theoretical node, it does not exist
   * as its been deleted. We will work with its family members, not
   * the double black node directly.
   */
  void solve_double_black(node_ptr db_parent, node_ptr db_sibling,
                          bool at_right)
  {
    while (db_parent != node_end) {

    }
  }

  node_ptr find_and_erase(const Key& key) {

    node_ptr start = _root;

    // same iteration as insert with other intentions.
    while (start != node_end) {
      if (key_cmp(key, key_of_val(start->data))) {
        start = start->left;
      } else {
        if (key == key_of_val(start->data)) {
          break;
        }
        start = start->right;
      }
    }
    // if we iterated until a leaf, rip.
    if (start == node_end) {
      return NULL;
    }


    if (start->left != node_end
        && start->right != node_end)
    {
      switch_with_inorder_predecessor(start);
    }

/*
 * Here, start is to be deleted and can only have 0 or 1 child.
 * If 0 childs :
 *  - If start is red, delete. Done.
 *  - If start is black, solve double black on start.
 * If 1 child :
 *  - If start or child is red, delete, subsitute, successor node
 *    gets painted black.
 *  - If both are black, switch positions start <-> child, and 
 *    solve double black on start
 * 
 */
    if (start->right == start->left) {
      if (start->color == black) {
        solve_double_black(start);
      }
    } else if (start->right == node_end) { // left child E
      // switch start <--> start->left
      start->left->assign_parent(start->parent);
      if (start->parent != node_end) {
        start->parent->assign_left_child(start->left);
      } else {
        _root = start->left;
      }
      // make start start->left's left child in
      // case double black needs to be solved
      if (start->color == black
          && start->left->color == black)
      {
        start->assign_parent(start->left);
        start->assign_left_child(node_end);
        start->left->assign_left_child(start);
        solve_double_black(start);
      } else {
        start->left->color = black;
      }
    } else { // right child E
      // switch start <--> start->right
      start->right->assign_parent(start->parent);
      if (start->parent != node_end) {
        start->parent->assign_right_child(start->right);
      } else {
        _root = start->right;
      }
      // make start start->right's right child in case
      // double black needs to be solved
      if (start->color == black
          && start->right->color == black)
      {
        start->assign_parent(start->right);
        start->assign_right_child(node_end);
        start->right->assign_right_child(start);
        solve_double_black(start);
      // else, the node remaining must be black, not caring 
      } else {
        start->right->color = black;
      }
    }
    destroy_node(start);
    --node_count;
  }

  void erase(const Key& key) {
    find_and_erase(key);
  }

}; // class rbtree

} // namespace
#endif