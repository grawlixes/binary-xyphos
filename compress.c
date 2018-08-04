#include <stdlib.h>
#include <stdio.h>

/* Node: represents the nodes of a Huffman tree

   A node will only have a char 'c' associated
   with it if it has neither a left nor a right
   subtree, i.e. the node is a leaf node.
					     */
struct Node;

// print_usage_string() (void): prints the correct way of calling the
// executable to stout
void print_usage_string();

int main(int argc, char * argv[]) {
	// read through the file to get the count of all numbers

	if (argc != 2) {
		printf("Incorrect number of arguments. See usage string:\n");
		print_usage_string();
	}

	

	return 0;
}

void print_usage_string() {
	printf("./binary_xyphos <input_file_name>\ninput_file_name should be the name of a text file.\n");
	exit(1);
}

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

