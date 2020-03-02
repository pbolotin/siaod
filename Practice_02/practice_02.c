/**************************************************************************
Topic: Random tree of search, ideal balance tree of search
***************************************************************************
Goal:  To know how to build these trees
***************************************************************************
1.  Create functions for building RTS and IBTS
***************************************************************************
2.  Calculate middle height of trees
    n = 10, 50, 100, 200, 400 (number of vertex in tree)
    Fill table:
    N  | Height RTS| Height IBTS
    ___|___________|____________
    10 |           |
    50 |           |
    100|           |
    200|           |
    400|           |
    Get analize of the results
***************************************************************************
3.  Create function for check if binary tree is tree of search?
    Check work of function on the builded RTS and IBTS
***************************************************************************
4.  Create function of search in the tree for element with the key, and
    check its work on builded RTS and IBTS.
***************************************************************************
5.  Find number of operations needed for search. Compare this number
    and height of tree.
***************************************************************************

/*struct, key for search
/ for all key are defined < > =
/ unique keys in tree
/ Binary tree is tree of search if left subtree has less keys,
/ right has more keys, than keys of the vertex
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Binary_tree_vertex {
    struct Binary_tree_vertex *pointer_to_the_left;
    struct Binary_tree_vertex *pointer_to_the_right;
    int random_number;
} Binary_tree_vertex;

typedef struct Sequence_of_unique_numbers {
	int *unique_number_array;
	int how_many;
} Sequence_of_unique_numbers;

int is_tree_of_search() {
    return 0;
}

void find_the_vertex_with_key() {
    return;
}

Sequence_of_unique_numbers* create_sequence_of_unique_numbers(int how_many) {
	Sequence_of_unique_numbers* seq = (Sequence_of_unique_numbers*)malloc(sizeof(Sequence_of_unique_numbers));
	seq->how_many = how_many;
	seq->unique_number_array = (int*)malloc(sizeof(int) * how_many);
	
	for(int i = 0; i < how_many; i++) {
		seq->unique_number_array[i] = i;
	}
	int buff;
	int pos;
	for(int i = 0; i < how_many; i++) {
		pos = i + rand()%(how_many - i);
		if(pos != i) {
			buff = seq->unique_number_array[i];
			seq->unique_number_array[i] = seq->unique_number_array[pos];
			seq->unique_number_array[pos] = buff;
		}
	}
	return seq;
}

int free_sequence_of_unique_numbers(Sequence_of_unique_numbers* seq) {
	free(seq->unique_number_array);
	free(seq);
	return 0;
}

int main() {
	srand(time(NULL));
	printf("Create sequence of unique numbers\n");
	
	Sequence_of_unique_numbers* seq = create_sequence_of_unique_numbers(10);
	for(int i = 0; i < seq->how_many; i++) {
		printf("%d ", seq->unique_number_array[i]);
	}

	free_sequence_of_unique_numbers(seq);
    return 0;
}