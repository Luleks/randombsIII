import random
import time
import tracemalloc
from typing import Callable, List
from functools import wraps
import math


sorting_algs = [
    'insertion_sort',
    'selection_sort',
    'bubble_sort',
    'merge_sort',
    'heap_sort',
    'quick_sort',
    'bucket_sort',
    'counting_sort',
    'radix_sort'
]

max_len_sort_name = len(max(sorting_algs, key=lambda name: len(name)))
max_digits_before_point = 5
upper_range = 10_000


def space_time_monitor(func: Callable):
    @wraps(func)
    def wrap(arr: List):
        start_time = time.perf_counter()
        tracemalloc.start()

        arr = func(arr)

        mem_used = tracemalloc.get_traced_memory()
        tracemalloc.stop()

        end_time = time.perf_counter()
        total_time = str(round(end_time - start_time, 8))
        point = total_time.find('.')
        whole_part = f'{" " * (max_digits_before_point - len(total_time[:point]))}{total_time[:point]}'
        decimal_part = total_time[point:]
        decimal_part = f'{decimal_part}{"0" * (8 - len(decimal_part))}' 

        report = f'Algoritmu {" " * (max_len_sort_name - len(func.__name__))}'\
                 f'{func.__name__} je bilo potrebno {whole_part}{decimal_part}s '\
                 f'da sortira nize velicicne {len(arr)} '\
                 f'pri cemu je utroseno {(mem_used[1]/1024):.8f}KB memorije\n'

        return report, all(arr[i] <= arr[i + 1] for i in range(len(arr) - 1))
    
    return wrap


@space_time_monitor
def insertion_sort(arr: List):
    for i in range(1, len(arr)):
        j = i - 1
        tmp = arr[i]
        while j >= 0 and arr[j] > tmp:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = tmp
    return arr


@space_time_monitor
def bubble_sort(arr: List):
    for i in range(len(arr)):
        change = False
        for j in range(len(arr) - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                change = True
        if not change:
            break
    return arr


@space_time_monitor
def selection_sort(arr: List):
    for i in range(len(arr) - 1):
        min = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min]:
                min = j
        arr[i], arr[min] = arr[min], arr[i]   
    return arr        


def __heapify(arr: List, i: int, max_len: int=None):
    length = max_len or len(arr)
    element = arr[i]
    while 2 * i < length:
        child = 2 * i
        if child + 1 < length and arr[child + 1] > arr[child]:
            child += 1
        if arr[child] > element:
            arr[i] = arr[child]
            i = child
        else:
            break
    arr[i] = element

def __build_heap(arr: List):
    for i in range(len(arr) // 2 - 1, -1, -1):
        __heapify(arr, i)

@space_time_monitor
def heap_sort(arr: List):
    __build_heap(arr)
    for i in range(len(arr) - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        __heapify(arr, 0, i)
    return arr


def __partition(arr, l, r):
    i, j = l, l
    while j != r:
        if arr[j] < arr[r]:
            arr[i], arr[j] = arr[j], arr[i]
            i, j = i + 1, j + 1
        else:
            j += 1
    arr[i], arr[r] = arr[r], arr[i]
    return i

def __quick_sort(arr, l, r):
    if l < r:
        q = __partition(arr, l, r)
        __quick_sort(arr, l, q - 1)
        __quick_sort(arr, q + 1, r)

@space_time_monitor
def quick_sort(arr: List):
    __quick_sort(arr, 0, len(arr) - 1)
    return arr


@space_time_monitor
def counting_sort(arr: List):
    aux = [0] * (upper_range + 1)
    ret = [0] * len(arr)
    for element in arr:
        aux[element] += 1
    
    for i in range(1, len(aux)):
        aux[i] += aux[i - 1]
    
    for i in range(len(arr) - 1, -1, -1):
        ret[aux[arr[i]] - 1] = arr[i]
        aux[arr[i]] -= 1

    return ret


def __insertion_sort(arr: List):
    for i in range(1, len(arr)):
        j = i - 1
        tmp = arr[i]
        while j >= 0 and arr[j] > tmp:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = tmp

@space_time_monitor
def bucket_sort(arr: List):
    arr = list(map(lambda num: num / upper_range * (len(arr) // 10), arr))
    buckets = {i: [] for i in range(len(arr) // 10 + 1)}

    for num in arr:
        buckets[int(num)].append(num)

    for bucket in buckets.values():
        __insertion_sort(bucket)

    for i in range(1, len(arr) // 10 + 1):
        buckets[0].extend(buckets[i])
    
    return list(map(lambda num: num / (len(arr) // 10) * upper_range, buckets[0]))


def __counting_sort(arr: List, exp, r):
    ret = [0] * len(arr)
    aux = [0] * (2 ** r)

    for num in arr:
        index = (num >> exp) & (2 ** r - 1)
        aux[index] += 1

    for i in range(1, 2 ** r):
        aux[i] += aux[i - 1]

    i = len(arr) - 1
    while i >= 0:
        index = (arr[i] >> exp) & (2**r - 1)
        ret[aux[index] - 1] = arr[i]
        aux[index] -= 1
        i -= 1
    
    return ret

@space_time_monitor
def radix_sort(arr: List):
    n = len(arr)
    b = 32 # upper_range.bit_count()
    if b < math.floor(math.log2(n)):
        r = b
    else:
        r = math.floor(math.log2(n))
    
    exp = 0

    while (upper_range >> exp) > 0:
        arr = __counting_sort(arr, exp, r)
        exp += r
    
    return arr


def generate_report(arrs: List, sorting_algs: Callable):
    with open('report.txt', 'w') as f:
        for arr in arrs:
            for sort_alg in sorting_algs:
                if len(arr) > 10_000 and sort_alg.__name__ in {'selection_sort', 'insertion_sort', 'bubble_sort'}:
                    continue

                report, sort_is_valid = sort_alg(arr.copy())

                if not sort_is_valid:
                    print(f'Algoritam {sort_alg.__name__} nije zavrsio sa sortiranjem niza od {len(arr)} elemenata')
                else:
                    print(f'Algoritam {sort_alg.__name__} je zavrsio sa sortiranjem niza od {len(arr)} elemenata')

                f.write(report)

            f.write('-' * 50 + '\n')


if __name__ == '__main__':
    arr_100 = [random.randint(0, upper_range) for _ in range(100)]
    arr_1000 = [random.randint(0, upper_range) for _ in range(1000)]
    arr_10_000 = [random.randint(0, upper_range) for _ in range(10_000)]
    arr_100_000 = [random.randint(0, upper_range) for _ in range(100_000)]
    arr_1_000_000 = [random.randint(0, upper_range) for _ in range(1_000_000)]
    arr_10_000_000 = [random.randint(0, upper_range) for _ in range(10_000_000)]

    arrs = [arr_100, arr_1000, arr_10_000, arr_100_000, arr_1_000_000, arr_10_000_000]
    sorts = [insertion_sort, bubble_sort, selection_sort, heap_sort, quick_sort, counting_sort, bucket_sort, radix_sort]
    generate_report(arrs, sorts)
