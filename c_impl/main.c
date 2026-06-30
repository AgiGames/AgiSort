#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "agisort.h"

int score(const void* a) {
    int a_int = *((int*) a);
    return a_int;   
}

int main() {
    int array[100] = {
        42, 17, 93, 8, 61, 29, 74, 5, 88, 13,
        56, 99, 2, 67, 35, 81, 14, 90, 23, 49,
        71, 6, 95, 38, 52, 19, 84, 11, 63, 27,
        76, 1, 97, 44, 58, 32, 86, 9, 69, 21,
        79, 4, 91, 40, 54, 16, 82, 25, 65, 30,
        73, 7, 98, 46, 59, 34, 87, 10, 68, 22,
        80, 3, 92, 41, 55, 18, 83, 26, 64, 31,
        75, 12, 96, 45, 57, 33, 85, 15, 70, 24,
        78, 0, 94, 39, 53, 20, 89, 28, 66, 36,
        77, 37, 60, 43, 62, 47, 72, 48, 50, 51
    };
    agisort((char*) array, 100, sizeof(int), score);

    for (size_t i = 0; i < 100; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");


    return 0;
}
