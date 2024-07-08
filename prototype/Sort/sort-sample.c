#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void quicksort(int arr[], int low, int high);
void mergesort(int arr[], int low, int high);
void bubblesort(int arr[], int n);
void print_array(int arr[], int n);
void swap(int* a, int* b);

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quicksort algorithm
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[low];
        int i = low + 1;
        int j = high;

        while (i <= j) {
            while (i <= high && arr[i] <= pivot) {
                i++;
            }
            while (j >= low && arr[j] > pivot) {
                j--;
            }
            if (i <= j) {
                swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        swap(&arr[low], &arr[j]);

        quicksort(arr, low, j - 1);
        quicksort(arr, j + 1, high);
    }
}

// Mergesort algorithm
void mergesort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);

        int n1 = mid - low + 1;
        int n2 = high - mid;

        int *left = (int *)malloc(n1 * sizeof(int));
        int *right = (int *)malloc(n2 * sizeof(int));

        for (int i = 0; i < n1; i++) {
            left[i] = arr[low + i];
        }
        for (int i = 0; i < n2; i++) {
            right[i] = arr[mid + 1 + i];
        }

        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2) {
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = right[j];
            j++;
            k++;
        }

        free(left);
        free(right);
    }
}

// Bubblesort algorithm
void bubblesort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Function to print an array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5, 2, 8, 3, 1, 6, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int arr1[n], arr2[n], arr3[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = arr[i];
        arr2[i] = arr[i];
        arr3[i] = arr[i];
    }

    printf("Original array: ");
    print_array(arr, n);

    quicksort(arr1, 0, n - 1);
    printf("Sorted array using Quicksort: ");
    print_array(arr1, n);

    mergesort(arr2, 0, n - 1);
    printf("Sorted array using Mergesort: ");
    print_array(arr2, n);

    bubblesort(arr3, n);
    printf("Sorted array using Bubblesort: ");
    print_array(arr3, n);

    return 0;
}
