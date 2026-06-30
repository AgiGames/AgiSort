from typing import List
import heapq
import math

def agisort(unsorted_array: List[int]) -> List[int]:
    n = len(unsorted_array)
    min_num = min(unsorted_array)
    max_num = max(unsorted_array)
    if max_num == min_num:
        return unsorted_array
    
    buckets = [[] for _ in range(n)]

    for num in unsorted_array:
        i = math.floor(((num - min_num) / (max_num - min_num)) * (n - 1))
        heapq.heappush(buckets[i], num)
    
    result = []
    for heap in buckets:
        while heap:
            number = heapq.heappop(heap)
            result.append(number)
    
    return result

unsorted_array = [12, 11, 13, 5, 6]
sorted_array = agisort(unsorted_array)
print(sorted_array)