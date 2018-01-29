#include <stddef.h>
#include <string.h>

#include "rb_node.h"

/* Static sentinel structure for root and leaves cuts the required storage in half. */
static const struct rb_node RB_NULL; // members statically initialized to zero, so color is RB_BLACK


struct rb_node* rb_find(const struct rb_node* tree, const struct rb_node* node)
{
    struct rb_node* t = tree;
    while(tree != NULL && strcmp(node->word, tree->word))
    {
        if(strcmp(node->word, tree->word) < 0)
            t = rb_find(tree->left, node);
        else
            t = rb_find(tree->right, node);
    }
    return t;
};


void rb_left_rotate(const struct rb_node* tree, const struct rb_node* node)
{
    struct rb_node* t = tree;
    struct rb_node* x = node;
    struct rb_node* y = x->right;
    x->right = y->left;
    if(y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL)
        t = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rb_right_rotate(const struct rb_node* tree, const struct rb_node* node)
{
    struct rb_node* t = tree;
    struct rb_node* x = node;
    struct rb_node* y = x->left;
    x->left = y->right;
    if(y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL)
        t = y;
    else if(x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

struct rb_node* rb_insert(const struct rb_node* tree, const struct rb_node* node)
{
    struct rb_node* z = node;
    struct rb_node* y = NULL;
    struct rb_node* x = tree;
    while(x != NULL)
    {
        y = x;
        if(strcmp(z->word, x->word))
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    x = tree;
    if(y == NULL)
        x = z;
    else if(strcmp(z->word, y->word))
        y->left = z;
    else
        y->right = z;
    z->left = NULL;
    z->right = NULL;
    z->color = RB_RED;
    //rb_restore_after_insert(tree, z);
};

