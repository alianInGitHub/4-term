#ifndef AVLNODE_H
#define AVLNODE_H

class AVLNode
{
public:
    AVLNode();
    AVLNode(int _key, int _balance);
    AVLNode(int _key, int _balance, AVLNode* _left, AVLNode* _right, AVLNode* _father);

    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode* father;
    AVLNode* grandparent(){
        if(this->father != nullptr)
        return this->father->father;
        return nullptr;
    }
    bool is_leaf();
};

#endif // AVLNODE_H
