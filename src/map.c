
#include "map.h"
#include "defs.h"
#include <stdlib.h>

#define TABLE_CAPACITY 101

typedef struct node node_t;
typedef struct map map_t;

struct node
{
    char *key;  // string
    int *value; // number
    node_t *next;
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
    node_t *current, *next;

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

void *map_insert(map_t *map, void *key, size_t key_size, void *value)
{
}

void *map_remove(map_t *map, void *key)
{
}

void *map_get(map_t *map, void *key)
{
}
