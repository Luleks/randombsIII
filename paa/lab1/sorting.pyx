import cython

cdef extern from "sorting_algs.h":
    void c_selection_sort(int* arr, int arr_size)
    void c_heap_sort(int* arr, int arr_size)

def selection_sort(int[:] arr):
    c_selection_sort(&arr[0], arr.shape[0])

def heap_sort(int[:] arr):
    c_heap_sort(&arr[0], arr.shape[0])