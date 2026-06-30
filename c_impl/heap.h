#ifndef HEAP_H
#define HEAP_H

#include <string.h>
#include <stdlib.h>

typedef struct {
    char* items;
    size_t item_size;
    size_t count;
    size_t capacity;
    int (*score)(const void*);
} Heap;

extern char* _heap_popped_bytes;

#define HEAP_APPEND(xs, T, x) \
    do { \
        const T temp = (x); \
        HEAP_APPEND_BYTES_IMPL((xs), &temp); \
    } while(0);

#define HEAP_APPEND_BYTES_IMPL(xs, x) \
    do { \
        if ((xs)->count >= (xs)->capacity) { \
            if ((xs)->capacity == 0) (xs)->capacity = 256; \
            else (xs)->capacity *= 2; \
            (xs)->items = realloc((xs)->items, (xs)->capacity * (xs)->item_size * sizeof(char)); \
        } \
        memcpy((xs)->items + ((xs)->item_size * (xs)->count), (x), (xs)->item_size); \
        (xs)->count += 1; \
    } while(0);

#define HEAP_PUSH(xs, T, x) \
    do { \
        const T temp = (x); \
        heap_push_impl((xs), (char*) &temp); \
    } while(0);

#define HEAP_BUILD(xs) \
    do { \
        heap_build_impl((xs)); \
    } while(0);

#define HEAP_POP(xs, out_var_name) \
    do { \
        _heap_popped_bytes = heap_pop_impl((xs)); \
        if (_heap_popped_bytes == NULL) { \
            fprintf(stderr, "Heap is empty!\n"); \
            abort(); \
            break; \
        } \
        memcpy(&out_var_name, _heap_popped_bytes, (xs)->item_size); \
        free(_heap_popped_bytes); \
        _heap_popped_bytes = NULL; \
    } while(0);

void heap_build_impl(Heap* heap);
void heap_push_impl(Heap* heap, char* bytes);
void heap_append_impl(Heap* heap, char* bytes);
char* heap_pop_impl(Heap* heap);
void heap_init(Heap* heap, char* items_bytes, size_t count, size_t capacity, int (*score) (const void*));
void heap_free(Heap* heap);

#endif
