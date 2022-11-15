RED BLACK TREE REFERENCES

About trees :
1.1. https://stackoverflow.com/questions/205945/why-does-the-c-stl-not-provide-any-tree-containers

About RB trees :

2.1 https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
2.2 https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
2.3 https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/

A great series of videos on RB trees:
2.4 https://www.youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin

a true explanation :
2.7 https://cs.kangwon.ac.kr/~leeck/file_processing/red_black_tree.pdf

Original paper :
https://docs.lib.purdue.edu/cgi/viewcontent.cgi?article=1457&context=cstech

Demonstration of search Worst-Case time complexity:
https://www.youtube.com/watch?v=aRkE7DmVbCE

Some algorithm details (mentions cases where parent is red and
uncle does not exist/is root).
https://tildesites.bowdoin.edu/~ltoma/teaching/cs231/fall16/Lectures/05-BST/rbtrees.pdf

What should an rbtree of 4 nodes look like ?
https://stackoverflow.com/questions/66280563/what-should-a-4-node-red-black-tree-look-like

Functor less :

3.1 https://www.geeksforgeeks.org/functors-in-cpp/
3.2 https://en.cppreference.com/w/cpp/utility/functional/less


BEST LINK FOR INSERTION:
https://tildesites.bowdoin.edu/~ltoma/teaching/cs231/fall16/Lectures/05-BST/rbtrees.pdf

BEST LINK FOR DELETION:
https://www.youtube.com/watch?v=_c30ot0Kcis&t=275s


RED BLACK TREE RULES

 Red black trees must hold :

(0)   Nodes are either RED or BLACK (surprise)

(1)   Root and nil leaves are BLACK.

(2)   If a node is RED, its children are BLACK.

(3)   All paths from a node (not counting the starting

​       one) to its nil descendants contain the same number

​       of black nodes.


NOTES:

Why is default color in insertion RED ? 

If (1) holds, and insertion is always on nil nodes, inserting RED never violates (3). By inserting red the only initial
problem we deal with is (2). This is why, when inserting, we will always check if the parent is BLACK first, and when
it is, no violation happens.
