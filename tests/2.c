#include <stdio.h>
#include <string.h>

void Sort(char *str) {
    int arr['z' - 'a' + 1];
    int len = strlen(str);
    memset(arr, 0, ('z' - 'a' + 1) * sizeof(int));
    for (int i = 0; i < len; ++i) {
        arr[str[i] - 'a'] += 1;
    }
    int it = 0;
    for (int i = 0; i < ('z' - 'a' + 1); ++i) {
        memset(&str[it], 'a' + i, arr[i] * sizeof(char));
        it += arr[i];
    }
}
int main() {
    char str[1000001];
    scanf("%1000000s", str);
    Sort(str);
    printf("%s", str);
    return 0;
}
