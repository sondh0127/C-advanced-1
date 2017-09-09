#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jval.h"

#define ARR_SIZE 10000
#define HIGHEST_ELEMENT 100

Jval * createArray(int size);
void swap(Jval * a, int i, int j);
int compareFunction(Jval * a, Jval * b);
void qsort2(Jval * a, int l, int r, int(*compare)(Jval *, Jval *));
void qsort3(Jval * a, int l, int r, int(*compare)(Jval *, Jval *));
void check(Jval * a, int size, int(*compare)(Jval *, Jval *));

int main() {
    clock_t start_t, end_t;
    double total_t;

    Jval * a = createArray(ARR_SIZE);
    Jval * b = (Jval *)malloc(ARR_SIZE * sizeof(Jval));

    memcpy(b, a, ARR_SIZE * sizeof(Jval));

    // Normal quicksort
    start_t = clock();
    qsort2(a, 0, ARR_SIZE - 1, compareFunction);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("2-way quicksort: %lf\n", total_t);
    check(a, ARR_SIZE, compareFunction);
    free(a);
    
    // 3-way partioning quicksort
    start_t = clock();
    qsort3(b, 0, ARR_SIZE - 1, compareFunction);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("3-way quicksort: %lf\n", total_t);
    check(b, ARR_SIZE, compareFunction);
    free(b);

    return 0;
}

Jval * createArray(int size) {
    Jval * arr =  (Jval *)malloc(size * sizeof(Jval));
    srand(time(NULL));
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = new_jval_i(1 + rand() % HIGHEST_ELEMENT);
    }
    return arr;
}

void swap(Jval * a, int i, int j) {
    Jval tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int compareFunction(Jval * a, Jval * b) {
    return jval_i(*a) - jval_i(*b);
}

void qsort2(Jval * a, int l, int r, int(*compare)(Jval *, Jval *)) {
    if (r <= l) return;
    int i = l - 1;
    int j = l;
    while(j < r) {
        if (compare(&a[j], &a[r]) < 0) {
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

void qsort3(Jval * a, int l, int r, int(*compare)(Jval *, Jval *)) {
    if (r <= l) return;
    int i = l - 1, j = r;
    int p = l, q = r - 1;
    while (i <= r) {
        i++;
        if (i >= j) break;
        if (compare(&a[i], &a[r]) >= 0) {
            while (j >= l) {
                j--;
                if (i >= j) break;
                if (compare(&a[j], &a[r]) <= 0) {
                    swap(a, i, j);
                    if (compare(&a[i], &a[r]) == 0) {
                        swap(a, i, p);
                        p++;
                    }
                    if (compare(&a[j], &a[r]) == 0) {
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

void check(Jval * a, int size, int(*compare)(Jval *, Jval *)) {
    int i;
    int correct = 1;
    for (i = 0; i < size - 1; i++) {
        if (compare(&a[i], &a[i + 1]) > 0) {
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