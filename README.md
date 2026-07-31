# AgiSort
A novel average case O(n) sorting algorithm.

## Python Installation
```
pip install agisort
```

## C Installation
```
git clone git@github.com:AgiGames/AgiSort.git
```
To compile file ```main.c``` that uses agisort:
```
gcc .\main.c .\c_impl\agisort.c .\c_impl\heap.c -I.\c_impl\ -o main
```

## C Usage
```C
#include <agisort.h>
#include <stdio.h>

int score(const void* a) {
    int a_int = *((int*) a);
    return a_int;   
}

int main() {
    int array[10] = {
        23, 10, 11, 2, 4, 9, 56, 21, 0, 0
    };

    agisort((char*) array, 10, sizeof(int), score);

    for (size_t i = 0; i < 10; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
```

## Python Usage
```python
from agisort import agisort

array = [
    23, 10, 11, 2, 4, 9, 56, 21, 0, 0
]
array = agisort(array)

print(array)
```
