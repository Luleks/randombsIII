import cython

cdef extern from "stdlib.h":
    void* malloc(size_t size)
    void* realloc(void* ptr, size_t size)
    void free(void* ptr)

cdef extern from "sorting_algs.h":
    void c_selection_sort(int* arr, int arr_size)
    void c_heap_sort(int* arr, int arr_size)
    void c_bucket_sort(int* arr, int arr_size)

def selection_sort(int[:] arr):
    c_selection_sort(&arr[0], arr.shape[0])

def heap_sort(int[:] arr):
    c_heap_sort(&arr[0], arr.shape[0])

def bucket_sort(int[:] arr):
    c_bucket_sort(&arr[0], arr.shape[0])