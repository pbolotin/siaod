/**************************************************************************
Topic:  Building of binary tree
***************************************************************************
Goal:   To know of binary tree
***************************************************************************
1.  To place in memory b.t. from picture (see below)
    Vertexes are filled by random numbers.
***************************************************************************
2.  To develop procedures for calculation of size,
    height, middle height, control sum of binary tree.
    And to check them on example.
***************************************************************************
3.  To create walk-around procedure for binary tree
    from the left to the right,
    and print result sequence
***************************************************************************
Personal number:73180026
***************************************************************************
Last number: 6
***************************************************************************
Binary tree number 6:
    p
   / \
  p   p
 /   /
p   p
     \
      p
***************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct Binary_tree_vertex {
    struct Binary_tree_vertex *pointer_to_the_left;
    struct Binary_tree_vertex *pointer_to_the_right;
    int random_number;
} Binary_tree_vertex;

Binary_tree_vertex* add_left_vertex(Binary_tree_vertex* to_which_vertex) {
    Binary_tree_vertex* new_vertex = (Binary_tree_vertex*)malloc(sizeof(Binary_tree_vertex));
    new_vertex->random_number = 0;
    new_vertex->pointer_to_the_left  = NULL;
    new_vertex->pointer_to_the_right = NULL;
    to_which_vertex->pointer_to_the_left = new_vertex;
    return new_vertex;
}

Binary_tree_vertex* add_right_vertex(Binary_tree_vertex* to_which_vertex) {
    Binary_tree_vertex* new_vertex = (Binary_tree_vertex*)malloc(sizeof(Binary_tree_vertex));
    new_vertex->random_number = 0;
    new_vertex->pointer_to_the_left  = NULL;
    new_vertex->pointer_to_the_right = NULL;
    to_which_vertex->pointer_to_the_right = new_vertex;
    return new_vertex;
}

Binary_tree_vertex* init_binary_tree() {
    Binary_tree_vertex* root = (Binary_tree_vertex*)malloc(sizeof(Binary_tree_vertex));
    root->random_number = 0;
    root->pointer_to_the_left  = NULL;
    root->pointer_to_the_right = NULL;
    return root;
}

int free_binary_tree(Binary_tree_vertex* vertex) {
    unsigned int how_many_vertices_are_freed = 0;
    Binary_tree_vertex* left_pointer = vertex->pointer_to_the_left;
    Binary_tree_vertex* right_pointer = vertex->pointer_to_the_right;
    printf("Good bye, vertex with number %d. We'll remember you!\n", vertex->random_number);
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

Binary_tree_vertex* create_binary_tree() {
    Binary_tree_vertex* root = init_binary_tree();
    root->random_number = rand()%10;
    
    Binary_tree_vertex* vertex = add_left_vertex(root);
    vertex->random_number = rand()%10;
    vertex = add_left_vertex(vertex);
    vertex->random_number = rand()%10;
    
    vertex = add_right_vertex(root);
    vertex->random_number = rand()%10;
    vertex = add_left_vertex(vertex);
    vertex->random_number = rand()%10;
    vertex = add_right_vertex(vertex);
    vertex->random_number = rand()%10;
    return root;
}

unsigned int size_of_binary_tree(Binary_tree_vertex* vertex) {
    if(vertex == NULL) return 0;
    return 1 + size_of_binary_tree(vertex->pointer_to_the_left) + size_of_binary_tree(vertex->pointer_to_the_right);
}

unsigned int height_of_binary_tree(Binary_tree_vertex* vertex) {
    if(vertex == NULL) return 0;
    return 1 + MAX(height_of_binary_tree(vertex->pointer_to_the_left), height_of_binary_tree(vertex->pointer_to_the_right));
}

int main() {
    srand(time(NULL));

    Binary_tree_vertex* root = create_binary_tree();
    
    printf("Size of binary tree        : %d\n", size_of_binary_tree(root));
    printf("Height of binary tree      : %d\n", height_of_binary_tree(root));
    printf("How many vertices are freed: %d\n", free_binary_tree(root));
    return 0;
}