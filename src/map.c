
#include "map.h"
#include "defs.h"
#include <cstring>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_CAPACITY 101

typedef struct node node_t;
typedef struct map map_t;

struct node
{
    void *key;   // string
    void *value; // number
    node_t *next;
    node_t *prev;
};

struct map
{
    int capacity;
    int length;
    node_t **array;
    cmp_fn cmpfn;
    hash64_fn hashfn;
};

map_t *map_create(cmp_fn cmpfn, hash64_fn hashfn)
{
    map_t *table = malloc(sizeof(map_t));
    if (!table)
        return NULL;

    table->capacity = TABLE_CAPACITY;
    table->length = 0;
    table->cmpfn = cmpfn;
    table->hashfn = hashfn;
    table->array = malloc(table->capacity * sizeof(node_t));

    return table;
}

void map_destroy(map_t *map, free_fn val_freefn)
{
    if (!map)
        return;

    int i = 0;
    node_t *current, *next;

    while (i < map->capacity)
    {
        current = map->array[i];

        while (current)
        {
            next = current->next;
            if (val_freefn)
                val_freefn(current->value);
            free(current->key);
            free(current);
            current = next;
        };
        i++;
    };

    free(map->array);
    free(map);
}

size_t map_length(map_t *map)
{
    if (!map)
        return 0;

    size_t num = 0;
    int i = 0;
    node_t *current;

    while (i < map->capacity)
    {
        current = map->array[i];
        if (current != NULL)
        {
            if (current->next != NULL) // collision
            {
                while (current->next)
                {
                    num++;
                    current = current->next;
                }
            }
            num++;
        }
        i++;
    }

    map->length = num;
    return num;
}

node_t *nodepair(void *key, void *value, size_t key_size)
{
    if (!key || !value)
        return NULL;

    node_t *new = malloc(sizeof(node_t));
    if (!new)
        return NULL;

    new->key = malloc(key_size);
    if (!new->key)
    {
        free(new);
        return NULL;
    }

    memcpy(new->key, key, key_size);
    new->value = value;
    new->next = NULL;
    new->prev = NULL;

    return new;
}

void *map_insert(map_t *map, void *key, size_t key_size, void *value)
{
    if (!map || !key || !value)
        return NULL;

    node_t *new = nodepair(key, value, key_size);

    int hash = map->hashfn(key);
    node_t *current = map->array[hash];

    while (current != NULL)
    {
        if (memcmp(current->key, key, key_size) == 0)
        {
            void *old_val = current->value;
            current->value = value;
            free(new);
            return old_val;
        }
        current = current->next;
    }

    new->next = map->array[hash];
    if (map->array[hash] != NULL)
        map->array[hash]->prev = new;
    map->array[hash] = new;
    return NULL;
}

void *map_remove(map_t *map, void *key)
{
    if (!map || !key)
        return NULL;

    uint64_t hash = map->hashfn(key);
    node_t *current = map->array[hash];

    if (!current) // empty, key not exist
        return NULL;

    if (current->next) // checking linked list
    {
        while (current != NULL)
        {
            if (strcmp((char *)current->key, (char *)key) == 0)
            {
                if (current->next)
                {
                    node_t *old_node = current;
                                }
            }
            current = current->next;
        }
        return NULL;
    }
}

void *map_get(map_t *map, void *key)
{
}
