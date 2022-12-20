#include <stdio.h>
#include "avl.h"

#define avl_max(a, b) ((a > b) ? a : b)


void avl_init_head(struct avl_head *head)
{
        if (head) {
                head->left_child = head->right_child = NULL;
        }
        return;
}

static int __avl_height(struct avl_head *root)
{
        return (root != NULL) ? root->height : -1;
}

/* height is the greater value between the height of left sub-tree and 
 * right sub-tree of a root */
static int avl_height(struct avl_head *root)
{
        int left_height;
        int right_height;
        left_height = __avl_height(root->left_child);
        right_height = __avl_height(root->right_child);
        return avl_max(left_height, right_height) + 1;
}

/**/
static int avl_balance(struct avl_head *root)
{
        int left_height;
        int right_height;
        left_height = __avl_height(root->left_child);
        right_height = __avl_height(root->right_child);
        return left_height - right_height;
}


static void avl_rotate_single(struct avl_head *new_root,
                              struct avl_head *new_left_child,
                              struct avl_head *new_right_child,
                              struct avl_head *new_lr_child,
                              struct avl_head *new_rl_child)
{
        new_root->left_child = new_left_child;
        new_root->right_child = new_right_child;
        new_left_child->right_child = new_lr_child;
        new_right_child->left_child = new_rl_child;
        return;
}

/* when left sub-tree is left heavy, (LL), single rotate right */
static struct avl_head *avl_ll(struct avl_head *root)
{
        struct avl_head *new_root = root->left_child;
        struct avl_head *new_left_child = new_root->left_child;
        avl_rotate_single(new_root,
                          new_root->left_child,
                          root,
                          new_left_child->right_child,
                          new_root->right_child);
        root->height = avl_height(root);
        new_root->height = avl_height(new_root);
        return new_root;
}

static struct avl_head *avl_lr(struct avl_head *root)
{
        /* compute balance factor here */
        return NULL;
}

static struct avl_head *avl_rr(struct avl_head *root)
{
        struct avl_head *new_root = root->right_child;
        struct avl_head *new_right_child = new_root->right_child;
        avl_rotate_single(new_root,
                          root,
                          new_root->right_child,
                          new_root->left_child,
                          new_right_child->left_child);
        root->height = avl_height(root);
        new_root->height = avl_height(new_root);
        return new_root;
}

static struct avl_head *avl_rl(struct avl_head *root)
{
        return NULL;
}

struct avl_head *avl_add(struct avl_head *root,
                         struct avl_head *node, 
                         avl_comparator avlcmp)
{
        int root_balance_factor;
        int child_balance_factor;
        if (root == NULL) {
                printf("inserted\n");
                avl_init_head(node);
                node->debug_value = get_node_value(node);
                root = node;
        } else {
                if (avlcmp(root, node) <0) {
                        printf("going left, ");
                        root->left_child = avl_add(root->left_child, node, avlcmp);
                } else {
                        printf("going right, ");
                        root->right_child = avl_add(root->right_child, node, avlcmp);
                }
        }

        root->height = avl_height(root);
        root_balance_factor = avl_balance(root);
        if (root_balance_factor == 2) {
                child_balance_factor = avl_balance(root->left_child);
                if (child_balance_factor == 1) {
                        root = avl_ll(root);
                } else if (child_balance_factor == -1) {
                        root = avl_lr(root);
                }
        } else if (root_balance_factor == -2) {
                child_balance_factor = avl_balance(root->right_child);
                if (child_balance_factor == -1) {
                        root = avl_rr(root);
                } else if (child_balance_factor == 1) {
                        root = avl_rl(root);
                }
        }
        return root;
}

struct avl_head *avl_search(struct avl_head *root, 
                            struct avl_head *node,
                            avl_comparator avlcmp,
                            avl_selector avlsel)
{
}

