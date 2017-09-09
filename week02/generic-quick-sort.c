/*
    The qsort2() and qsort3() implementations in this file has not been optimized
    to be a fully generic function.
    Need to find a way to pass the array member into the compare function as
    a generic variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 10000
#define HIGHEST_ELEMENT 100

int* createArray(int size);
int* duplicateArray(int* arr, int size);
int compareFunction(const void * a, const void * b);
void swap(void * a, int i, int j);
void qsort2(void * a, int l, int r, int(*compare)(const void*, const void*));
void qsort3(void * a, int l, int r, int(*compare)(const void*, const void*));
void check(void * a, int size, int(*compare)(const void*, const void*));

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
    check(a, ARR_SIZE, compareFunction);
    free(a);

    // Normal quicksort
    start_t = clock();
    qsort2(b, 0, ARR_SIZE - 1, compareFunction);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("2-way quicksort: %lf\n", total_t);
    check(b, ARR_SIZE, compareFunction);
    free(b);
    
    // 3-way partioning quicksort
    start_t = clock();
    qsort3(c, 0, ARR_SIZE - 1, compareFunction);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("3-way quicksort: %lf\n", total_t);
    check(c, ARR_SIZE, compareFunction);
    free(c);

    return 0;
}

void swap(void* a, int i, int j) {
    int tmp = ((int *)a)[i];
    ((int *)a)[i] = ((int *)a)[j];
    ((int *)a)[j] = tmp;
}

void qsort2(void * a, int l, int r, int(*compare)(const void*, const void*)) {
    if (r <= l) return;
    int i = l - 1;
    int j = l;
    while(j < r) {
        if (compare( &((int *)a)[j], &((int *)a)[r] ) < 0) {
            i++;
            swap(a, i, j);
        }
        j++;
    }
    i++;
    swap(a, i, r);

    qsort2(a, l, i - 1, compareFunction);
    qsort2(a, i + 1, r, compareFunction);
}

void qsort3(void * a, int l, int r, int(*compare)(const void*, const void*)) {
    if (r <= l) return;
    int i = l - 1, j = r;
    int p = l, q = r - 1;
    while (i <= r) {
        i++;
        if (i >= j) break;
        if (compare( &((int *)a)[i], &((int *)a)[r] ) >= 0) {
            while (j >= l) {
                j--;
                if (i >= j) break;
                if (compare( &((int *)a)[j], &((int *)a)[r] ) <= 0) {
                    swap(a, i, j);
                    if (compare( &((int *)a)[i], &((int *)a)[r] ) == 0) {
                        swap(a, i, p);
                        p++;
                    }
                    if (compare( &((int *)a)[j], &((int *)a)[r] ) == 0) {
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
    qsort3(a, l, i, compareFunction);
    qsort3(a, j, r, compareFunction);
}

void check(void * a, int size, int(*compare)(const void*, const void*)) {
    int i;
    int correct = 1;
    for (i = 0; i < size - 1; i++) {
        if (compare ( &(((int *)a)[i]), &((int *)a)[i + 1] ) > 0) {
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