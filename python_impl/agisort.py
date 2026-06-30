from typing import List, Callable
import heapq
import math

def agisort(input_list: List[int], score: Callable[[object], int]) -> List[int]:
    n = len(input_list)
    min_score = min(input_list, key=lambda x: score(x))
    max_score = max(input_list, key=lambda x: score(x))
    if min_score == max_score:
        return input_list
    
    heaps = [[] for _ in range(n)]

    for ith_element in input_list:
        i = math.floor(((score(ith_element) - min_score) / (max_score - min_score)) * (n - 1))
        heapq.heappush(heaps[i], ith_element)
    
    i = 0
    for heap in heaps:
        while heap:
            ith_element = heapq.heappop(heap)
            input_list[i] = ith_element
            i += 1
    
    return input_list

def score(num: int):
    return num

unsorted_array = [12, 11, 13, 5, 6]
sorted_array = agisort(unsorted_array, score)
print(sorted_array)