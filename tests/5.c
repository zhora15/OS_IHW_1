#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define PART 100
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int main() {
    int n, l, r, it, v, res;
    char req[4];
    scanf("%d", &n);
    int *inp = malloc(n * sizeof(int));
    int *arr = n / PART ? malloc((n / PART) * sizeof(int)) : NULL;
    if (n / PART) {
        for(int i=0; i<n/PART;++i){
            arr[i] = INT_MIN;
        }
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &inp[i]);
        if ((n / PART) && (i < (n / PART) * PART)) {
            arr[i / PART] = arr[i / PART] > inp[i] ? arr[i / PART] : inp[i];
        }
    }
    scanf("%3s", req);
    while (strcmp(req, "END")) {
        if (!strcmp(req, "UPD")) {
            scanf("%d%d", &it, &v);
            inp[it] = v;
            if (it < n/PART*PART){
                arr[it/PART] = inp[it/PART * PART];
                for (int i = it/PART * PART; i < (it/PART+1)*PART; ++i){
                    arr[it/PART] = MAX(arr[it/PART], inp[i]);
                }
            }

        } else if (!strcmp(req, "MAX")) {
            scanf("%d%d", &l, &r);
            res = INT_MIN;

            for (int i = (l + PART - 1) / PART; i <= (r - PART) / PART; ++i) {
                res = MAX(arr[i], res);
            }
            int l_limit = ((l + PART - 1) / PART) * PART - 1 > r ? r : ((l + PART - 1) / PART) * PART - 1;
            for (int i = l; i <= l_limit; ++i) {
                res = MAX(res, inp[i]);
            }
            int r_start = l_limit == r ? r : (r / PART) * PART;
            for (int i = r_start; i <= r; ++i) {
                res = MAX(res, inp[i]);
            }
            //printf("%d %d %d %d\n", l, l_limit, r_start, r);
            printf("%d\n", res);
        }
        scanf("%3s", req);
    }
    free(inp);
    free(arr);
}