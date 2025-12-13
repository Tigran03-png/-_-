#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void bubbleSort(int a[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}


void selectionSort(int a[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        int temp = a[i];
        a[i] = a[min_idx];
        a[min_idx] = temp;
    }
}


void quickSort(int a[], int low, int high) {
    if (low >= high) return;
    int pivot = a[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
        }
    }
    int temp = a[i];
    a[i] = a[high];
    a[high] = temp;

    quickSort(a, low, i - 1);
    quickSort(a, i + 1, high);
}


int* generate_array(int size) {
    int* arr = malloc(size * sizeof(int));
    for (int i=0; i<size; i++) {
        arr[i] = rand() % 100000;
    }
    return arr;
}


int* copy_array(int* arr, int size) {
    int* new_arr = malloc(size * sizeof(int));
    for (int i=0; i<size; i++) new_arr[i] = arr[i];
    return new_arr;
}

int main() {
    int sizes[] = {10, 1000, 10000, 100000};
    int count = 4;
    printf("%-10s %-15s %-15s %-15s\n", "Размер", "Время пузырь", "Время выбрать", "Время быстрая");
    for (int i=0; i<count; i++) {
        int size = sizes[i];
        int* original = generate_array(size);


        int* arr_bubble = copy_array(original, size);
        clock_t start = clock();
        bubbleSort(arr_bubble, size);
        double time_bubble = (double)(clock() - start) / CLOCKS_PER_SEC;
        free(arr_bubble);


        int* arr_select = copy_array(original, size);
        start = clock();
        selectionSort(arr_select, size);
        double time_select = (double)(clock() - start) / CLOCKS_PER_SEC;
        free(arr_select);


        int* arr_quick = copy_array(original, size);
        start = clock();
        quickSort(arr_quick, 0, size - 1);
        double time_quick = (double)(clock() - start) / CLOCKS_PER_SEC;
        free(arr_quick);
        free(original);

        printf("%-10d %-15f %-15f %-15f\n", size, time_bubble, time_select, time_quick);
    }

    return 0;
}