#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    3-way quicksort give significantly faster result compare to normal quicksort
    when the total elements (ARR_SIZE) are larger and there are fewer keys element
*/

#define ARR_SIZE 10000
#define HIGHEST_ELEMENT 100

int* createArray(int size);
int* duplicateArray(int* arr, int size);
int compareFunction(const void * a, const void * b);
void swap(int a[], int i, int j);
void qsort2(int a[], int l, int r);
void qsort3(int a[], int l, int r);
void check(int a[], int size);

int main() {
    clock_t start_t, end_t;
    double total_t;

    int* a = createArray(ARR_SIZE);
    int* b = duplicateArray(a, ARR_SIZE);
    int* c = duplicateArray(a, ARR_SIZE);

    // Built-in quicksort
    start_t = clock();
    qsort(a, ARR_SIZE, sizeof(int), compareFunction);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Built-in quicksort: %lf\n", total_t);
    check(a, ARR_SIZE);
    free(a);

    // Normal quicksort
    start_t = clock();
    qsort2(b, 0, ARR_SIZE - 1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("2-way quicksort: %lf\n", total_t);
    check(b, ARR_SIZE);
    free(b);
    
    // 3-way partioning quicksort
    start_t = clock();
    qsort3(c, 0, ARR_SIZE - 1);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("3-way quicksort: %lf\n", total_t);
    check(c, ARR_SIZE);
    free(c);

    return 0;
}

void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void qsort2(int a[], int l, int r) {
    if (r <= l) return;
    int i = l - 1;
    int j = l;
    while(j < r) {
        if (a[j] < a[r]) {
            i++;
            swap(a, i, j);
        }
        j++;
    }
    i++;
    swap(a, i, r);

    qsort2(a, l, i - 1);
    qsort2(a, i + 1, r);
}

void qsort3(int a[], int l, int r) {
    if (r <= l) return;
    int i = l - 1, j = r;
    int p = l, q = r - 1;
    while (i <= r) {
        i++;
        if (i >= j) break;
        if (a[i] >= a[r]) {
            while (j >= l) {
                j--;
                if (i >= j) break;
                if (a[j] <= a[r]) {
                    swap(a, i, j);
                    if (a[i] == a[r]) {
                        swap(a, i, p);
                        p++;
                    }
                    if (a[j] == a[r]) {
                        swap(a, j, q);
                        q--;
                    }
                    break;
                }
            }
        }
    }
    int k;
    swap(a, j, r);
    i--; j++;
    for (k = l; k < p; k++) {
        swap(a, k, i);
        i--;
    }
    for (k = r - 1; k > q; k--) {
        swap(a, k, j);
        j++;
    }
    qsort3(a, l, i);
    qsort3(a, j, r);
}

void check(int a[], int size) {
    int i;
    int correct = 1;
    for (i = 0; i < size - 1; i++) {
        if (a[i] > a[i + 1]) {
            correct = 0;
            break;
        }
    }
    if (correct) {
        printf("Correct!\n");
    } else {
        printf("Incorrect\n");
    }
}

int* createArray(int size) {
    int* arr =  (int *)malloc(size * sizeof(int));
    srand(time(NULL));
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = 1 + rand() % HIGHEST_ELEMENT;
    }
    return arr;
}

int* duplicateArray(int* arr, int size) {
    int* newArr = (int *)malloc(size * sizeof(int));
    int i;
    for (i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    return newArr;
}

int compareFunction(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}