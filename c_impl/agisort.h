#ifndef AGISORT_H
#define AGISORT_H

#include <stddef.h>

void agisort(char* input_bytes, size_t input_count, size_t input_size, double (*score) (const void*));

#endif
