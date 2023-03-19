#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int x, size = 0, cap = 4;
    char req[6];
    int readIndex = 0, writeIndex = 0;
    int *arr = malloc(cap * sizeof(int));

    scanf("%5s", req);
    while (strcmp(req, "END")){
        if (!strcmp(req, "EMPTY")){
            if (size){
                printf("false\n");
            } else {
                printf("true\n");
            }
        } else if (!strcmp(req, "ENQ")){
            scanf("%d", &x);
            if (size == cap){
                cap*=2;
                arr = realloc(arr, cap * sizeof(int));
                memcpy(&arr[size], arr, readIndex* sizeof(int));
                writeIndex = size + readIndex;
            }
            arr[writeIndex++] = x;
            if (writeIndex == cap){
                writeIndex = 0;
            }
            ++size;
        } else if (!strcmp(req, "DEQ")){
            printf("%d\n", arr[readIndex++]);
            if (readIndex == cap){
                readIndex = 0;
            }
            --size;
        }
        scanf("%5s", req);
    }
    free(arr);
    return 0;
}
