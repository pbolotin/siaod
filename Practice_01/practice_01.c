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
#include <stdio.h>

typedef struct Binary_tree_vertex {
    Binary_tree_vertex *pointer_to_the_left;
    Binary_tree_vertex *pointer_to_the_right;
    int random_number;
} Binary_tree_vertex;

int main() {
    return 0;
}