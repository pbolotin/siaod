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

//#define DEBUG_INFO(S) printf(S)
#define DEBUG_INFO(S)

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

typedef struct Vertex {
	int balance;
	int date;
	struct Vertex* right;
	struct Vertex* left;
} Vertex;

Vertex* add_date_into_Bin_B_Tree(int date, Vertex* vertex, int *VR, int* HR) {
	Vertex *new_vertex = NULL;
	if(vertex == NULL) {
		new_vertex = (Vertex*)malloc(sizeof(Vertex));
		new_vertex->balance = 0;
		new_vertex->date    = date;
		new_vertex->right   = NULL;
		new_vertex->left    = NULL;
		*VR = 1;
	} else {
		if(vertex->date > date) {
			vertex->left = add_date_into_Bin_B_Tree(date, vertex->left, VR, HR);
			if(*VR) {
				if(vertex->balance == 0) {
					Vertex *q = vertex->left;
					vertex->left = q->right;
					q->right = vertex;
					vertex = q;
					q->balance = 1;
					*VR = 0;
					*HR = 1;
				} else {
					vertex->balance = 0;
					*HR = 1;
				}
			} else {
				*HR = 0;
			}
		} else if(vertex->date < date) {
			vertex->right = add_date_into_Bin_B_Tree(date, vertex->right, VR, HR);
			if(*VR) {
				vertex->balance = 1;
				*VR = 0;
				*HR = 1;
			} else if(*HR) {
				if(vertex->balance > 0) {
					Vertex *q = vertex->right;
					vertex->right = q->left;
					vertex->balance = 0;
					q->balance = 0;
					q->left = vertex;
					vertex = q;
					*VR = 1;
					*HR = 0;
				} else {
					*HR = 0;
				}
			}
		}
		return vertex;
	}
	return new_vertex;
}

Vertex* create_Bin_B_Tree_from_Sequence_of_unique(Sequence_of_unique_numbers* seq) {
	int VR = 1;
	int HR = 1;
	Vertex *vertex = NULL;
	for(int i = 0; i < seq->how_many; i++) {
		printf("Try add %d ", seq->unique_number_array[i]);
		vertex = add_date_into_Bin_B_Tree(seq->unique_number_array[i], vertex, &VR, &HR);
	}
	printf("\n");
	return vertex;
}

void print_Bin_B_Tree(Vertex *vertex, int level, int parent_date, char from) {
	if(vertex == NULL) return;
	
	for(int i = 0; i < level; i++) {
		printf(" ");
	}
	printf("l%d %c b%d p%d k%d\n", level, from, vertex->balance, parent_date, vertex->date);
	
	if(vertex->left != NULL) {
		print_Bin_B_Tree(vertex->left, level+1, vertex->date, 'L');
	}
	if (vertex->right != NULL) {
		print_Bin_B_Tree(vertex->right, level+1, vertex->date, 'R');
	}
}


int main(void) {
	srand(time(NULL));
	int how_many = 12;
	int test_array[12] = {12, 21, 18, 1, 17, 16, 3, 6, 13, 15, 10, 20};
	
	Sequence_of_unique_numbers seq;
	seq.how_many = how_many;
	seq.unique_number_array = test_array;
	
	Vertex* bin_b_tree = create_Bin_B_Tree_from_Sequence_of_unique(&seq);
	
	print_Bin_B_Tree(bin_b_tree, 0, -1, 'Z');
		
	return 0;
}