#include <stdlib.h>

void c_selection_sort(int* arr, int arr_size) {
    int i, j, min, temp;
    for (i = 0; i < arr_size - 1; i++) {
        min = i;
        for (j = i + 1; j < arr_size; j++)
            if (arr[j] < arr[min]) 
                min = j;
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}


void __heapify(int* arr, int i, int max_len) {
    int length = max_len;
    int element = arr[i], child;
    while (2 * i < length) {
        child = 2 * i;
        if (child + 1 < length && arr[child + 1] > arr[child])
            child += 1;
        if (arr[child] > element) {
            arr[i] = arr[child];
            i = child;
        }
        else
            break;
    }
    arr[i] = element;
}

void __build_heap(int* arr, int arr_size) {
    int i;
    for (i = arr_size / 2 - 1; i >= 0; i--) {
        __heapify(arr, i, arr_size);
    }
}

void c_heap_sort(int* arr, int arr_size) {
    int i, temp;
    __build_heap(arr, arr_size);
    for (i = arr_size - 1; i >= 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        __heapify(arr, 0, i);
    }
}


void __insertion_sort(int* arr, int arr_size) {
    int i, j, temp;
    for (i = 1; i < arr_size; i++) {
        j = i - 1;
        temp = arr[i];
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = temp;
    }
}

void c_bucket_sort(int* arr, int arr_size) {
    int i, arr_max = arr[0];
    int num_buckets, sort_buckets, bucket_range;
    for (i = 1; i < arr_size; i++) {
        if (arr[i] > arr_max)
            arr_max = arr[i];
    }
    if (arr_size > 100 * arr_max) {
        num_buckets = arr_max + 1;
        sort_buckets = 0;
        bucket_range = 1;
    }
    else {
        num_buckets = (arr_size > 100) ? (int)((arr_size / 100.0) + 0.5) + 1 : 1;
        sort_buckets = 1;
        bucket_range = (num_buckets > 1) ? arr_max / (num_buckets - 1) : arr_max + 1;
    }

    int** buckets = (int**)malloc(num_buckets * sizeof(int*));
    for (i = 0; i < num_buckets; i++) {
        buckets[i] = (int*)malloc(150 * sizeof(int));
        for (int j = 0; j < 150; j++)
            buckets[i][j] = 0;
    }
    int* indexes = (int*)malloc(num_buckets * sizeof(int));
    int* sizes = (int*)malloc(num_buckets * sizeof(int));
    for (i = 0; i < num_buckets; i++) {
        indexes[i] = 0;
        sizes[i] = 150;
    }

    for (i = 0; i < arr_size; i++) {
        int bucket = arr[i] / bucket_range;
        if (indexes[bucket] == sizes[bucket]) {
            sizes[bucket] *= 2;
            buckets[bucket] = (int*)realloc(buckets[bucket], sizes[bucket] * sizeof(int));
        }
        buckets[bucket][indexes[bucket]++] = arr[i];
    }

    if (sort_buckets) {
        for (i = 0; i < num_buckets; i++)
            __insertion_sort(buckets[i], indexes[i]);
    }

    int c = 0;
    for (i = 0; i < num_buckets; i++) {
        for (int j = 0; j < indexes[i]; j++) {
            arr[c++] = buckets[i][j];
        }
    }
    
    // for (i = 0; i < num_buckets; i++) {
    //     free(buckets[i]);
    // }
    // free(buckets);
    // free(indexes);
    // free(sizes);
}