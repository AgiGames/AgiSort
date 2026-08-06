#ifndef HEAPS_MANAGER_H
#define HEAPS_MANAGER_H

#include <stdlib.h>

#include <heap.h>

typedef struct {
    size_t* capacities;
    size_t count;
    Heap* heaps;
    size_t* offsets;
    char* items;
} HeapsManager;

void hm_init(HeapsManager* hm, size_t* heap_capacities, size_t heap_count, size_t item_size, double (*score)(const void *));
void hm_push(HeapsManager* hm, size_t heap_index, char* bytes);
char* hm_pop(HeapsManager *hm, size_t heap_index);
void hm_free(HeapsManager* hm);
Heap* hm_get_heap(HeapsManager *hm, size_t heap_index);

#endif
