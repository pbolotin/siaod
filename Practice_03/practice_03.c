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

#define DEBUG_INFO(S) printf(S)
//#define DEBUG_INFO(S)

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

typedef struct ABL_tree_vertex {
	struct ABL_tree_vertex *right;
	struct ABL_tree_vertex *left;
	int balance;
	int key;
} ABL_tree_vertex;

ABL_tree_vertex* init_binary_tree() {
    ABL_tree_vertex* root = (ABL_tree_vertex*)malloc(sizeof(ABL_tree_vertex));
    root->key = 0;
	root->balance = 0;
    root->left  = NULL;
    root->right = NULL;
    return root;
}

//#BUG: strange for creation, maybe should have done it as it is in the lectures?
ABL_tree_vertex* add_vertex_into_ABL_tree_of_search(ABL_tree_vertex* vertex, int key, int* growing) {
	if(vertex == NULL) {
		printf("Create\n");
		ABL_tree_vertex* new_vertex = (ABL_tree_vertex*)malloc(sizeof(ABL_tree_vertex));
		new_vertex->key = key;
		new_vertex->left = NULL;
		new_vertex->right = NULL;
		new_vertex->balance = 0;
		*growing = 1;
		return new_vertex;
		//1 New vertex
		//key
		//L,R NULL
		//bal = 0
		//grow true
	} else {
		if(vertex->key > key) {
			printf("L\n");
			vertex->left = add_vertex_into_ABL_tree_of_search(vertex->left, key, growing);
			if(*growing == 1) {
				if(vertex->balance > 0) {//Правое поддерево было больше
					vertex->balance = 0;//Сбалансировали добавлением
					*growing = 0;//Рост не происходит
				} else if(vertex->balance == 0) {//Поддеревья были равны
					vertex->balance = -1;//Баланс сместился влево
					//Рост происходит!
				} else {//Поддерево слева больше на текущем уровне (было) ещё и рост!
					if(vertex->left->balance < 0) {//Поддерево слева больше на нижнем уровне, поэтому уже нужно баланс находить
						//vertex->balance = -2;//Разбалансировалось дерево, на этом узле
						//Надо выбрать, что делать, или LL, или LR
						//Так как два узла по левой сторне, то делаем LL поворот
						printf("LL\n");
						ABL_tree_vertex* p = vertex;
						ABL_tree_vertex* q = p->left;
						p->left = q->right;
						q->right = p;
						p = q;
						vertex = p;
					} else {//Поддерево слева нормальное, значит, поддерево справа растёт, значит делаем LR
						printf("LR\n");
					}
					//После поворота рост купирован
					*growing = 0;
				}
			}
		}
		else if(vertex->key < key) {
			printf("R\n");
			vertex->right = add_vertex_into_ABL_tree_of_search(vertex->right, key, growing);
		}
		else {
			printf("This key is exist!\n");
			return vertex;
		}
	}
}

ABL_tree_vertex* create_ABL_tree_of_search_from_sequence_of_unique_numbers(Sequence_of_unique_numbers* seq) {
	if(seq == NULL) return NULL;
	if(seq->how_many <= 0) return NULL;
	
	ABL_tree_vertex* root = NULL;
	int growing = 0;
	for(int i = 0; i < seq->how_many; i++) {
		root = add_vertex_into_ABL_tree_of_search(root, seq->unique_number_array[i], &growing);
	}
	
    return root;
}

ABL_tree_vertex* test_add_vertex_and_balance_tree(ABL_tree_vertex* vertex, int key, int *growing) {
	if(vertex == NULL) {
		ABL_tree_vertex* new_vertex = (ABL_tree_vertex*)malloc(sizeof(ABL_tree_vertex));
		new_vertex->balance = 0;
		new_vertex->key = key;
		new_vertex->left = NULL;
		new_vertex->right = NULL;
		*growing = 1;
		return new_vertex;
	}
	
	if(key < vertex->key) {
		vertex->left = test_add_vertex_and_balance_tree(vertex->left, key, growing);
		if(*growing != 0) {
			if(vertex->balance <= 0) {
				vertex->balance--;
				if(vertex->balance == -2) {
					ABL_tree_vertex* temp;
					if(vertex->left->balance == -1) {
						DEBUG_INFO("Need LL\n");
						temp = vertex->left;
						vertex->left = vertex->left->right;
						temp->right = vertex;
						vertex = temp;
						vertex->balance = 0;
						vertex->right->balance = 0;
					} else {
						DEBUG_INFO("Need LR\n");
						temp = vertex->left->right;
						vertex->left->right = vertex->left->right->left;
						temp->left = vertex->left;
						vertex->left = temp->right;
						temp->right = vertex;
						vertex = temp;
						if(vertex->balance == -1) {
							vertex->left->balance = 0;
							vertex->right->balance = 1;
						} else {
							vertex->left->balance = -1;
							vertex->right->balance = 0;
						}
						vertex->balance = 0;
					}
					*growing = 0;
				}
			}
			if(vertex->balance > 0) {
				vertex->balance--;
				*growing = 0;
			}
			printf("Grow from left, balance:%d\n", vertex->balance);
		}
	} else if(key > vertex->key) {
		vertex->right = test_add_vertex_and_balance_tree(vertex->right, key, growing);
		if(*growing != 0) {
			if(vertex->balance >= 0) {
				vertex->balance++;
				if(vertex->balance == 2) {
					ABL_tree_vertex* temp;
					if(vertex->right->balance == 1) {
						DEBUG_INFO("Need RR\n");
						temp = vertex->right;
						vertex->right = vertex->right->left;
						temp->left = vertex;
						vertex = temp;
						vertex->balance = 0;
						vertex->left->balance = 0;
					} else {
						DEBUG_INFO("Need RL\n");
						temp = vertex->right->left;
						vertex->right->left = vertex->right->left->right;
						temp->right = vertex->right;
						vertex->right = temp->left;
						temp->left = vertex;
						vertex = temp;
						if(vertex->balance == 1) {
							vertex->right->balance = 0;
							vertex->left->balance = -1;
						} else {
							vertex->right->balance = 1;
							vertex->left->balance = 0;
						}
						vertex->balance = 0;
					}
					*growing = 0;
				}
			}
			if(vertex->balance < 0) {
				vertex->balance++;
				*growing = 0;
			}
			printf("Grow from right, balance:%d\n", vertex->balance);
		}
	}
	return vertex;
}

void test_print_tree(ABL_tree_vertex* vertex, int level, int parent_key, char from) {
	if(vertex == NULL) return;
	
	for(int i = 0; i < level; i++) {
		printf(" ");
	}
	printf("l%d %c b%d p%d k%d\n", level, from, vertex->balance, parent_key, vertex->key);
	
	if(vertex->left != NULL) {
		test_print_tree(vertex->left, level+1, vertex->key, 'L');
	}
	if (vertex->right != NULL) {
		test_print_tree(vertex->right, level+1, vertex->key, 'R');
	}
}

ABL_tree_vertex* test_tree_create(Sequence_of_unique_numbers* seq) {
	printf("test tree create\n");
	if(seq == NULL) return NULL;
	if(seq->how_many <= 0) return NULL;
	
	ABL_tree_vertex* root = NULL;
	int growing = 0;
	for(int i = 0; i < seq->how_many; i++) {
		root = test_add_vertex_and_balance_tree(root, seq->unique_number_array[i], &growing);
	}
	
	return root;
}

//#BUG: strange for deletion, maybe easy?
int free_binary_tree(ABL_tree_vertex* vertex) {
    unsigned int how_many_vertices_are_freed = 0;
    ABL_tree_vertex* left = vertex->left;
    ABL_tree_vertex* right = vertex->right;
    //printf("Good bye, vertex with number %d. We'll remember you!\n", vertex->key);
    free(vertex);
    how_many_vertices_are_freed++;
    if(left != NULL) {
        how_many_vertices_are_freed += free_binary_tree(left);
    }
    if(right != NULL) {
        how_many_vertices_are_freed += free_binary_tree(right);
    }
    return how_many_vertices_are_freed;
}

int main(void) {
	srand(time(NULL));
	Sequence_of_unique_numbers *seq = create_sequence_of_unique_numbers(10, 'r');
	for(int i = 0; i < seq->how_many; i++) {
		printf("%d ", seq->unique_number_array[i]);
	}
	
	//ABL_tree_vertex* ABL_tree = create_ABL_tree_of_search_from_sequence_of_unique_numbers(seq);
	//printf("%p\n", (void*)ABL_tree);
	//free_binary_tree(ABL_tree);
	
	free_sequence_of_unique_numbers(seq);
	
	//test
	Sequence_of_unique_numbers *test_seq = (Sequence_of_unique_numbers*)malloc(sizeof(Sequence_of_unique_numbers));
	test_seq->how_many = 6;
	//int test_array[4] = {11, 9, 2, 12};
	//int test_array[6] = {10, 11, 7, 9, 6, 8};
	//int test_array[6] = {10, 11, 6, 5, 7, 8};
	//int test_array[6] = {10, 11, 12};
	int test_array[6] = {10, 6, 14, 12, 18, 13};
	test_seq->unique_number_array = test_array;
	ABL_tree_vertex* test_tree = test_tree_create(test_seq);
	test_print_tree(test_tree, 0, -1, 'Z');
	free_binary_tree(test_tree);
		
	return 0;
}