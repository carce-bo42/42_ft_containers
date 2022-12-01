#ifndef FT_CONTAINERS_RED_BLACK_TREE_HPP
# define FT_CONTAINERS_RED_BLACK_TREE_HPP
#pragma once

#include <memory>
#include <functional>
#include "ft/utils/pair.hpp"
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"
#include "ft/RBT/reb_black_tree_reverse_iterator.hpp"

namespace ft {

// KeyOfVal functor for map
template < typename Key,
           typename Val /* = ft::pair<Key, typename T> */ >
struct map_get_key {
  const Key operator()(const Val& value) const {
    return value.first;
  }
};

// KeyOfVal functor for set
template < typename Key >
struct set_get_key {
  const Key operator()(const Key& value) const {
    return value;
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
 * Red black trees must hold :
 * (0) Nodes are either RED or BLACK (surprise)
 * (1) Root and nil leaves are BLACK.
 * (2) If a node is RED, its children are BLACK.
 * (3) All paths from a node (not counting the starting
 *     one) to its nil descendants contain the same number
 *     of black nodes.
 */
template < typename Key, // Unique for Map and Set. Allows ordering
           typename Val, // Some Type that contains Key
           typename KeyOfVal, // Functor that extracts a Key
                              // from some arbitrary Val
           typename Compare = std::less<Key>,
           typename Allocator = std::allocator<Val> >
class rb_tree {

  public:

  typedef rb_tree_node<Val>                           node_type;
  typedef rb_tree_node<const Val>                     const_node_type;
  typedef typename node_type::n_color                 n_color;
  // get another allocator.
  typedef typename Allocator::
          template rebind<node_type>::other           node_allocator;
  typedef typename node_allocator::pointer            node_ptr;
  typedef typename node_allocator::const_pointer      const_node_ptr;

  typedef Key                                         key_type;
  typedef Val                                         value_type;
  typedef Compare                                     key_compare;
  typedef KeyOfVal                                    key_extractor;
  typedef size_t                                      size_type;
  typedef rb_tree_iterator<Val, node_ptr>             iterator;
  typedef rb_tree_iterator<const Val, const_node_ptr> const_iterator;
  typedef rb_tree_reverse_iterator<iterator>          reverse_iterator;
  typedef rb_tree_reverse_iterator<const_iterator>    const_reverse_iterator;

  private:

  node_ptr       _root;
  node_ptr       node_end; // node end is my STL's header node
                           // If the tree is empty, is equal to root.
                           // It is always black and its parent is always itself. 
                           // max/min correspond to its right/left child,
                           // or NULL if the tree is empty (see init_tree)
  size_type      node_count;
  node_allocator node_alloc;

  public:

  key_compare    key_cmp;
  key_extractor  key_of_val;

  rb_tree()
  :
    _root(0),
    node_count(0),
    node_alloc()
  {
    init_tree();
  }

  rb_tree( const rb_tree& other )
  :
    _root(0),
    node_count(0),
    node_alloc(other.node_alloc)
  {
    init_tree();
    for (rb_tree::const_iterator it = other.begin(); it != other.end(); it++) {
      insert(*it);
    }
  }

  rb_tree( const Compare& comp )
  :
    _root(0),
    node_count(0),
    node_alloc(),
    key_cmp(comp)
  {
    init_tree();
  }

  ~rb_tree() {
    delete_subtree(_root);
    destroy_node(node_end);
  }

  node_ptr get_node_end() const {
    return node_end;
  }

  node_ptr get_root() const {
    return _root;
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
      --node_count;
      node = save;
    }
  }

  private:

  // Node end acts as nil. Starts being root
  void init_tree() {
    node_end = construct_node(Val(), 0);
    node_end->assign_parent(node_end);
    node_end->assign_left_child(0);
    node_end->assign_right_child(0);
    node_end->color = black;
    _root = node_end;
  }

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

  /*
   * This followed the source : 
   * https://tildesites.bowdoin.edu/~ltoma/teaching/cs231/fall16/Lectures/05-BST/rbtrees.pdf
   */
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
      node_end->assign_right_child(new_node);
      node_end->assign_left_child(new_node);
      _root = new_node;
      ++node_count;
      return new_node;
    }

    node_ptr parent = (init != _root) ? init->parent : node_end;
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
      if (parent == get_maximum()) {
        node_end->assign_right_child(new_node);
      }
      parent->assign_right_child(new_node);
    } else {
      if (parent == get_minimum()) {
        node_end->assign_left_child(new_node);
      }
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
  bool check_hint(node_ptr hint, const Val& value) {

    if (hint == _root) { // nice hint dumbass
      return false;
    }
    if (hint->is_left_child()) { // hint < parent
      if (key_of_val(value) >= key_of_val(hint->parent->data)) {
        return false;
      }
    } else { // hint > parent
      if (key_of_val(value) < key_of_val(hint->parent->data)) {
        return false;
      }
    }
    return true;
  }

  /*
   * To swap values, since val = pair <const Key, Val>, it is not doable
   * with some swap method. The value data iside the node pointer must be
   * destructed, and reconstructed.
   * mantaining allocated space is crucial. So we clone,
   * destroy, then construct as we please, without calling deallocate
   */
  void swap_node_values(node_ptr n1, node_ptr n2) {
    node_type n1_tmp_clone(*n1); // cannot use assignment because of const Key
    node_type n2_tmp_clone(*n2);
    node_alloc.destroy(n1);
    node_alloc.destroy(n2);
    node_alloc.construct(n1, node_type(n2_tmp_clone.data,
                                       n1_tmp_clone.parent,
                                       n1_tmp_clone.left,
                                       n1_tmp_clone.right,
                                       n1_tmp_clone.color));
    node_alloc.construct(n2, node_type(n1_tmp_clone.data,
                                       n2_tmp_clone.parent,
                                       n2_tmp_clone.left,
                                       n2_tmp_clone.right,
                                       n2_tmp_clone.color));
  }

  node_ptr switch_with_inorder_predecessor(node_ptr n) {

    node_ptr r = n->left;
    
    while (r->right != node_end) {
      r = r->right;
    }
    swap_node_values(r, n);
    return r;
  }

  /* 
   * This is a mix between the theory from GeeksForGeeks, the following
   * link :
   * https://www.codesdope.com/course/data-structures-red-black-trees-deletion/
   * and my own reasoning (NOT ONE SINGLE site mentions case parent is red).
   * 
   * Double black acts as a theoretical node, since only its
   * parent, sibling and sibling's childs are relevant.
   * db_at_right indicates wether double black is at right or not of
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
  void solve_double_black(node_ptr db_parent, bool db_at_right) {

    while (db_parent != node_end) { // equivalent to double black != root
      node_ptr s = db_at_right ? db_parent->left : db_parent->right;
      if (s->color == black) {
        /*
         * If s is black and has no red childs, they MUST be nil,
         * otherwise theres a black depth violation on sibling side:
         * db side has n + 2 (db) black depth,
         * sibling would have n + 1(s black)
         *                      + 1(black child)
         *                      + k(nil leaves at least) black depth. 
         * 
         * [1.1]
         *     aR                  aB       
         *    /  \   col a<->b   /   \
         *  BB   bB     ==>    nil   bR           OK
         *      /  \                /  \
         *    nil  nil            nil  nil
         * 
         * [1.2]
         *     aB                    aB -> new BB 
         *    /  \   col b red     /   \
         *  BB   bB      ==>     nil   bR           CONTINUE 
         *      /  \                  /  \
         *    nil  nil              nil  nil   
         */
        if (s->right->color == black
            && s->left->color == black)
        {
          s->color = red;
          if (db_parent->color == red) {
            db_parent->color = black;
          } else {
            db_at_right = db_parent->is_right_child() ? true : false;
            db_parent = db_parent->parent;
            continue;
          }
        }
        /*
         * if s is black and has at least one red child :
         * - After rotating, db_parent should have its sibling
         *   the same color as him :
         * 
         * [2.1]
         *    aB/R    rot b->a         bB  
         *    /  \   col c as a      /   \          OK
         *  BB   bB     ==>       aB/R   cB/R
         *      /  \
         *    nil  cR
         * 
         * [2.2]
         *    aB/R    rot b->a         bB       if a == R        bR
         *    /  \   col c as a      /   \      a,c -> black    /  \
         *  BB   bB     ==>       aB/R   cB/R    b -> red     aB   cB    OK
         *      /  \                 \                         \ 
         *     dR  cR                dR                        dR
         *   
         * [2.3]
         *    aB/R    rot c->b      aB/R    rot c->a       cB  
         *    /  \   col c black   /   \   col b as a    /   \
         *  BB   bB     ==>      BB    cB     ==>      aB/R   bB/R    OK
         *      /  \                    \
         *     cR  nil                  bB
         */
        else if (db_at_right) {
          if (s->left->color == red) {
            s->left->color = db_parent->color;
            rotate_right(s);
            if (s->right->color == red
                && s->right->left->color == red)
            {
              s->left->color = black;
              s->right->color = black;
              s->color = red;
            }
          } else { // s->right->color == red
            s->right->color = black;
            s->color = db_parent->color;
            rotate_left(s->right);
            rotate_right(s->parent);
          }
        } else { // db at left
          if (s->right->color == red) {
            s->right->color = db_parent->color;
            rotate_left(s);
            if (s->left->color == red
                && s->left->right->color == red)
            {
              s->left->color = black;
              s->right->color = black;
              s->color = red;
            }
          } else {
            s->left->color = black; 
            s->color = db_parent->color;
            rotate_right(s->left);
            rotate_left(s->parent);
          }
        }
        break;
      } else {
        /* 
         * If s is red, parent is black and both of sibling's
         * childs MUST exist and be black.
         * Else, black depth is violated on sibling's side. 
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
        if (db_at_right) {
          rotate_right(s);
          db_parent = s->right;
        } else {
          rotate_left(s);
          db_parent = s->left;
        }
      }
    } // while db not root or db not solved.
  }

  node_ptr erase(node_ptr n) {

    bool update_min = n == node_end->left;
    bool update_max = n == node_end->right;

    // deleting the only node
    if (n == _root && node_count == 1) {
      destroy_node(n);
      --node_count;
      node_end->assign_left_child(0);
      node_end->assign_right_child(0);
      _root = node_end;
      return node_end;
    }

    if (n->left != node_end
        && n->right != node_end)
    {
      n = switch_with_inorder_predecessor(n);
    }
   /*
    * Here, n is to be deleted and can only have 0 or 1 child.
    *  - Notice how theres only 3 possible constructions (taking out
    *    symmetric cases) for a node to have 0 or1 child. Any other 
    *    disposition violates black depth. 
    *     B/R          B          B
    *    /  \        /  \       /  \ 
    *  nil  nil     R   nil   nil   R
    * - one of them leads to double black, the others are instantly
    *   solved by just promoting the child.
    */
    if (n->right == n->left) {
      if (n == _root) {
        _root = node_end;
      } else {
        bool db_at_right;
        if (n->is_left_child()) {
          n->parent->assign_left_child(node_end);
          db_at_right = false;
        } else {
          n->parent->assign_right_child(node_end);
          db_at_right = true;
        }
        if (n->color == black) {
          solve_double_black(n->parent, db_at_right);
        }
      }
    // left child red => switch n <--> n->left
    } else {
      node_ptr substitute = n->right == node_end
                            ? n->left
                            : n->right;
      substitute->color = black;
      substitute->assign_parent(n->parent);
      if (n->parent != node_end) {
        if (n->is_left_child()) {
          n->parent->assign_left_child(substitute);
        } else {
          n->parent->assign_right_child(substitute);
        }
      } else {
        _root = substitute;
      }
    }
    /*
     * Update min/max node (for iterators). Note that at this point
     * n is not reachable from the tree, so get_minimum/maximum() gives
     * the new minimum/maximum.
     */
    if (update_min) {
      node_end->assign_left_child(get_minimum());
    }
    if (update_max) {
      node_end->assign_right_child(get_maximum());
    }
    destroy_node(n);
    --node_count;
    return node_end;
  }

  public:

  // allocator and key_cmp are dumb to swap, since 
  // the other tree has the same types as this one.
  void swap(rb_tree& other) {
    ft::swap(_root, other._root);
    ft::swap(node_end, other.node_end);
    ft::swap(node_count, other.node_count);
  }

  void clear() {
    delete_subtree(_root);
    destroy_node(node_end);
    init_tree();
  }

  size_type max_size() const {
    return node_alloc.max_size();
  }

  /*
   * Returns an iterator pointing to the first element that is not
   * less than (i.e. greater or equal to) key.
   */
  iterator lower_bound(const Key& key) {
    iterator it = iterator(get_minimum(), node_end);
    while (it.base() != node_end) {
      if (key_cmp(key_of_val(*it), key)) {
        ++it;
      } else { // not less than key 
        break;
      }
    }
    return it;
  }

  const_iterator lower_bound(const Key& key) const {
    const_iterator it = const_iterator(get_minimum(), node_end);
    while (it.base() != node_end) {
      if (key_cmp(key_of_val(*it), key)) {
        ++it;
      } else { // not less than key 
        break;
      }
    }
    return it;
  }

  /*
   * Returns an iterator pointing to the first element that is
   * greater than key.
   */
  iterator upper_bound(const Key& key) {
    iterator it = iterator(get_minimum(), node_end);
    while (it.base() != node_end) {
      if (key_cmp(key_of_val(*it), key)
          || key_of_val(*it) == key)
      {
        ++it;
      } else { // not less than key or equal
        break;
      }
    }
    return it;
  }

  const_iterator upper_bound(const Key& key) const {
    const_iterator it = const_iterator(get_minimum(), node_end);
    while (it.base() != node_end) {
      if (key_cmp(key_of_val(*it), key)
          || key_of_val(*it) == key)
      {
        ++it;
      } else { // not less than key or equal
        break;
      }
    }
    return it;
  }

  node_ptr get_maximum() {
    node_ptr p = _root;
    while (p->right && p->right != node_end) {
      p = p->right;
    }
    return p;
  }

  const_node_ptr get_maximum() const {
    const_node_ptr p = _root;
    while (p->right && p->right != node_end) {
      p = p->right;
    }
    return p;
  }

  node_ptr get_minimum() {
    node_ptr p = _root;
    while (p->left && p->left != node_end) {
      p = p->left;
    }
    return p;
  }

  const_node_ptr get_minimum() const {
    const_node_ptr p = _root;
    while (p->left && p->left != node_end) {
      p = p->left;
    }
    return p;
  }

  inline iterator begin() {
    return iterator(get_minimum(), node_end);
  }

  inline const_iterator begin() const {
    return const_iterator(get_minimum(), node_end);
  }

  inline reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  inline const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  inline iterator end() {
    return iterator(node_end, node_end);
  }

  inline const_iterator end() const {
    return const_iterator(node_end, node_end);
  }

  inline reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  inline const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  inline bool empty() const {
    return node_count == 0;
  }

  inline size_type size() const {
    return node_count;
  }

  ft::pair<iterator, bool> insert(const Val& value) {

    node_ptr n = construct_node(value, node_end);
    node_ptr m = NULL;
    
    if ((m = find_and_insert(n, _root)) != n) {
      destroy_node(n);
      return ft::pair<iterator, bool>(iterator(m, node_end), false); 
    }
    rebalance_after_insertion(n);
    return ft::pair<iterator, bool>(iterator(n, node_end), true);
  }

  iterator insert_with_hint( iterator hint, const Val& value)
  {
    node_ptr n = construct_node(value, node_end);
    node_ptr m = NULL;

    if (hint == end()) {
      m = find_and_insert(n, _root);
    } else {
      bool good_hint = check_hint(hint.base(), value);
      if (good_hint) {
        m = find_and_insert(n, hint.base());
      } else {
        m = find_and_insert(n, _root);
      }
    }
    if (m != n) {
      destroy_node(n);
      return iterator(m, node_end);
    }
    rebalance_after_insertion(n);
    return iterator(n, node_end);
  }

  /* Insert with hint for set. Problem is, set has no knowledge whatsoever
   * of what an rb_tree::iterator is, so either this is done, or
   * theres some other bridge function that connects const_iterator
   * with the one with iterator.
   */
  const_iterator insert_with_hint( const_iterator hint, const Val& value)
  {
    node_ptr n = construct_node(value, node_end);
    node_ptr m = NULL;

    if (hint == end()) {
      m = find_and_insert(n, _root);
    } else {
      bool good_hint = check_hint(const_cast<node_ptr>(hint.base()), value);
      if (good_hint) {
        m = find_and_insert(n, const_cast<node_ptr>(hint.base()));
      } else {
        m = find_and_insert(n, _root);
      }
    }
    if (m != n) {
      destroy_node(n);
      return const_iterator(m, node_end);
    }
    rebalance_after_insertion(n);
    return const_iterator(n, node_end);
  }

  node_ptr find(const Key& key) const {

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
    return start;
  }

  bool erase(const Key& key) {
    node_ptr n = find(key);
    if (n) {
      erase(n);
      return true;
    }
    return false;
  }

}; // class rbtree

} // namespace

#endif /* FT_CONTAINERS_RED_BLACK_TREE_HPP */