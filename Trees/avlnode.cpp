#include "avlnode.h"

AVLNode::AVLNode()
{
    this->father = this->right = this->left = nullptr;
}

AVLNode::AVLNode(int _key, int _balance)
{
    this->key = _key;
    this->height = _balance;
    this->father = this->right = this->left = nullptr;
}
AVLNode::AVLNode(int _key, int _balance, AVLNode* _left, AVLNode* _right, AVLNode* _father)
{
    this->key = _key;
    this->height = _balance;
    this->left = _left;
    this->right = _right;
    this->father = _father;
}

bool AVLNode::is_leaf()
{
    if((this->left == nullptr) && (this->right == nullptr))
        return true;
    return false;
}
