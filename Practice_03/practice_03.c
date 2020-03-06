/*
* ABL-tree building
* 1. Procedure for buid ABL-tree
* 2. Calculate average height, cases: n=10, 50, 100, 200, 400 (how many nodes)
* 3. Fill the table according (2) and for theorethical prognosis
* 4. Do the experiment to calculate middle of turns for one included node.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct ABL_tree_vertex {
	ABL_tree_vertex *right;
	ABL_tree_vertex *left;
	char balance;
	int key;
} ABL_tree_vertex;

int main(void) {
	return 0;
}