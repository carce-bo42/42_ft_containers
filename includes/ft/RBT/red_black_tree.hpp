#ifndef CONTAINERS_RED_BLACK_TREE_HPP
# define CONTAINERS_RED_BLACK_TREE_HPP

#include <memory>
#include <functional>
#include "ft/RBT/red_black_tree_node.hpp"
#include "ft/RBT/red_black_tree_iterator.hpp"

namespace ft {

// KeyOfVal functor for rb_tree
template < typename Key,
           typename Val /* = ft::pair<Key, typename T> */ >
struct get_key {

  typedef ft::rb_tree_node<Val> node_type;

  Key operator()(const node_type* node) {
    return node->data.first;
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
  typedef Val                              value_type;
  typedef value_type*                      pointer;
  typedef const value_type*                const_pointer;
  typedef value_type&                      reference;
  typedef const value_type&                const_reference;
  typedef size_t                           size_type;
  typedef ptrdiff_t                        difference_type;
  typedef Alloc                            allocator_type;
  typedef rb_tree_iterator<Val>            iterator;
  typedef rb_tree_iterator<const Val>      const_iterator;

  private:

  node_ptr       _root;
  // node end is the dummy node used for end() and rend().
  // it contains no parent, no childs, and is appended to
  // the right of the max and to the left of the min. If
  // the tree is empty, is equal to root.
  node_ptr       node_end;
  size_t         node_count;
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
    node_end = construct_node(Val());
    _root = node_end;
  }

  ~rb_tree() {
    delete_subtree(_root);
    destroy_node(node_end);
  }

  private:

  void delete_subtree(node_ptr node) {
    if (node) {
      delete_subtree(node->right);
      delete_subtree(node->left);
      if (node != node_end) {
        destroy_node(node);
      }
    }
  }

  void rotate(node_ptr n) {
    return n->is_left_child() ? rotate_right(n) : rotate_left(n);
  }

  void switch_colors(node_ptr x, node_ptr y) {
    n_color color_tmp = x->color;
    x->set_color(y->color);
    y->set_color(color_tmp);
  }

  /* 
   * Rotation helper, does:
   * 
   * if new_child_parent_o == right_child
   *      X                  X
   *      |                 |
   *      p                 n
   *    /        === >       \
   *   n                      p
   * else
   *     X                  X
   *     |                  |
   *     p                  n
   *      \      === >    /
   *       n            p
   */
  void switch_with_parent(node_ptr n, node_ptr parent)
  {
    if (parent->is_left_child()) {
      parent->parent->assign_left_child(n);
      n->assign_parent(parent->parent);
    } else if (parent->is_right_child()) {
      parent->parent->assign_right_child(n);
      n->assign_parent(parent->parent);
    } else {
      n->make_root(node_end);
      _root = n;
    }
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

    switch_colors(from, to);
    switch_with_parent(from, to);

    node_ptr tmp = from->left;
    from->assign_left_child(to);
    to->assign_right_child(tmp);
    if (tmp && tmp != node_end) {
      tmp->assign_parent(from->left);
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
    
    switch_colors(from, to);
    switch_with_parent(from, to);

    node_ptr tmp = from->right;
    from->assign_right_child(to);
    to->assign_left_child(tmp);
    if (tmp && tmp != node_end) {
      tmp->assign_parent(from->right);
    }
  }

  void rebalance_after_insertion(node_ptr n) {
    if (n == _root) {
      n->set_color(black);
    } else if (n->parent == _root || n->parent->color == black) {
      n->parent->set_color(black);
    // with the previous block we make sure there exists a grandparent
    } else {
      node_ptr uncle = n->uncle(); // grandparent's other child
      //std::cout << "uncle : " << uncle << " node end " << node_end << std::endl;
      if (uncle && uncle != node_end && uncle->color == red) {
        /*
        std::cout << "n(" << iterator(n)->first
                  << "), uncle(" << iterator(uncle)->first << ")";
        uncle->print_node_state();
        std::cout << std::endl;
        */
        uncle->set_color(black);
        n->parent->set_color(black);
        uncle->parent->set_color(red);
        return rebalance_after_insertion(uncle->parent);
      } else {
          if ((n->is_right_child() && n->parent->is_left_child())
              || (n->is_left_child() && n->parent->is_right_child()))
          {
            /*
            std::cout << "n->orientation() " << n->orientation()
                      << " n->parent->orientation() : " << n->parent->orientation()
                      << std::endl;
            std::cout << "root : " << _root
                      << " n->parent : " << n->parent << std::endl;
            */
            node_ptr ex_parent = n->parent;
            rotate(n);
            /*
            if (n->is_right_child()) {
              std::cout << "about to rotate left n : " << std::endl;
              n->print_node_state();
              rotate_left(n);
            } else {
              rotate_right(n);
            }*/
            return rebalance_after_insertion(ex_parent);
          }
          // (n->orientation == n->parent->orientation) == true
          /*
          if (n->is_left_child()) {
            rotate_right(n->parent);
          } else {
            .rotate_left(n->parent);
          }
          */
         rotate(n->parent);
      }
    }
  }

  void transplant(node_ptr x, node_ptr y) {
    if (x == _root) {
      _root = y;
    } else if (x->is_left_child()) {

    }
  }

  public:

  node_ptr construct_node(const Val& value) {
    node_ptr new_node = node_alloc.allocate(1);
    node_alloc.construct(new_node, node_type(value));
    return new_node;
  }

  /*
   * This is a dangerous method to be public. These innocent lines will produce
   * a use after free error when the tree destructor is called :
   * n = construct_node(...)
   * tree.pure_insert(n);
   * destroy_node(n);
   */
  void destroy_node(node_ptr node) {
    node_alloc.destroy(node);
    node_alloc.deallocate(node, 1);
  }

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
    return iterator(get_minimum());
  }

  const_iterator begin() const {
    return const_iterator(get_minimum());
  }

  iterator end() {
    return iterator(node_end);
  }

  const_iterator end() const {
    return const_iterator(node_end);
  }

  bool find_and_insert(node_ptr new_node,
                       node_ptr parent,
                       node_ptr start,
                       bool at_right)
  {
    /*  
     * Theres 3 cases where we can insert on an end. 
     * - If we are inserting at right of parent (we are new max)
     * - If we are inserting at left of parent (we are new min)
     * - If we are inserting and parent does not exist. (first node)
     */
    if (!start || start == node_end) {
      if (node_count == 0) {
        new_node->assign_right_child(node_end);
        new_node->assign_left_child(node_end);
        new_node->make_root(node_end);
        _root = new_node;
      } else {
        new_node->assign_parent(parent);
        if (at_right) {
          parent->assign_right_child(new_node);
          if (start == node_end) {
            new_node->assign_right_child(node_end);
          }
        } else {
          parent->assign_left_child(new_node);
          if (start == node_end) {
            new_node->assign_left_child(node_end);
          }
        }
      }
      ++node_count;
      return true;
    }
    // regular insertion
    /*
    if (!start) {
      if (new_orientation == right_child) {
        new_node->assign_parent(parent, right_child);
        parent->assign_right_child(new_node);
      } else {
        new_node->assign_parent(parent, left_child);
        parent->assign_left_child(new_node);
      }
      ++node_count;
      return true;
    }
    */
    /*
    std::cout << "key_of_val(new_node) = " << key_of_val(new_node) << std::endl;
    std::cout << "key_of_val(start) = " << key_of_val(start) << std::endl;
    std::cout << "key_cmp(key_of_val(new_node), key_of_val(start)) = "
              << key_cmp(key_of_val(new_node), key_of_val(start)) << std::endl;
    */
    // seek new path
    if (key_cmp(key_of_val(new_node), key_of_val(start))) {
      return find_and_insert(new_node, start, start->left, false);
    } else if (key_of_val(start) == key_of_val(new_node)) {
      return false;
    } else {
      return find_and_insert(new_node, start, start->right, true);
    }
  }

  bool insert(const Val& value) {
    node_ptr n = construct_node(value);
    // ToDo control return value (duplicates)
    if (!find_and_insert(n, _root, _root, false)) {
      destroy_node(n);
      return false;
    }
    rebalance_after_insertion(n);
    return true;
  }

}; // class rbtree

} // namespace
#endif