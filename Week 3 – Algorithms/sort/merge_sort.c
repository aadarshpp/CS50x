#include <stdlib.h>

void merge_sort_range(int* array, int left, int right);

void merge(int* array, int left, int mid, int right);

// Entry point for merge sort; sorts the entire array
void merge_sort(int* array, int size)
{
    merge_sort_range(array, 0, size - 1);
}

// Recursively sorts the array within the index range [left, right] using merge sort
void merge_sort_range(int* array, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    merge_sort_range(array, left, mid);
    merge_sort_range(array, mid + 1, right);

    merge(array, left, mid, right);
}

// Merges two sorted halves of the array: [left, mid] and [mid + 1, right]
void merge(int* array, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*) malloc(n1 * sizeof(int));
    int* R = (int*) malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = array[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
            array[k++] = L[i++];
        else
            array[k++] = R[j++];
    }

    while (i < n1)
        array[k++] = L[i++];
    while (j < n2)
        array[k++] = R[j++];

    free(L);
    free(R);
}
