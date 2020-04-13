//
// Created by User on 06.04.2020.
//

#ifndef TASK_7__TREES_SOURCETREE_H
#define TASK_7__TREES_SOURCETREE_H

typedef struct link {
    int id;
    int we;
    link *left, *right;
} tree;

//sieved adding
void add(tree *&tr, int id); //without weight
void add(tree *&tr, int id, int we); //with weight

//print tree (root on the left)
void show(tree *t, int n);
void show_we(tree *t, int n);

//create random tree with depth n (or 10)
int generateTree(tree *&a, int n);

//print tree (almost beautifully)
int print(tree *t);
int print_we(tree *t);

//delete el with given id from the tree
tree* del(tree *t, int id);

tree *elLocation(tree **t, int id);

//find the maximum path length from root to vertex with zero weight
int zeroDepth(tree *t);
#endif //TASK_7__TREES_SOURCETREE_H
