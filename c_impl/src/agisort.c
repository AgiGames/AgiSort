#include <float.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <heap.h>
#include <heaps_manager.h>

void agisort(char* input_bytes, size_t input_count, size_t item_size, double (*score) (const void*)) {
    if (input_count < 2) return;
    
    double* scores = calloc(input_count, sizeof(double));
    double max_score = score(input_bytes);
    double min_score = max_score;
    scores[0] = max_score;
    for (size_t i = 1; i < input_count; ++i) {
        char* ith_ele_bytes = input_bytes + (i * item_size);
        double ith_ele_score = score(ith_ele_bytes);
        scores[i] = ith_ele_score;

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
    
    HeapsManager hm;
    size_t* heap_capacities = calloc(input_count, sizeof(size_t));
    double denom = (max_score - min_score);
    double scaler = input_count - 1;
    for (size_t i = 0; i < input_count; ++i) {
        size_t scaled_idx = ((scores[i] - min_score) / denom) * scaler;
        heap_capacities[scaled_idx] += 1;
    }

    hm_init(&hm, heap_capacities, input_count, item_size, score);
    for (size_t i = 0; i < input_count; ++i) {
        char* ith_ele_bytes = input_bytes + (i * item_size);
        size_t scaled_idx = ((scores[i] - min_score) / denom) * scaler;
        hm_push(&hm, scaled_idx, ith_ele_bytes);
    }

    size_t j = 0;
    for (size_t i = 0; i < input_count; ++i) {
        Heap* heap = hm_get_heap(&hm, i);
        while(heap->count > 0) {
            char* popped_bytes = heap_pop_impl(heap);
            memcpy(input_bytes + (j * item_size), popped_bytes, item_size);
            j += 1;
            free(popped_bytes);
        }
    }

    free(scores);
    free(heap_capacities);
    hm_free(&hm);
}

