#include <stdlib.h>

/* Node: represents the nodes of a Huffman tree

   A node will only have a char 'c' associated
   with it if it has neither a left nor a right
   subtree, i.e. the node is a leaf node.
					     */

struct Node {
	// count (int): the number of times that every character in the
	// subtree at this node's root occur in the program
	int count;

	// left (Node): the left subnode of this Node, if it exists
	struct Node * left;

	// right (Node): same as above but the right subnode, if it exists
	struct Node * right;

	// c (char): the character of this Node, if it exists
	char c;
};


