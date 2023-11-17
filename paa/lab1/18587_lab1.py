import random
import time
import tracemalloc
from typing import Callable, List
from functools import wraps


sorting_algs = [
    'selection_sort',
    'heap_sort',
    'bucket_sort'
]

max_len_sort_name = len(max(sorting_algs, key=lambda name: len(name)))
max_digits_before_point = 5
upper_range = 10_000


def space_time_monitor(func: Callable) -> None:
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
                 f'da sortira niz velicicne {len(arr)} '\
                 f'pri cemu je utroseno {(mem_used[1]/1024):.8f}KB memorije\n'

        return report, arr == sorted(arr)
    
    return wrap


@space_time_monitor
def selection_sort(arr: List[int]) -> List[int]:
    for i in range(len(arr) - 1):
        min = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min]:
                min = j
        arr[i], arr[min] = arr[min], arr[i]   
    return arr


def __heapify(arr: List[int], i: int, max_len: int=None) -> None:
    length = max_len or len(arr)
    element = arr[i]
    while 2 * i + 1 < length:
        child = 2 * i + 1
        if child + 1 < length and arr[child + 1] > arr[child]:
            child += 1
        if arr[child] > element:
            arr[i] = arr[child]
            i = child
        else:
            break
    arr[i] = element

def __build_heap(arr: List[int]) -> None:
    for i in range(len(arr) // 2 - 1, -1, -1):
        __heapify(arr, i)

@space_time_monitor
def heap_sort(arr: List[int]) -> List[int]:
    __build_heap(arr)
    for i in range(len(arr) - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        __heapify(arr, 0, i)
    return arr


def __insertion_sort(arr: List[int]) -> None:
    for i in range(1, len(arr)):
        j = i - 1
        tmp = arr[i]
        while j >= 0 and arr[j] > tmp:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = tmp

@space_time_monitor
def bucket_sort(arr: List[int]) -> List[int]:
    arr_max = max(arr)
    if len(arr) > 100 * arr_max:
        num_buckets = arr_max + 1
        sort_buckets = False
        bucket_range = 1
    else:
        num_buckets = int(round(len(arr) / 100, 0)) + 1 if len(arr) > 100 else 1
        sort_buckets = True
        bucket_range = arr_max // (num_buckets - 1) if num_buckets > 1 else arr_max + 1
                    
    buckets = {i: [] for i in range(num_buckets)}

    for num in arr:
        buckets[num // bucket_range].append(num)

    if sort_buckets:
        for bucket in buckets.values():
            __insertion_sort(bucket)

    for i in range(1, num_buckets):
        buckets[0].extend(buckets[i])
    
    return buckets[0]


def generate_report(arrs: List, sorting_algs: Callable) -> None:

    with open('report.txt', 'w+') as f:
        for arr in arrs:
            for sort_alg in sorting_algs:
                if sort_alg.__name__ == 'selection_sort' and len(arr) > 100_000:
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
    sorts = [selection_sort, heap_sort, bucket_sort]
    generate_report(arrs, sorts)
