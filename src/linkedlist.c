#include "list.h"
#include "printing.h"

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

// TODO Find out for what we use this
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
    lnode_t *current = list->head;
    lnode_t *next;
    lnode_t *delete_node;

    while (current)
    {
        next = current->next;
        delete_node = current;
        if (item_free)
        {
            item_free(current->item);
        }
        current = next;
        free(delete_node);
    }

    free(list);
}

size_t list_length(list_t *list)
{
    if (!list)
        return 0;

    lnode_t *current = list->head;
    size_t lenght = 0;
    while (current)
    {
        lenght++;
        current = current->next;
    }

    list->length = lenght;
    return lenght;
}

int list_addfirst(list_t *list, void *item)
{
    if (!list || !item)
        return -22;

    lnode_t *new_node = malloc(sizeof(lnode_t));
    lnode_t *current = list->head;

    if (!new_node)
        return -12;

    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
        new_node->item = item;
    }
    else
    {
        current->prev = new_node;
        new_node->next = current;
        new_node->prev = NULL;
        new_node->item = item;
        list->head = new_node;
    }

    return 0;
}

int list_addlast(list_t *list, void *item)
{
    if (!list || !item)
        return -22;

    lnode_t *new_node = malloc(sizeof(lnode_t));
    lnode_t *current = list->tail;

    if (!new_node)
        return -12;

    if (list->tail == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->item = item;
    }
    else
    {
        current->next = new_node;
        new_node->next = NULL;
        new_node->prev = current;
        new_node->item = item;
        list->tail = new_node;
    }

    return 0;
}

void *list_popfirst(list_t *list)
{
    if (!list || !list->head)
        PANIC();

    lnode_t *old_node = list->head;
    void *item = old_node->item;

    if (list_length(list) != 1)
    {
        list->head = old_node->next;
        list->head->prev = NULL;
    }
    else
    {
        list->head = NULL;
        list->tail = NULL;
    }

    free(old_node);
    return item;
}

void *list_poplast(list_t *list)
{
    if (!list || !list->tail)
        PANIC();

    lnode_t *old_node;
    if (list_length(list) == 1)
    {
        old_node = list->head;
    }
    else
    {
        old_node = list->tail;
    }
    void *item = old_node->item;

    if (list_length(list) != 1)
    {
        list->tail = old_node->prev;
        list->tail->next = NULL;
    }
    else
    {
        list->tail = NULL;
        list->head = NULL;
    }

    free(old_node);

    return item;
}

int list_contains(list_t *list, void *item)
{
    if (!list || !item || !list->head)
        return 0;

    lnode_t *current = list->head;

    while (current)
    {
        if (!list->cmpfn(current->item, item))
        {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

void list_sort(list_t *list)
{
}

list_iter_t *list_createiter(list_t *list)
{
    if (!list)
        return NULL;

    list_iter_t *new_iter = malloc(sizeof(list_iter_t));

    if (!new_iter)
        return NULL;

    new_iter->list = list;
    new_iter->node = list->head;

    return new_iter;
}

void list_destroyiter(list_iter_t *iter)
{
    free(iter);
}

int list_hasnext(list_iter_t *iter)
{
    lnode_t *current = iter->node;

    if (current == NULL)
    {
        return 0;
    }

    return 1;
}

void *list_next(list_iter_t *iter)
{
    lnode_t *current = iter->node;

    if (list_hasnext(iter))
    {
        iter->node = current->next;
    }

    return current->item;
}

// TODO Implemet this. Reset iter to the firt item in the list
void list_resetiter(list_iter_t *iter)
{
}
