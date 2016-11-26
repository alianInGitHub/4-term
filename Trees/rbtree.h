#ifndef RBTREE_H
#define RBTREE_H

#include "rbnode.h"
//#include "mainwindow.h"

#define BLACK  0
#define RED    1

class RBTree
{
    friend class RBNode;
public:
    RBTree();
    RBNode* root;
    int rbheight;
    void read_file(const char* file);
    void write_file(const char* file);
    void add(int key);
    void insert(int key);
    void remove(RBNode* node);
    void remove(int key)
    {
        RBNode* temp = root;
        while((temp != nullptr) && (temp->key != key))
        {
            if(temp->key < key)
            {
                temp = temp->right;
            } else temp = temp->left;
        }
        remove(temp);
    }

    void clear();

private:
    void rotate_left(RBNode* p);
    void rotate_right(RBNode* p);
    void DeleteFixUp(bool removed_color, RBNode* &node);
    void fix_level(RBNode* node);
    bool is_leaf(RBNode* node);
    void  insert_0(RBNode* node);
    void  insert_1(RBNode* node);
    void  insert_2(RBNode* node);
    void  insert_3(RBNode* node);
    void  insert_4(RBNode *node);

    void delete_0(RBNode* node);
    void delete_1(RBNode* node);
    void delete_2(RBNode* node);
    void delete_3(RBNode* node);
    void delete_4(RBNode* node);
    void delete_5(RBNode *node);
};

#endif // RBTREE_H
