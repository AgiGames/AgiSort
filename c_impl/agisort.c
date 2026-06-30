#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "heap.h"

void agisort(char* input_bytes, size_t input_count, size_t input_size, int (*score) (const void*)) {
    if (input_count < 2) return;
    
    int max_score = INT_MIN;
    int min_score = INT_MAX;
    for (size_t i = 0; i < input_count; ++i) {
        char* ith_ele_bytes = input_bytes + (i * input_size);
        int ith_ele_score = score(ith_ele_bytes);

        if (ith_ele_score < min_score) {
            min_score = ith_ele_score;
        }
        if (ith_ele_score > max_score) {
            max_score = ith_ele_score;
        }

    }

    if (min_score == max_score) {
        return;
    }
    
    Heap* heaps = (Heap*) malloc(sizeof(Heap) * input_count);
    for (size_t i = 0; i < input_count; ++i) {
        heap_init(heaps + i, NULL, 0, input_size, score);
    }

    for (size_t i = 0; i < input_count; ++i) {
        char* ith_ele_bytes = input_bytes + (i * input_size);
        size_t scaled_idx = floorf(((float) (score(ith_ele_bytes) - min_score) / (max_score - min_score)) * (input_count - 1));
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

