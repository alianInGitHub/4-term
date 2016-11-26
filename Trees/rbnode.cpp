#include "rbnode.h"

RBNode::RBNode()
{
}

RBNode::RBNode(int _key, bool _color, int _level, RBNode* _left, RBNode* _right, RBNode* _father){
    this->key = _key;
    this->color = _color;
    this->level = _level;
    this->left = _left;
    this->right = _right;
    this->father = _father;
}

RBNode::RBNode(int _key, bool _color){
    this->key = _key;
    this->color = _color;
    this->level = 0;
    this->father = this->right = this->left = nullptr;
}
RBNode::~RBNode()
{
    this->father = this->right = this->left = nullptr;
}

RBNode* RBNode::brother()
{
    if(this == nullptr) return nullptr;

    if(this->father == nullptr) return nullptr;

    if(this->father->left == this)
    {
        return this->father->right;
    } else
        return this->father->left;
}

RBNode* RBNode::grandparent()
{
    if(this == nullptr) return nullptr;

    if(this->father == nullptr) return nullptr;

    return this->father->father;
}

RBNode* RBNode::uncle()
{
    if(this == nullptr) return nullptr;

    if(this->father == nullptr) return nullptr;

    if (this->grandparent() == nullptr)
    {
        return nullptr;
    } else
    {
        RBNode* granny = this->grandparent();
        if(granny->left == this->father)
        {
            return granny->right;
        } else
            return granny->left;
    }
}

bool RBNode::is_leaf()
{
    if(this == nullptr)
    {
        return true;
    }
    if((this->right == nullptr) && (this->left == nullptr))
    {
        return true;
    }
    return false;
}
