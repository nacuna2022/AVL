#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct node_struct {
        int value;
        struct avl_head head;
};

static struct avl_head *tree;

int get_node_value(struct avl_head *head)
{
        struct node_struct *n = container_of(head, struct node_struct, head);
        return n->value;
}


static struct node_struct *new_node(const int value)
{
        struct node_struct *nn;
        nn = malloc(sizeof(struct node_struct));
        if (nn) {
                nn->value = value;
        }
        return nn;
}

static int compare_nodes(struct avl_head *head, struct avl_head *node)
{
        int err = 0;
        struct node_struct *h;
        struct node_struct *n;
        h = container_of(head, struct node_struct, head);
        n = container_of(node, struct node_struct, head);
        if (n->value < h->value) {
                err = -1; /* go left */
        } else if (n->value > h->value) {
                err = 1; /* go right */
        }
        return err; /* equal, let the library decide */
}

//static int values[10] = {25, 15, 1, 2, 12, 5, 34, 27, 7, 30};
static int values[] = {5, 4, 3, 2, 1};

int main(void)
{
        for (size_t i=0; i<(sizeof values/sizeof(int)); i++) {
                struct node_struct *node;
                node = new_node((int)values[i]);
                printf("inserting %d: ", node->value);
                fflush(stdout);
                tree = avl_add(tree, &node->head, compare_nodes);
        }
        return 0;
}

