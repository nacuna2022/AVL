#ifndef __AVL_H__
#define __AVL_H__
#include <stddef.h>
#include <stdbool.h>

#ifndef container_of
#define container_of(ptr, type, member) ({  \
                void *mptr = (void *)(ptr); \
                ((type *)(mptr - offsetof(type, member)));})
#endif

struct avl_head {
        int height;
        int debug_value;
        struct avl_head *left_child;
        struct avl_head *right_child;
};

/* head value >  node value : -1
 * head value == node value :  0
 * head value <  node value :  1
 */
typedef int (*avl_comparator)(struct avl_head *head, struct avl_head *node);

/* true = avl node contains data
 * false = avl node does not contain the data
 */
typedef bool (*avl_selector)(struct avl_head *head, const void *data);

void avl_init_head(struct avl_head *head);
struct avl_head *avl_add(struct avl_head *root,
                         struct avl_head *node, 
                         avl_comparator avlcmp);
struct avl_head *avl_search(struct avl_head *root, 
                            struct avl_head *node,
                            avl_comparator avlcmp,
                            avl_selector avlsel);
#endif /* __AVL_H__ */
