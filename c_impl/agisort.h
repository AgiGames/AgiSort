#ifndef AGISORT_H
#define AGISORT_H

#include <stddef.h>

void agisort(char* input_bytes, size_t input_count, size_t input_size, int (*score) (const void*));

#endif
