#include "rbtree.h"
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///......................NON..CLASS..FUNCTIONS.......................///
////////////////////////////////////////////////////////////////////////

bool black_siblings(RBNode* node)
{
    if(node->is_leaf())
        return true;
    if((node->right == nullptr) && (node->left->color == BLACK))
        return true;
    if((node->left == nullptr) && (node->right->color == BLACK))
        return true;
    if((node->left->color == BLACK) && (node->left->color == BLACK))
        return true;
    return false;
}


/////////////////////////////////////////////////////////////////////////
///..............................PUBLIC...............................///
/////////////////////////////////////////////////////////////////////////




RBTree::RBTree()
{
    root = nullptr;
}

void RBTree::read_file(const char *file)

{
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

void RBTree::write_file(const char *file)
{
    ofstream f(file);
    if(f.is_open())
    {
        f << root->key;
    }
    f.close();
}

void RBTree::add(int key)
{
    if(root == nullptr)
    {
        root = new RBNode(key,BLACK);
    } else
    {
        insert(key);
    }
}

void RBTree::insert(int key)
{

    RBNode* temp = root;
    RBNode* father = nullptr;
    while(temp != nullptr)
    {
        if(temp->key > key)
        {
            father = temp;
            temp = temp->left;
        } else
            if(temp->key < key)
            {
                father = temp;
                temp = temp->right;
            } else return;
    }
    if(father == nullptr)
    {
        temp = new RBNode(key,BLACK,1,nullptr,nullptr,root);
        insert_1(temp);
    } else
    {
        if(father->key > key)
        {
            father->left = new RBNode(key,RED,father->level + 1, nullptr,nullptr,father);
            insert_1(father->left);
        } else
        if(father->key < key)
        {
            father->right = new RBNode(key,RED,father->level + 1, nullptr,nullptr,father);
            insert_1(father->right);
        }
    }
}

void RBTree::remove(RBNode *node)
{
    if(node == nullptr)
        return;
    if(node->is_leaf())
    {
        if(node == node->father->right)
        {
            node->father->right = nullptr;
        } else
            node->father->left = nullptr;
        node->father = nullptr;
        delete node;
    } else
    {
        RBNode* temp = node;
        if((node->right != nullptr) && (node->right->left != nullptr))
        {
            node = node->right->left;
            while(!node->is_leaf())
                node = node->left;
            swap(temp->key,node->key);
            remove(node);
        } else
        {
            temp = node->right;
            temp->father = node->father;
            temp->left = node->left;
            node->right = node->left = node->father = nullptr;
            if(node == root)
                root = temp;
            delete node;
            fix_level(temp);
        }
        delete_0(temp);
    }
}



////////////////////////////////////////////////////////////////////////////////////////
///..................................PRIVATE.........................................///
////////////////////////////////////////////////////////////////////////////////////////






void RBTree::rotate_left(RBNode *node)
{
    if(node == nullptr) return;
    RBNode* granny = node->grandparent();
    RBNode* father = node->father;
    if(father == nullptr)
        return;
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

void RBTree::rotate_right(RBNode *node)
{
    if(node == nullptr)
        return;
    RBNode* granny = node->grandparent();
    RBNode* father = node->father;
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

void RBTree::fix_level(RBNode* node)
{
    if(node == nullptr) return;
    node->level--;

    if((node->right != nullptr) && (node->level + 2 == node->right->level))
    {
        fix_level(node->right);
    }
    if((node->left != nullptr) && (node->level + 2 ==  node->left->level))
    {
        fix_level(node->left);
    }
}


bool RBTree::is_leaf(RBNode *node)
{
    if(node == nullptr) return true;
    if((node->left == nullptr) && (node->right == nullptr))
    {
        return true;
    }
    return false;
}

void  RBTree::insert_0(RBNode* node)
{
    if(node->father == nullptr)
    {
        node->color = BLACK;
    } else insert_1(node);
}

void RBTree::insert_1(RBNode* node)
{
    if(node->father->color == RED)
    {
        insert_2(node);
    } else
        return;
}

void RBTree::insert_2(RBNode *node)
{
    RBNode* uncle = node->uncle();
    RBNode* granny = node->grandparent();

    if((uncle != nullptr) && (node->father->color == RED) && (uncle->color == RED))
    {
        node->father->color = BLACK;
        uncle->color = BLACK;
        granny->color = RED;
        insert_0(granny);
    } else
    {
        insert_3(node);
    }
}

void RBTree::insert_3(RBNode *node)
{
    RBNode* granny = node->grandparent();

    if(granny != nullptr)
    {
        if((node->father->right == node) && (node->father == granny->left))
        {
            rotate_left(node);
            node = node->left;
        } else
            if((node->father->left == node) && (node->father == granny->right))
            {
                rotate_right(node);
                node = node->right;
            }
        insert_4(node);
    }
}

void RBTree::insert_4(RBNode *node)
{
    RBNode* granny = node->grandparent();
    node->father->color = BLACK;
    node->color = RED;
    if((node->father->right == node) && (node->father == granny->left))
    {
        rotate_left(granny);
    } else
        if((node->father->left == node) && (node->father == granny->right))
        {
            rotate_right(granny);
        }
}

void RBTree::delete_0(RBNode *node)
{
    if(node->father != nullptr)
    {
        delete_1(node);
    }
}

void RBTree::delete_1(RBNode *node)
{
    RBNode* brother = node->brother();
    if(brother == nullptr) return;
    if(brother->color == RED)
    {
        node->father->color = RED;
        brother->color = BLACK;
        if(node->father->left == node)
        {
            rotate_left(node->father);
        } else
            rotate_right(node->father);
    }
    delete_2(node);
}

void RBTree::delete_2(RBNode *node)
{
    RBNode* brother = node->brother();
    if(brother == nullptr) return;
    if ((node->father->color == BLACK) &&
            (brother->color == BLACK) && black_siblings(brother))
    {
        delete_0(node->father);
    } else
       delete_3(node);
}

void RBTree::delete_3(RBNode *node)
{
    RBNode* brother = node->brother();
    if(brother == nullptr) return;
    if ((node->father->color == RED) &&
            (brother->color == BLACK) &&
            black_siblings(brother))
    {
        brother->color = RED;
        brother->father->color = BLACK;
    } else
        delete_4(node);
}

void RBTree::delete_4(RBNode *node)
{
    RBNode* brother = node->brother();
    if(brother == nullptr) return;
    if(brother->color == BLACK)
    {
        if ((node->father->left == node) &&
                ((brother->right == nullptr) || (brother->right->color == BLACK)) &&
                ((brother->left != nullptr) && (brother->left->color == RED)))
        { /* this last test is trivial too due to cases 2-4. */
            brother->color = RED;
            brother->left->color = BLACK;
            rotate_right(brother);
        } else if ((node == node->father->right) &&
                   ((brother->left == nullptr) || (brother->left->color == BLACK)) &&
                   ((brother->right != nullptr) && (brother->right->color == RED)))
        {/* this last test is trivial too due to cases 2-4. */
            brother->color = RED;
            brother->right->color = BLACK;
            rotate_left(brother);
        }
    }
}

void RBTree::delete_5(RBNode *node)
{
    RBNode* brother = node->brother();
    if(brother == nullptr) return;
    brother->color = node->father->color;
    node->father->color = BLACK;

    if (node->father->left == node)
    {
        node->right->color = BLACK;
        rotate_left(node->father);
    } else
    {
        node->left->color = BLACK;
        rotate_right(node->father);
    }
}
