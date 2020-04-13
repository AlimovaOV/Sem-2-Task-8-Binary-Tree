#include <iostream>
#include "sourceTree.h"

using namespace std;

tree *a = nullptr;

int main() {
    cout << "Auto Generated tree is (printed without weights):\n";
    generateTree(a, 9);
    print(a);
    for (;;) {
        //get cmd
        cout << "Enter command:\n"
             << " 1 - beautifully print the tree (without weights)\n"
             << " 12 - beautifully print the tree (only weights)\n"
             << " 2 + N - generate new random binary tree with N vertices (clears old one)\n"
             << " 3 + N + W - add vertex with id=N, weight=W to the tree\n"
             << " 4 + N - delete first vertex with id == N\n"
             << " 5 - print tree with 'show' function\n"
             << " 52 - print tree with weight by 'show_we' function\n"
             << " 6 - clear the tree\n"
             << " 7 - find the maximum path length from root to vertex with zero weight\n"
             << " 8 - EXIT\n";
        int cmd;
        cin >> cmd;
        int tmp, tmp2;
        switch (cmd) {
            case 1:
                print(a);
                break;
            case 12:
                print_we(a);
                break;
            case 2:
                cin >> tmp;
                generateTree(a, tmp);
                break;
            case 3:
                cin >> tmp >> tmp2;
                add(a, tmp, tmp2);
                break;
            case 4:
                cin >> tmp;
                del(a, tmp);
                break;
            case 5:
                show(a, 1);
                break;
            case 52:
                show_we(a, 1);
                break;
            case 6:
                delete a;
                a = nullptr;
                break;
            case 7:
                cout << zeroDepth(a) << endl;
                break;
            case 8:
                cout << "Za funkciy print hochu zachet po k/r ochen'";
                return 0;
            default:
                cout << "Smth gone wrong :c\n";
        }
    }
}
