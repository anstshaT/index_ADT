#include "list.h"

#include <stdlib.h>

typedef struct lnode lnode_t;
struct lnode
{
    lnode_t *next;
    lnode_t *prev;
    void *item;
};

struct list
{
    lnode_t *head;
    lnode_t *tail;
    size_t length;
    cmp_fn cmpfn;
};

struct list_iter
{
    list_t *list;
    lnode_t *node;
};

#TODO Find out for what we use this
static lnode_t *newnode(void *item)
{
}

list_t *list_create(cmp_fn cmpfn)
{
    list_t *list = malloc(sizeof(list_t));

    if (!list)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->cmpfn = cmpfn;

    return list;
}

void list_destroy(list_t *list, free_fn item_free)
{
}

size_t list_length(list_t *list)
{
}

int list_addfirst(list_t *list, void *item)
{
}

int list_addlast(list_t *list, void *item)
{
}

void *list_popfirst(list_t *list)
{
}

void *list_poplast(list_t *list)
{
}

int list_contains(list_t *list, void *item)
{
}

void list_sort(list_t *list)
{
}

list_iter_t *list_createiter(list_t *list)
{
}

void list_destroyiter(list_iter_t *iter)
{
}

int list_hasnext(list_iter_t *iter)
{
}

void *list_next(list_iter_t *iter)
{
}

void list_resetiter(list_iter_t *iter)
{
}
