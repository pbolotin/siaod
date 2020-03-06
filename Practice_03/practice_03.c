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
	struct ABL_tree_vertex *right;
	struct ABL_tree_vertex *left;
	char balance;
	int key;
} ABL_tree_vertex;

typedef struct Sequence_of_unique_numbers {
	int *unique_number_array;
	int how_many;
} Sequence_of_unique_numbers;

Sequence_of_unique_numbers* create_sequence_of_unique_numbers(int how_many, char mode) {
	Sequence_of_unique_numbers* seq = (Sequence_of_unique_numbers*)malloc(sizeof(Sequence_of_unique_numbers));
	seq->how_many = how_many;
	seq->unique_number_array = (int*)malloc(sizeof(int) * how_many);
	
	for(int i = 0; i < how_many; i++) {
		seq->unique_number_array[i] = i;
	}
	if(mode == 'r') {
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
	}
	return seq;
}

int free_sequence_of_unique_numbers(Sequence_of_unique_numbers* seq) {
	free(seq->unique_number_array);
	free(seq);
	return 0;
}

int main(void) {
	return 0;
}