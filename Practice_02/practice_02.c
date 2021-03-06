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

#define INT_MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct Binary_tree_vertex {
    struct Binary_tree_vertex *pointer_to_the_left;
    struct Binary_tree_vertex *pointer_to_the_right;
    int key_value;
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

Binary_tree_vertex* init_binary_tree() {
    Binary_tree_vertex* root = (Binary_tree_vertex*)malloc(sizeof(Binary_tree_vertex));
    root->key_value = 0;
    root->pointer_to_the_left  = NULL;
    root->pointer_to_the_right = NULL;
    return root;
}

//#BUG: strange for creation, maybe should have done it as it is in the lectures?
void add_vertex_into_binary_tree_of_search(Binary_tree_vertex* vertex, int key_value) {
	if(vertex->key_value > key_value) {
		//printf("L");
		if(vertex->pointer_to_the_left != NULL) {
			add_vertex_into_binary_tree_of_search(vertex->pointer_to_the_left, key_value);
		} else {
			Binary_tree_vertex* new_vertex = init_binary_tree();
			vertex->pointer_to_the_left = new_vertex;
			new_vertex->key_value = key_value;
		}
	} else if(vertex->key_value < key_value) {
		//printf("R");
		if(vertex->pointer_to_the_right != NULL) {
			add_vertex_into_binary_tree_of_search(vertex->pointer_to_the_right, key_value);
		} else {
			Binary_tree_vertex* new_vertex = init_binary_tree();
			vertex->pointer_to_the_right = new_vertex;
			new_vertex->key_value = key_value;
		}
	}
}

Binary_tree_vertex* create_random_tree_of_search_from_sequence_of_unique_numbers(Sequence_of_unique_numbers* seq) {
	if(seq == NULL) return NULL;
	if(seq->how_many <= 0) return NULL;
	
    Binary_tree_vertex* root = init_binary_tree();
    root->key_value = seq->unique_number_array[0];
	
	for(int i = 1; i < seq->how_many; i++) {
		add_vertex_into_binary_tree_of_search(root, seq->unique_number_array[i]);
	}
	
    return root;
}

//#BUG: strange for deletion, maybe easy?
int free_binary_tree(Binary_tree_vertex* vertex) {
    unsigned int how_many_vertices_are_freed = 0;
    Binary_tree_vertex* left_pointer = vertex->pointer_to_the_left;
    Binary_tree_vertex* right_pointer = vertex->pointer_to_the_right;
    //printf("Good bye, vertex with number %d. We'll remember you!\n", vertex->key_value);
    free(vertex);
    how_many_vertices_are_freed++;
    if(left_pointer != NULL) {
        how_many_vertices_are_freed += free_binary_tree(left_pointer);
    }
    if(right_pointer != NULL) {
        how_many_vertices_are_freed += free_binary_tree(right_pointer);
    }
    return how_many_vertices_are_freed;
}

unsigned int size_of_binary_tree(Binary_tree_vertex* vertex) {
    if(vertex == NULL) return 0;
    return 1 + size_of_binary_tree(vertex->pointer_to_the_left) + size_of_binary_tree(vertex->pointer_to_the_right);
}

unsigned int height_of_binary_tree(Binary_tree_vertex* vertex) {
    if(vertex == NULL) return 0;
    return 1 + INT_MAX(height_of_binary_tree(vertex->pointer_to_the_left), height_of_binary_tree(vertex->pointer_to_the_right));
}

unsigned int sum_of_paths_of_binary_tree(Binary_tree_vertex* vertex, unsigned int level) {
    if(vertex == NULL) return 0;
    return level + sum_of_paths_of_binary_tree(vertex->pointer_to_the_left, level+1) + sum_of_paths_of_binary_tree(vertex->pointer_to_the_right, level+1);
}

double middle_height_of_binary_tree(Binary_tree_vertex* vertex) {
    return (double)sum_of_paths_of_binary_tree(vertex, 1)/size_of_binary_tree(vertex);
}

unsigned int control_sum_of_binary_tree(Binary_tree_vertex* vertex) {
    if(vertex == NULL) return 0;
    return vertex->key_value + control_sum_of_binary_tree(vertex->pointer_to_the_left) + control_sum_of_binary_tree(vertex->pointer_to_the_right);
}

void walk_around_from_the_left_to_the_right(Binary_tree_vertex* vertex) {
    if(vertex == NULL) return;
    walk_around_from_the_left_to_the_right(vertex->pointer_to_the_left);
    printf("%d ", vertex->key_value);
    walk_around_from_the_left_to_the_right(vertex->pointer_to_the_right);
}


Binary_tree_vertex* create_ideal_balance_tree_of_search_from_sequence_of_unique_numbers(Sequence_of_unique_numbers* seq, int left_index, int right_index) {
	if(left_index > right_index) {
		return NULL;
	}
	int mid = (int)(left_index + right_index) / 2;
	//printf("%d, %d, %d, %d, %d\n", left_index, mid - 1, mid, mid + 1, right_index);
	Binary_tree_vertex* vertex = init_binary_tree();
	vertex->key_value = seq->unique_number_array[mid];
	vertex->pointer_to_the_left = create_ideal_balance_tree_of_search_from_sequence_of_unique_numbers(seq, left_index, mid - 1);
	vertex->pointer_to_the_right = create_ideal_balance_tree_of_search_from_sequence_of_unique_numbers(seq, mid + 1, right_index);
	return vertex;
}

int is_it_binary_tree_of_search(Binary_tree_vertex* vertex) {
	if(vertex != NULL &&
		(vertex->pointer_to_the_left != NULL && (
		  vertex->key_value <= vertex->pointer_to_the_left->key_value ||
		  !is_it_binary_tree_of_search(vertex->pointer_to_the_left))) ||
		 (vertex->pointer_to_the_right != NULL && (
		  vertex->key_value >= vertex->pointer_to_the_right->key_value ||
		  !is_it_binary_tree_of_search(vertex->pointer_to_the_right)))
	) return 0;
	return 1;
}

Binary_tree_vertex* find_vertex_with_key_in_the_tree(Binary_tree_vertex* vertex, int key) {
	Binary_tree_vertex* curr = vertex;
	for(; curr != NULL;) {
		if(curr->key_value < key) curr = curr->pointer_to_the_right;
		else if (curr->key_value > key) curr = curr->pointer_to_the_left;
		else break;
	}
	return curr;
}

int how_many_operation_are_needed_to_find_key_in_the_tree(Binary_tree_vertex* vertex, int key) {
	Binary_tree_vertex* curr = vertex;
	int operations_counter = 0;
	for(; curr != NULL;) {
		if(curr->key_value < key) {
			operations_counter++;
			printf("%d ", curr->key_value);
			curr = curr->pointer_to_the_right;
		}
		else if(curr->key_value > key) {
			operations_counter++;
			printf("%d ", curr->key_value);
			curr = curr->pointer_to_the_left;
		}
		else break;
	}
	return operations_counter;
}

double _calculate_average_height(int n, int how_many_tries, char mode) {	
	int sum_of_heights = 0;
	for(int i = 0; i < how_many_tries; i++) {
		if(mode == 'r') {
			Sequence_of_unique_numbers* seq = create_sequence_of_unique_numbers(n, mode);
			Binary_tree_vertex* random_tree_of_search = create_random_tree_of_search_from_sequence_of_unique_numbers(seq);
			sum_of_heights += height_of_binary_tree(random_tree_of_search);
			if(!is_it_binary_tree_of_search(random_tree_of_search)) {
				free_binary_tree(random_tree_of_search);
				free_sequence_of_unique_numbers(seq);
				printf("Error, builded random_tree_of_search are wrong!\n");
				exit(-1);
			}
			free_binary_tree(random_tree_of_search);
			free_sequence_of_unique_numbers(seq);
		} else {
			Sequence_of_unique_numbers* seq = create_sequence_of_unique_numbers(n, 'a');
			Binary_tree_vertex* ideal_balance_tree_of_search = create_ideal_balance_tree_of_search_from_sequence_of_unique_numbers(seq, 0, seq->how_many - 1);
			sum_of_heights += height_of_binary_tree(ideal_balance_tree_of_search);
			if(!is_it_binary_tree_of_search(ideal_balance_tree_of_search)) {
				free_binary_tree(ideal_balance_tree_of_search);
				free_sequence_of_unique_numbers(seq);
				printf("Error, builded ideal_balance_tree_of_search are wrong!\n");
				exit(-1);
			}
			free_binary_tree(ideal_balance_tree_of_search);
			free_sequence_of_unique_numbers(seq);
		}
	}
	return (double)sum_of_heights/(double)how_many_tries;
}

int create_statistic_table(int how_many_tries) {
	printf("Average height RTS  n=10 : %f\n", _calculate_average_height(10 , how_many_tries, 'r'));
	printf("Average height RTS  n=50 : %f\n", _calculate_average_height(50 , how_many_tries, 'r'));
	printf("Average height RTS  n=100: %f\n", _calculate_average_height(100, how_many_tries, 'r'));
	printf("Average height RTS  n=200: %f\n", _calculate_average_height(200, how_many_tries, 'r'));
	printf("Average height RTS  n=400: %f\n", _calculate_average_height(400, how_many_tries, 'r'));
	
	printf("Average height IBTS n=10 : %f\n", _calculate_average_height(10 , how_many_tries, 'a'));
	printf("Average height IBTS n=50 : %f\n", _calculate_average_height(50 , how_many_tries, 'a'));
	printf("Average height IBTS n=100: %f\n", _calculate_average_height(100, how_many_tries, 'a'));
	printf("Average height IBTS n=200: %f\n", _calculate_average_height(200, how_many_tries, 'a'));
	printf("Average height IBTS n=400: %f\n", _calculate_average_height(400, how_many_tries, 'a'));
	return 0;
}

int main() {
	srand(time(NULL));
	printf("Create sequence of unique numbers\n");
	
	Sequence_of_unique_numbers* seq = create_sequence_of_unique_numbers(400, 'r');
	
//	for(int i = 0; i < seq->how_many; i++) {
//		printf("%d ", seq->unique_number_array[i]);
//	}
	
	Binary_tree_vertex* random_tree_of_search = create_random_tree_of_search_from_sequence_of_unique_numbers(seq);
	
	printf("Is it binary tree of search: %d\n", is_it_binary_tree_of_search(random_tree_of_search));
	printf("Size of binary tree        : %d\n", size_of_binary_tree(random_tree_of_search));
    printf("Height of binary tree      : %d\n", height_of_binary_tree(random_tree_of_search));
    printf("Sum of paths of binary tree: %d\n", sum_of_paths_of_binary_tree(random_tree_of_search, 0));
    printf("Middle height f binary tree: %f\n", middle_height_of_binary_tree(random_tree_of_search));
    printf("Control sum of binary tree : %d\n", control_sum_of_binary_tree(random_tree_of_search));
    walk_around_from_the_left_to_the_right(random_tree_of_search);
    printf("\n");
	printf("Address of found vertex    : %p\n", (void*)find_vertex_with_key_in_the_tree(random_tree_of_search, 0));
	printf("How many operation to find : %d\n", how_many_operation_are_needed_to_find_key_in_the_tree(random_tree_of_search, 0));
	printf("Address of found vertex    : %p\n", (void*)find_vertex_with_key_in_the_tree(random_tree_of_search, 200));
	printf("How many operation to find : %d\n", how_many_operation_are_needed_to_find_key_in_the_tree(random_tree_of_search, 200));
	printf("Address of found vertex    : %p\n", (void*)find_vertex_with_key_in_the_tree(random_tree_of_search, 400));
	printf("How many operation to find : %d\n", how_many_operation_are_needed_to_find_key_in_the_tree(random_tree_of_search, 400));
    printf("How many vertices are freed: %d\n", free_binary_tree(random_tree_of_search));

	free_sequence_of_unique_numbers(seq);
	
	seq = create_sequence_of_unique_numbers(400, 'a');
	
	Binary_tree_vertex* ideal_balance_tree_of_search = create_ideal_balance_tree_of_search_from_sequence_of_unique_numbers(seq, 0, seq->how_many - 1);
	
	printf("Is it binary tree of search: %d\n", is_it_binary_tree_of_search(ideal_balance_tree_of_search));
	printf("Size of binary tree        : %d\n", size_of_binary_tree(ideal_balance_tree_of_search));
    printf("Height of binary tree      : %d\n", height_of_binary_tree(ideal_balance_tree_of_search));
    printf("Sum of paths of binary tree: %d\n", sum_of_paths_of_binary_tree(ideal_balance_tree_of_search, 0));
    printf("Middle height f binary tree: %f\n", middle_height_of_binary_tree(ideal_balance_tree_of_search));
    printf("Control sum of binary tree : %d\n", control_sum_of_binary_tree(ideal_balance_tree_of_search));
    walk_around_from_the_left_to_the_right(ideal_balance_tree_of_search);
    printf("\n");
	printf("Address of found vertex    : %p\n", (void*)find_vertex_with_key_in_the_tree(ideal_balance_tree_of_search, 0));
	printf("How many operation to find : %d\n", how_many_operation_are_needed_to_find_key_in_the_tree(ideal_balance_tree_of_search, 0));
	printf("Address of found vertex    : %p\n", (void*)find_vertex_with_key_in_the_tree(ideal_balance_tree_of_search, 200));
	printf("How many operation to find : %d\n", how_many_operation_are_needed_to_find_key_in_the_tree(ideal_balance_tree_of_search, 200));
	printf("Address of found vertex    : %p\n", (void*)find_vertex_with_key_in_the_tree(ideal_balance_tree_of_search, 400));
	printf("How many operation to find : %d\n", how_many_operation_are_needed_to_find_key_in_the_tree(ideal_balance_tree_of_search, 400));
    printf("How many vertices are freed: %d\n", free_binary_tree(ideal_balance_tree_of_search));

	free_sequence_of_unique_numbers(seq);
	
	create_statistic_table(1000);
	
    return 0;
}