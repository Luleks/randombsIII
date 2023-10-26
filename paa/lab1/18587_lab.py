import random
import time
import tracemalloc
from typing import Callable, List
from functools import wraps
import sorting
import array


sorting_algs = [
    'selection_sort',
    'heap_sort',
    'bucket_sort'
]

max_len_sort_name = len(max(sorting_algs, key=lambda name: len(name)))
max_digits_before_point = 4
upper_range = 10_000


def space_time_monitor(func: Callable) -> None:
    @wraps(func)
    def wrap(arr: List):
        start_time = time.perf_counter()
        tracemalloc.start()

        func(arr)

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
def selection_sort(arr: array.array):
    sorting.selection_sort(arr)

@space_time_monitor
def heap_sort(arr: array.array):
    sorting.heap_sort(arr)

def generate_report(arrs: List, sorting_algs: Callable) -> None:


    with open('report.txt', 'a+') as f:
        for arr in arrs:
            for sort_alg in sorting_algs:
                if sort_alg.__name__ == 'selection_sort' and len(arr) > 100_000:
                    continue

                report, sort_is_valid = sort_alg(array.array(arr.typecode, arr))

                if not sort_is_valid:
                    print(f'Algoritam {sort_alg.__name__} nije zavrsio sa sortiranjem niza od {len(arr)} elemenata')
                else:
                    print(f'Algoritam {sort_alg.__name__} je zavrsio sa sortiranjem niza od {len(arr)} elemenata')

                f.write(report)

            f.write('-' * 50 + '\n')


if __name__ == '__main__':
    arr_100 = array.array('i', [random.randint(0, upper_range) for _ in range(100)])
    arr_1000 = array.array('i', [random.randint(0, upper_range) for _ in range(1000)])
    arr_10_000 = array.array('i', [random.randint(0, upper_range) for _ in range(10_000)])
    arr_100_000 = array.array('i', [random.randint(0, upper_range) for _ in range(100_000)])
    # arr_1_000_000 = array.array('i', [random.randint(0, upper_range) for _ in range(1_000_000)])
    # arr_10_000_000 = array.array('i', [random.randint(0, upper_range) for _ in range(10_000_000)])

    arrs = [arr_100, arr_1000, arr_10_000, arr_100_000]
    sorts = [selection_sort, heap_sort]
    generate_report(arrs, sorts)
