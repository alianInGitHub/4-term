#include "avltree.h"
#include <fstream>
using namespace std;

int max(int a, int b)
{
    if(a > b) return a;
    return b;
}

void swap(int &a, int &b)
{
    int c = b;
    b = a;
    a = c;
}

void fix_height_add(AVLNode* &node)
{
    if(node == nullptr)
        return;
    if(node->is_leaf())
        return;
    if(node->right != nullptr)
    while(node->right->height + 1 > node->height)
    {
        node->height++;
    }
    if(node->left != nullptr)
    while (node->left->height + 1 > node->height) {
        node->height++;
    }
    fix_height_add(node->father);
}

void fix_height_del(AVLNode* &node)
{
    if(node == nullptr)
        return;
    if(node->is_leaf())
    {
        node->height = 0;
    } else
    if((node->right != nullptr) || (node->left != nullptr))
    {return;} else
    {
        if(node->left->height != node->right->height)
        {
            node->height = max(node->left->height,node->right->height) + 1;
        }
    }
    fix_height_del(node->father);

}

AVLTree::AVLTree(const char* file)
{
    this->root = nullptr;
    ifstream f(file);
    if(f.is_open())
    {
        string s;
        getline(f,s);
        ofstream of("output.txt");
        if(of.is_open())
        {
            of << s;
        }
        of.close();
        unsigned i = 0;
        while (i < s.size()) {
            while((i < s.size()) && (s[i] == ' ')) {
                i++;
            }
            int num = 0;
            while((i < s.size()) && (s[i] != ' '))
            {
                num = num * 10 + s[i] - '0';
                i++;
            }
            if(num == 0)
                break;
            this->add(num);
        }
    }
    f.close();
}

void AVLTree::rotate_left(AVLNode *&node)
{
    if(node == nullptr) return;
    AVLNode* granny = node->grandparent();
    AVLNode* father = node->father;
    if(father == nullptr)
        return;
    father->height--;
    node->height++;

    father->right = node->left;
    if(node->left != nullptr)
    {
        node->left->father = father;
    }
    node->left = father;
    node->father = granny;
    father->father = node;
    if(granny != nullptr)
    {
        if(granny->left == father)
        {
            granny->left = node;
        }else
        {
            granny->right = node;
        }
    } else
    {
        this->root = node;
    }
}

void AVLTree::rotate_right(AVLNode *&node)
{
    if(node == nullptr)
        return;
    AVLNode* granny = node->grandparent();
    AVLNode* father = node->father;
    if(father == nullptr)
        return;
    node->father = granny;
    father->left = node->right;
    if(node->right != nullptr)
    {
        node->right->father = father;
    }
    node->right = father;
    father->father = node;
    if(granny != nullptr)
    {
        if(granny->left == node->father)
        {
            granny->left = node;
        }else
        {
            granny->right = node;
        }
    } else
    {
        this->root = node;
    }
}

void AVLTree::big_rotate_right(AVLNode *&node)
{
    rotate_right(node->left->right);
    rotate_left(node->left);
}

void AVLTree::big_rotate_left(AVLNode *&node)
{
    rotate_left(node->right->left);
    rotate_right(node->right);
}

void AVLTree::add(int key)
{
    AVLNode* temp = root;
    AVLNode* father = nullptr;
    while(temp != nullptr)
    {
        if(temp->key < key)
        {
            father = temp;
            temp = temp->right;
        } else
            if(temp->key > key)
            {
                father = temp;
                temp = temp->left;
            } else
                return;
    }
    if(father == nullptr)
    {
        root = new AVLNode(key,0,nullptr,nullptr,father);
    } else
    {
        if(father->key < key)
        {
            father->right = new AVLNode(key,0,nullptr,nullptr,father);
        } else
        {
            father->left = new AVLNode(key,0,nullptr,nullptr,father);
        }
        fix_height_add(father);
        balance(father);
    }
}

void AVLTree::balance(AVLNode *&node)
{
    if(node == nullptr) return;
    if(node->height == 0)
    {
        if(!node->is_leaf())
        {
            node->height += 1;
        }
    } else
    {
        int difference;
        if(node->right == nullptr)
        {
            difference = node->left->height + 1;
        } else
            if(node->left == nullptr)
            {
                difference = node->right->height + 1;
            } else
                difference = node->right->height - node->left->height;
        if(difference >= 2)
        {
            if(node->right->left->height <= node->left->height)
            {
                rotate_right(node->right);
            } else
            {
                big_rotate_right(node->right);
            }
        } else
            if(difference <= -2)
            {
                if(node->left->right->height <= node->right->height)
                {
                    rotate_left(node->left);
                } else
                {
                    big_rotate_left(node->left);
                }
            }
    }
}

void AVLTree::remove(AVLNode *&node)
{
    if(node == nullptr)
        return;
    AVLNode* temp = node;
    if(node->is_leaf())
    {
        temp = node->father;
        node->father = nullptr;
        if(node->father->right == node)
        {
            node->father->right = nullptr;
        } else
            node->father->left = nullptr;
        delete node;
        if(temp->is_leaf())
        {
            temp->height--;
        }
    }
    if((temp->right != nullptr) && (temp->right->left != nullptr))
    {
        node = node->right->left;
        while(node->left != nullptr)
            node = node->left;
        swap(temp->key,node->key);
        remove(node);
    }
}
