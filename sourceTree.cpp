//
// Created by User on 06.04.2020.
//

#include "sourceTree.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define tre first //using in print func
#define pos second //using in print func

//create random tree with depth n (or 10)
int generateTree(tree *&a, int n = 10) {
    delete a;
    a = nullptr;
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
        add(a, rand() % 24, rand() % 3 - 1);
    return 0;
}

//sieved adding
void add(tree *&tr, int id) {
    if (tr == nullptr) {
        //make tree (root)
        tree *temp = (tree *) malloc(sizeof(tree));
        temp->id = id;
        temp->left = nullptr;
        temp->right = nullptr;
        tr = temp;
    } else {
        if (id < tr->id)
            add(tr->left, id);
        else
            add(tr->right, id);
    }
}

void add(tree *&tr, int id, int we) {
    if (tr == nullptr) {
        //make tree (root)
        tree *temp = (tree *) malloc(sizeof(tree));
        temp->id = id;
        temp->we = we;
        temp->left = nullptr;
        temp->right = nullptr;
        tr = temp;
    } else {
        if (id < tr->id)
            add(tr->left, id, we);
        else
            add(tr->right, id, we);
    }
}

//print tree (root on the left)
void show(tree *t, int n) {
    if (t != nullptr) {
        show(t->left, n + 1);
        cout << setw(n * 4) << t->id << endl;
        show(t->right, n + 1);
    }
}

void show_we(tree *t, int n) {
    if (t != nullptr) {
        show_we(t->left, n + 1);
        cout << setw(n * 5) << t->id << '(' << t->we <<')' << endl;
        show_we(t->right, n + 1);
    }
}

//print tree of pointers (root on the left)
void showPointers(tree *t, int n) {
    if (t != nullptr) {
        showPointers(t->left, n + 1);
        cout << setw(n * 10) << t << endl;
        showPointers(t->right, n + 1);
    }
}

//does el. of tree has only left child?
bool isOnlyLeft(tree *t) {
    return ((t->left == nullptr) && (t->right != nullptr));
}

//does el. of tree has only right child?
bool isOnlyRight(tree *t) {
    return ((t->left != nullptr) && (t->right == nullptr));
}

//is el. of tree a leaf?
bool isLeaf(tree *t) {
    return (t->left == nullptr && t->right == nullptr);
}

//return pointer at el with given id
tree *elLocation(tree **t, int id) {
    if ((*t) == nullptr)
        return nullptr;
    if ((*t)->id == id)
        return (*t);
    else {
        if (id < (*t)->id)
            return elLocation(&((*t)->left), id);
        else
            return elLocation(&((*t)->right), id);
    }
}
//можно упростить? хотя бы без без двойных указателей

tree *getRightChild(tree *t) {
    tree *tmp = t;
    while (!(isOnlyLeft(tmp) || isLeaf(tmp)))
        tmp = tmp->right;
    return tmp;
}

tree *del(tree *t, int id) {
    if (t == nullptr)
        return t;

    if (id == t->id) {

        tree *tmp;
        if (t->right == nullptr)
            tmp = t->left;
        else {

            tree *ptr = t->right;
            if (ptr->left == nullptr) {
                ptr->left = t->left;
                tmp = ptr;
            } else {

                tree *pmin = ptr->left;
                while (pmin->left != nullptr) {
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = t->left;
                pmin->right = t->right;
                tmp = pmin;
            }
        }

        delete t; //free t
        return tmp;
    } else if (id < t->id)
        t->left = del(t->left, id);
    else
        t->right = del(t->right, id);
    return t;
}

//max of int x and y
int max(int x, int y) {
    if (x > y)
        return x;
    return y;
}

int pow(int x, int n) {
    int tmp = 1;
    for (int i = 0; i < n; i++)
        tmp *= x;
    return tmp;
}

//returns depth of given tree
int treeDepth(tree *t) {
    if (t == nullptr)
        return 0;
    if (isLeaf(t))
        return 1;
    return max(treeDepth(t->left), treeDepth(t->right)) + 1;
}

int _zeroDepth(tree *t, int d){
    if (t == nullptr)
        return -1;

    if (t->we == 0)
        return max(d, max(_zeroDepth(t->left, d+1), _zeroDepth(t->right, d+1)));
    else
        return max(_zeroDepth(t->left, d+1), _zeroDepth(t->right, d+1));
}

int zeroDepth(tree *t) {
    return _zeroDepth(t, 0);
}

//print tree (beautifully)
int print(tree *t) {
    int n = treeDepth(t);
    if (t == nullptr)
        return 0;

    int N = pow(2, n);
    pair<tree *, int> tmp[N];
    int tmp_size = 1, tmp_ind = 0;
    tmp[0].tre = t;
    tmp[0].pos = 34;

    pair<char, int> simple[pow(2, n)]; //! change with formula one day

    for (int i = 0; i < n; i++) {
        //print id this lvl
        cout << setw((tmp + (0 + tmp_ind) % N)->pos) << (tmp + (0 + tmp_ind) % N)->tre->id;
        cout << ' ';
        for (int k = 1; k < tmp_size; k++) {
            cout << setw((tmp + (k + tmp_ind) % N)->pos - (tmp + (k + tmp_ind - 1) % N)->pos)
                 << (tmp + (k + tmp_ind) % N)->tre->id;
        }
        cout << endl;

        //print '/', '\' this lvl
        int m = 0;
        if (i + 1 != n) {
            for (int k = 0; k < tmp_size; k++) {
                if (((tmp + (k + tmp_ind) % N)->tre->left != nullptr) &&
                    ((tmp + (k + tmp_ind) % N)->tre->right != nullptr)) {
                    simple[m++] = make_pair('/', (tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2));
                    simple[m++] = make_pair('\\', (tmp + (k + tmp_ind) % N)->pos + 32 / pow(2, i + 2));

                } else if ((tmp + (k + tmp_ind) % N)->tre->left != nullptr) {
                    simple[m++] = make_pair('/', (tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2));
                } else if ((tmp + (k + tmp_ind) % N)->tre->right != nullptr) {
                    simple[m++] = make_pair('\\', (tmp + (k + tmp_ind) % N)->pos + 32 / pow(2, i + 2));
                }
            }


            cout << setw((simple + (0 + 0))->pos) << (simple + (0 + 0))->first;
            for (int k = 1; k < m; k++) {
                cout << setw((simple + (k + 0))->pos - (simple + (k + 0 - 1))->pos)
                     << (simple + (k + 0))->first; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            }
        }

        /* if (i + 1 != n){
             if (((tmp + (0 + tmp_ind) % N)->tre->left != nullptr) && ((tmp + (0 + tmp_ind) % N)->tre->right != nullptr)) {
                 cout << setw((tmp + (0 + tmp_ind) % N)->pos - 32 / pow(2, i + 2) + space) << "/";
                 space = 32 / pow(2, i + 2);
                 cout << setw( 32 / pow(2, i + 2) + space) << "\\";
                 space = 32 / pow(2, i + 2);
             }
             else if ((tmp + (0 + tmp_ind) % N)->tre->left != nullptr){
                 cout << setw((tmp + (0 + tmp_ind) % N)->pos - 32 / pow(2, i + 2) + space) << "/";
                 space = 32 / pow(2, i + 2);
             }
             else if ((tmp + (0 + tmp_ind) % N)->tre->right != nullptr){
                 cout << setw( 32 / pow(2, i + 2) + space) << "\\";
                 space = 32 / pow(2, i + 2);
             }
             cout << ' ';

             for (int k = 1; k < tmp_size; k++){
                 if (((tmp + (k + tmp_ind) % N)->tre->left != nullptr) && ((tmp + (k + tmp_ind) % N)->tre->right != nullptr)) {
                     cout << setw(- 32 / pow(2, i + 2) + space +(tmp + (k + tmp_ind) % N)->pos - (tmp + (k + tmp_ind - 1) % N)->pos) << "/";
                     space = 32 / pow(2, i + 2);
                     cout << setw( 32 / pow(2, i + 2) + space +(tmp + (k + tmp_ind) % N)->pos - (tmp + (k + tmp_ind - 1) % N)->pos) << "\\";
                     space = 32 / pow(2, i + 2);
                 }
                 else if ((tmp + (k + tmp_ind) % N)->tre->left != nullptr){
                     cout << setw( - 32 / pow(2, i + 2) + space+(tmp + (k + tmp_ind) % N)->pos - (tmp + (k + tmp_ind - 1) % N)->pos) << "/";
                     space = 32 / pow(2, i + 2);
                 }
                 else if ((tmp + (k + tmp_ind) % N)->tre->right != nullptr){
                     cout << setw( 32 / pow(2, i + 2) + space+(tmp + (k + tmp_ind) % N)->pos - (tmp + (k + tmp_ind - 1) % N)->pos) << "\\";
                     space = 32 / pow(2, i + 2);
                 }
             }
 */

        /*if (((tmp + (0 + tmp_ind) % N)->tre->left != nullptr) && ((tmp + (0 + tmp_ind) % N)->tre->right != nullptr)) {
            cout << setw((tmp + (0 + tmp_ind) % N)->pos - 32 / pow(2, i + 2)) << "/";
            cout << setw(32 / pow(2, i + 2) << 1) << "\\";
            //cout << setw(32 / pow(2, i + 2)) << " ";
            space += 32 / pow(2, i + 2);
        }
        else if ((tmp + (0 + tmp_ind) % N)->tre->left != nullptr){
            cout << setw((tmp + (0 + tmp_ind) % N)->pos - 32 / pow(2, i + 2)) << "/";
            //cout << setw(32 / pow(2, i + 2) * 3) << ' ';
            space += 32 / pow(2, i + 2) * 3;
        }
        else if ((tmp + (0 + tmp_ind) % N)->tre->right != nullptr){
            cout << setw((tmp + (0 + tmp_ind) % N)->pos - 32 / pow(2, i + 2)) << ' ';
            cout << setw(32 / pow(2, i + 2) << 1) << "\\";
            //cout << setw(32 / pow(2, i + 2)) << " ";
            space += 32 / pow(2, i + 2);
        }
        else
            space = 2 + 32 / pow(2, i + 1);
        cout << ' ';

        for (int k = 1; k < tmp_size; k++) {
            if (((tmp + (k + tmp_ind) % N)->tre->left != nullptr) && ((tmp + (k + tmp_ind) % N)->tre->right != nullptr)) {
                cout << setw((tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2) + space) << "/";
                cout << setw(32 / pow(2, i + 2) << 1) << "\\";
                //cout << setw(32 / pow(2, i + 2)) << " ";
                space = 32 / pow(2, i + 2);
            }
            else if ((tmp + (k + tmp_ind) % N)->tre->left != nullptr){
                cout << setw((tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2) + space) << "/";
                //cout << setw(32 / pow(2, i + 2) * 3) << ' ';
                space = 32 / pow(2, i + 2) * 3;
            }
            else if ((tmp + (k + tmp_ind) % N)->tre->right != nullptr){
                ///cout << setw((tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2)) << ' ';
                cout << setw(32 / pow(2, i + 2) + (tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2) + space) << "\\";
                //cout << setw(32 / pow(2, i + 2)) << " ";
                space = 32 / pow(2, i + 2);
            } else
                space += 32 / pow (2, i + 1);
            cout << ' ';
        }*/
        //}
        cout << endl;
        //go to the next lvl
        int tmp_resize = 0;
        for (int j = 0; j < tmp_size; j++) {
            if ((tmp + (j + tmp_ind) % N)->tre->left != nullptr) {
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->tre = (tmp + (j + tmp_ind) % N)->tre->left;
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->pos =
                        (tmp + (j + tmp_ind) % N)->pos - 32 / pow(2, i + 1);
                tmp_resize++;
            }

            if ((tmp + (j + tmp_ind) % N)->tre->right != nullptr) {
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->tre = (tmp + (j + tmp_ind) % N)->tre->right;
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->pos =
                        (tmp + (j + tmp_ind) % N)->pos + 32 / pow(2, i + 1);
                tmp_resize++;
            }
        }

        tmp_ind = (tmp_ind + tmp_size) % N;
        tmp_size = tmp_resize;
    }
    return 0;
}


//print weights of the tree (beautifully)
int print_we(tree *t) {
    int n = treeDepth(t);
    if (t == nullptr)
        return 0;

    int N = pow(2, n);
    pair<tree *, int> tmp[N];
    int tmp_size = 1, tmp_ind = 0;
    tmp[0].tre = t;
    tmp[0].pos = 34;

    pair<char, int> simple[pow(2, n)]; //! change with formula one day

    for (int i = 0; i < n; i++) {
        //print we this lvl
        cout << setw((tmp + (0 + tmp_ind) % N)->pos) << (tmp + (0 + tmp_ind) % N)->tre->we;
        cout << ' ';
        for (int k = 1; k < tmp_size; k++) {
            cout << setw((tmp + (k + tmp_ind) % N)->pos - (tmp + (k + tmp_ind - 1) % N)->pos)
                 << (tmp + (k + tmp_ind) % N)->tre->we;
        }
        cout << endl;

        //print '/', '\' this lvl
        int m = 0;
        if (i + 1 != n) {
            for (int k = 0; k < tmp_size; k++) {
                if (((tmp + (k + tmp_ind) % N)->tre->left != nullptr) &&
                    ((tmp + (k + tmp_ind) % N)->tre->right != nullptr)) {
                    simple[m++] = make_pair('/', (tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2));
                    simple[m++] = make_pair('\\', (tmp + (k + tmp_ind) % N)->pos + 32 / pow(2, i + 2));

                } else if ((tmp + (k + tmp_ind) % N)->tre->left != nullptr) {
                    simple[m++] = make_pair('/', (tmp + (k + tmp_ind) % N)->pos - 32 / pow(2, i + 2));
                } else if ((tmp + (k + tmp_ind) % N)->tre->right != nullptr) {
                    simple[m++] = make_pair('\\', (tmp + (k + tmp_ind) % N)->pos + 32 / pow(2, i + 2));
                }
            }


            cout << setw((simple + (0 + 0))->pos) << (simple + (0 + 0))->first;
            for (int k = 1; k < m; k++) {
                cout << setw((simple + (k + 0))->pos - (simple + (k + 0 - 1))->pos)
                     << (simple + (k + 0))->first; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            }
        }
        
        cout << endl;
        //go to the next lvl
        int tmp_resize = 0;
        for (int j = 0; j < tmp_size; j++) {
            if ((tmp + (j + tmp_ind) % N)->tre->left != nullptr) {
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->tre = (tmp + (j + tmp_ind) % N)->tre->left;
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->pos =
                        (tmp + (j + tmp_ind) % N)->pos - 32 / pow(2, i + 1);
                tmp_resize++;
            }

            if ((tmp + (j + tmp_ind) % N)->tre->right != nullptr) {
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->tre = (tmp + (j + tmp_ind) % N)->tre->right;
                (tmp + (tmp_resize + tmp_ind + tmp_size) % N)->pos =
                        (tmp + (j + tmp_ind) % N)->pos + 32 / pow(2, i + 1);
                tmp_resize++;
            }
        }

        tmp_ind = (tmp_ind + tmp_size) % N;
        tmp_size = tmp_resize;
    }
    return 0;
}
