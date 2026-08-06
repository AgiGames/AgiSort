#include <heap.h>
#include <heaps_manager.h>

#include <stdlib.h>

void hm_init(HeapsManager* hm, size_t* heap_capacities, size_t heap_count, size_t item_size, double (*score)(const void *)) {
    hm->capacities = heap_capacities;
    hm->count = heap_count;
    hm->heaps = calloc(heap_count, sizeof(Heap));
    hm->offsets = calloc(heap_count, sizeof(size_t));

    size_t heap_capacities_sum = heap_capacities[0];
    hm->offsets[0] = 0;
    for (size_t i = 1; i < heap_count; ++i) {
        hm->offsets[i] = heap_capacities_sum * item_size;
        heap_capacities_sum += heap_capacities[i];
    }

    hm->items = calloc(heap_capacities_sum, item_size);
    for (size_t i = 0; i < heap_count; ++i) {
        heap_init_empty(hm->heaps + i, hm->items + hm->offsets[i], hm->capacities[i], item_size, score);
    }
}

void hm_push(HeapsManager *hm, size_t heap_index, char *bytes) {
    Heap* heap = hm->heaps + heap_index;
    heap_push_impl(heap, bytes);
}

char* hm_pop(HeapsManager *hm, size_t heap_index) {
    Heap* heap = hm->heaps + heap_index;
    return heap_pop_impl(heap);
}

Heap* hm_get_heap(HeapsManager *hm, size_t heap_index) {
    return hm->heaps + heap_index;
}

void hm_free(HeapsManager* hm) {
    free(hm->offsets);
    free(hm->heaps);
}
