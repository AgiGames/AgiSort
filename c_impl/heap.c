#include <stdbool.h>
#include <malloc.h>

#include "heap.h"

char* _heap_popped_bytes = NULL;

void iter_heapify(size_t i, Heap *heap) {
    char *temp = (char*) malloc(heap->item_size);

    while(true) {
        size_t left_idx = 2 * i + 1;
        size_t right_idx = 2 * i + 2;

        int smallest_idx = i;
        if (right_idx < heap->count && heap->score(heap->items + (right_idx * heap->item_size)) < heap->score(heap->items + (smallest_idx * heap->item_size)))  {
            smallest_idx = right_idx;
        }

        if (left_idx < heap->count && heap->score(heap->items + (left_idx * heap->item_size)) < heap->score(heap->items + (smallest_idx * heap->item_size))) {
            smallest_idx = left_idx;
        }

        if (smallest_idx == i) break;

        memcpy(temp, heap->items + (smallest_idx * heap->item_size), heap->item_size);
        memcpy(heap->items + (smallest_idx * heap->item_size),
               heap->items + (i * heap->item_size),
               heap->item_size);
        memcpy(heap->items + (i * heap->item_size),
               temp,
               heap->item_size);

        i = smallest_idx;
    }

    free(temp);
}

void heap_build_impl(Heap* heap) {
    for (int i = heap->count - 1; i >= 0; i--) {
        iter_heapify(i, heap);
    }
}

void heap_push_impl(Heap* heap, char* bytes) {
    HEAP_APPEND_BYTES_IMPL(heap, bytes);
    int i = heap->count - 1;
    char *temp = (char*) malloc(heap->item_size);

    while (i > 0) {
        int parent_idx = ((i - 1) / 2);
        if (parent_idx < 0) break;
        if (heap->score(heap->items + (parent_idx * heap->item_size)) <= heap->score(heap->items + (i * heap->item_size))) break;
            

        memcpy(temp, heap->items + (parent_idx * heap->item_size), heap->item_size);
        memcpy(heap->items + (parent_idx * heap->item_size),
               heap->items + (i * heap->item_size),
               heap->item_size);
        memcpy(heap->items + (i * heap->item_size),
               temp,
               heap->item_size);

        i = parent_idx;
    }

    free(temp);
}

void heap_append_impl(Heap* heap, char* bytes) {
    HEAP_APPEND_BYTES_IMPL(heap, bytes)
}

char* heap_pop_impl(Heap* heap) {
    int last_index = heap->count - 1;
    if (last_index < 0) return NULL;

    char* top_ele_bytes = (char*) malloc(heap->item_size);
    memcpy(top_ele_bytes, heap->items, heap->item_size);
    memcpy(heap->items, heap->items + (last_index * heap->item_size), heap->item_size);
    heap->count -= 1;

    iter_heapify(0, heap);
    return top_ele_bytes;
}

void heap_init(Heap* heap, char* items_bytes, size_t count, size_t item_size, int (*score) (const void*)) {
    heap->items = items_bytes;
    heap->count = count;
    heap->capacity = count;
    heap->item_size = item_size;
    heap->score = score;
}

void heap_free(Heap* heap) {
    free(heap->items);
}

