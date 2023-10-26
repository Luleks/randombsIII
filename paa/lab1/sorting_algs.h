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