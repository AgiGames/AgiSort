import math
import heapq
from typing import List, Callable

def agisort(input_list: List[int], score: Callable[[object], int] = lambda x: x) -> List[int]:
    n = len(input_list)
    min_score = min(score(x) for x in input_list)
    max_score = max(score(x) for x in input_list)
    if min_score == max_score:
        return input_list
    
    heaps = [[] for _ in range(n)]

    for ith_element in input_list:
        ith_score = score(ith_element)
        i = math.floor(((ith_score - min_score) / (max_score - min_score)) * (n - 1))
        heapq.heappush(heaps[i], (ith_score, ith_element))
    
    i = 0
    for heap in heaps:
        while heap:
            ith_score, ith_element = heapq.heappop(heap)
            input_list[i] = ith_element
            i += 1
    
    return input_list