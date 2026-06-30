#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

void agisort(char* input_bytes, size_t input_count, size_t input_size, int (*score) (const void*)) {
    if (input_count < 2) return;

    char* min_ele_bytes = input_bytes;
    char* max_ele_bytes = input_bytes;
    for (size_t i = 1; i < input_count; ++i) {
        char* ith_ele_bytes = input_bytes + (i * input_size);
        if (score(ith_ele_bytes) < score(min_ele_bytes)) {
            min_ele_bytes = ith_ele_bytes;
        }
        if (score(ith_ele_bytes) > score(max_ele_bytes)) {
            max_ele_bytes = ith_ele_bytes;
        }
    }

    // printf("%d\n", (*(int*)(max_ele_bytes)));

    if (score(min_ele_bytes) == score(max_ele_bytes)) {
        return;
    }
    
    Heap* heaps = (Heap*) malloc(sizeof(Heap) * input_count);
    for (size_t i = 0; i < input_count; ++i) {
        heap_init(heaps + i, NULL, 0, input_size, score);
    }

    for (size_t i = 0; i < input_count; ++i) {
        char* ith_ele_bytes = input_bytes + (i * input_size);
        size_t scaled_idx = ((score(ith_ele_bytes) - score(min_ele_bytes)) / (score(max_ele_bytes) - score(min_ele_bytes))) * (input_count - 1);
        heap_push_impl(heaps + scaled_idx, ith_ele_bytes);
    }

    size_t j = 0;
    for (size_t i = 0; i < input_count; ++i) {
        Heap* heap = heaps + i;
        while(heap->count > 0) {
            char* popped_bytes = heap_pop_impl(heap);
            memcpy(input_bytes + (j * input_size), popped_bytes, input_size);
            j += 1;
            free(popped_bytes);
        }
        heap_free(heap);
    }
    
    free(heaps);
}

