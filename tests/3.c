#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *merge(int *arr1, int *arr2, int n1, int n2) {
    int *arr = malloc((n1 + n2) * sizeof(int));
    int i = 0, j = 0;
    int k = 0;
    while ((i < n1) && (j < n2)) {
        if (arr1[i] <= arr2[j]) {
            arr[k] = arr1[i];
            i++;
        } else {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    if (i < n1) {
        memcpy(&arr[k], &arr1[i], (n1 - i) * sizeof(int));
    }
    if (j < n2) {
        memcpy(&arr[k], &arr2[j], (n2 - j) * sizeof(int));
    }
    free(arr1);
    free(arr2);
    return arr;
}

int main() {
    int n;
    scanf("%d", &n);
    int **seq = malloc(n * sizeof(int *));
    int *size_arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        scanf("%d", &size_arr[i]);
        seq[i] = malloc(size_arr[i] * sizeof(int));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < size_arr[i]; ++j) {
            scanf("%d", &seq[i][j]);
        }
    }

    while (n != 1) {
        for (int i = 0; i < n / 2; ++i) {
            seq[i] = merge(seq[2 * i], seq[2 * i + 1], size_arr[2 * i], size_arr[2 * i + 1]);
            size_arr[i] = size_arr[2 * i] + size_arr[2 * i + 1];
        }
        if (n%2){
            seq[n/2] = seq[n-1];
            size_arr[n/2] = size_arr[n-1];
        }
        n = (n + 1) / 2;
    }
    for (int i = 0; i < size_arr[0]; ++i) {
        printf("%d ", seq[0][i]);
    }

    free(seq[0]);
    free(seq);
    free(size_arr);

    return 0;
}
