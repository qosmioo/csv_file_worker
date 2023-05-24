#include "sort.h"

void swap (double &a, double &b) {
    double tmp = a;
    a = b;
    b = tmp;
}
void sort_array (double *array, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap (array[j], array[j + 1]);
            }
        }
    }
}
