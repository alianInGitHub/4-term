#ifndef AVLTREE_H
#define AVLTREE_H

#include "avlnode.h"

class AVLTree
{
    friend class AVLNode;
public:
    AVLTree(const char* file);
    AVLNode* root;
    void read_file(const char* file);
    void add(int key);
    void remove(AVLNode* &node);
    void rotate_right(AVLNode* &node);
private:
    void balance(AVLNode* &node);

    void rotate_left(AVLNode* &node);
    void big_rotate_right(AVLNode* &node);
    void big_rotate_left(AVLNode* &node);
};

#endif // AVLTREE_H
