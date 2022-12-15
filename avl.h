#ifndef __AVL_H__
#define __AVL_H__
#include <stddef.h>

#ifndef container_of
#define container_of(ptr, type, member) ({  \
                void *mptr = (void *)(ptr); \
                ((type *)(mptr - offsetof(type, member)));})
#endif

struct avl_head {
        struct avl_head *left;
        struct avl_head *right;
};

/* head value >  node value : -1
 * head value == node value :  0
 * head value <  node value :  1
 */
typedef int (*avl_comparator)(struct avl_head *head, struct avl_head *node);

void avl_init_head(struct avl_head *head);
struct avl_head *avl_add(struct avl_head *tree,
                         struct avl_head *node, 
                         avl_comparator avlcmp);
                
#endif /* __AVL_H__ */
