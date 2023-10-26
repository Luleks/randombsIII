// def bucket_sort(arr: List[int]) -> List[int]:
//     arr_max = max(arr)
//     if len(arr) > 100 * arr_max:
//         num_buckets = arr_max + 1
//         sort_buckets = False
//         bucket_range = 1
//     else:
//         num_buckets = int(round(len(arr) / 100, 0)) + 1 if len(arr) > 100 else 1
//         sort_buckets = True
//         bucket_range = arr_max // (num_buckets - 1) if num_buckets > 1 else arr_max + 1
                    
//     buckets = {i: [] for i in range(num_buckets)}

//     for num in arr:
//         buckets[num // bucket_range].append(num)

//     if sort_buckets:
//         for bucket in buckets.values():
//             __insertion_sort(bucket)

//     for i in range(1, num_buckets):
//         buckets[0].extend(buckets[i])
    
//     return buckets[0]

void bucket_sort(int* arr, int arr_size) {
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

    
}