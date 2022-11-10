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
   * This is a mix between the theory from GeeksForGeeks, the following
   * link :
   * https://www.codesdope.com/course/data-structures-red-black-trees-deletion/
   * and my own reasoning (NOT ONE SINGLE site mentions case parent is red).
   * 
   * Double black acts as a theoretical node, since only its
   * parent, sibling and sibling's childs are relevant.
   * at_right indicates wether double black is at right or not of
   * parent.
   * Symmetric cases are obviated from grafs.
   * DOUBLE_BLACK vocabulary (for grafs) :
   *                  
   *                  B/R : black / red
   *          a       BB : Double black node
   *        /  \       a : db_parent
   *      BB    b      b : sibling
   *           / \    c,d : sibling's childs 
   *          c   d   
   * 
   * A double black problem is solved if, from the position
   * the db_parent was initially, the black depth is kept the same as it
   * was before deletion, without the need of a double black node.
   */
  void solve_double_black(node_ptr db_parent, bool at_right) {

    while (db_parent != node_end) { // equivalent to double black != root

      node_ptr s = at_right ? db_parent->left : db_parent->right;
      // if sibling does not exist, move double black to parent.
      if (s == node_end) { // can sibling not exist in a double black scenario ? It shouldnt
        db_parent = db_parent->db_parent;
        at_right = db_parent->is_right_child() ? true : false;
      } else {
        if (s->color == black) {
          /*
           * if s is black and has at least one red child :
           * - After rotating, db_parent should have its sibling
           *   the same color as him :
           *
           * [1.1]
           *    aB/R    rot b->a         bB  
           *    /  \   col c as a      /   \          OK
           *  BB   bB     ==>       aB/R   cB/R
           *      /  \
           *    nil  cR
           * 
           * [1.2]
           *    aB/R    rot c->b      aB/R    rot c->a       cB  
           *    /  \   col c black   /   \   col b as a    /   \
           *  BB   bB     ==>      BB    cB     ==>      aB/R   bB/R    OK
           *      /  \                    \
           *     cR  nil                  bB
           */
          if (s->right->color == red) {
            if (at_right) {
              s->right->color = db_parent->color;
              rotate_left(s);                        
            } else {
              s->right->color = black;
              s->color = db_parent->color;
              rotate_left(s->right);
              rotate_right(s->parent);
            }
            break;
          } else if (s->left->color == red) {
            if (at_right) {
              s->left->color = black;
              s->color = db_parent->color;
              rotate_right(s->left);
              rotate_left(s->parent);
            } else {
              s->left->color = db_parent->color;
              rotate_right(s);
            }
            break;
          /*
           * If s is black and has no red childs, they MUST be nil,
           * otherwise theres a black depth violation on sibling side:
           * db side has n + 2 (db) black depth,
           * sibling would have n + 1(s black)
           *                      + 1(black child)
           *                      + k(nil leaves at least) black depth. 
           * 
           * [2.1]
           *     aR                  aB       
           *    /  \   col a<->b   /   \
           *  BB   bB     ==>    nil   bR           OK
           *      /  \                /  \
           *    nil  nil            nil  nil
           * 
           * [2.2]
           *     aB                    aB -> new BB       
           *    /  \   col b red     /   \
           *  BB   bB      ==>     nil   bR           CONTINUE 
           *      /  \                  /  \
           *    nil  nil              nil  nil   
           */
          } else {
            s->color = red;
            if (db_parent->color == red) {
              db_parent->color = black;
              break;
            } else {
              db_parent = db_parent->parent;
              at_right = db_parent->is_right_child() ? true : false;
            }
          }
        } else {
          /* 
           * If s is red, parent is black and both of sibling's childs MUST exist and
           * be black. Else, black depth is violated on sibling's side. 
           *  
           * [3]
           *      aB    col a<->b       bB              bB
           *    /   \   rot b->a      /   \   [2.2]   /   \
           *   BB   bR     ==>      aR    dB   ==>   aB   dB     OK
           *       /  \            / \              /  \ 
           *      cB  dB         BB  cB           nil  cR
           */
          db_parent->color = red;
          s->color = black;
          if (at_right) {
            rotate_right(s);            
          } else {
            rotate_left(s);
          }
        }
      }

    } // while db not root or db not solved.
    node_end->color = black; // skips a lot of if's, when I know if a child exists it
                             // must be red i just paint it, if it was a nil node, this
                             // will put it back to normal.
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
    *    solve double black on start.
    */
    if (start->right == start->left) {
      if (start->color == black) {
        if (start == _root) {
          _root = node_end;
        } else {
          if (start->is_left_child()) {
            start->parent->assign_left_child(node_end);
            solve_double_black(start->parent, false);
          } else {
            start->parent->assign_right_child(node_end);
            solve_double_black(start->parent, true);
          }
        }
      }
    } else if (start->right == node_end) { // left child E
      // switch start <--> start->left
      start->left->assign_parent(start->parent);
      if (start->parent != node_end) {
        start->parent->assign_left_child(start->left);
      } else {
        _root = start->left;
      }
      if (start->color == black
          && start->left->color == black)
      {
        solve_double_black(start->left, false);
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
      if (start->color == black
          && start->right->color == black)
      {
        solve_double_black(start->right, true);
      // the node remaining must be black, not caring 
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