#ifndef RBNODE_H
#define RBNODE_H

#define BLACK  0
#define RED    1

class RBNode
{
public:
    bool color; // 0 black, 1 red
    int  key;
    int level;
    RBNode* left;
    RBNode* right;
    RBNode* father;

    RBNode(int _key, bool _color, int _level, RBNode* _left, RBNode* _right, RBNode* _father);
    RBNode(int _key, bool _color);
    RBNode();
    ~RBNode();
    RBNode* grandparent ();
    RBNode* uncle();
    RBNode* brother();

    bool is_leaf();
};

#endif // RBNODE_H
