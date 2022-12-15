#include "avl.h"

void avl_init_head(struct avl_head *head)
{
        if (head) {
                head->left = head->right = NULL;
        }
        return;
}

struct avl_head *avl_add(struct avl_head *tree,
                         struct avl_head *node, 
                         avl_comparator avlcmp)
{
        struct avl_head *tmp;
        if (tree == NULL) {
                return node;
        }
        if (avlcmp(tree, node) <0) {
                tmp = avl_add(tree->left, node, avlcmp);
                tree->left = tmp;
        } else {
                tmp = avl_add(tree->right, node, avlcmp);
                tree->right = tmp;
        }
        return tree;
}

