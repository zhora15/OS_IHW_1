#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int key;
  int value;
  struct node *next;
} Node;

int main() {
    int m, i, v;
    Node **arr;
    char req[7];

    scanf("%d", &m);
    arr = malloc(m * sizeof(Node *));
    for (int j = 0; j < m; ++j) {
        arr[j] = NULL;
    }
    scanf("%6s", req);
    while (strcmp(req, "END")){
        if (!strcmp(req, "ASSIGN")) {
            scanf("%d%d", &i, &v);

            Node *cur = arr[i % m];
            Node *prev = NULL;
            int flag = 0;
            while ((cur) &&((cur->key ==i) || (cur->next))){
                if (cur->key == i) {
                    if (v) {
                        cur->value = v;
                    } else {
                        if (prev) {
                            prev->next = cur->next;
                        } else {
                            arr[i%m] = cur->next;
                        }
                        free(cur);
                    }
                    flag = 1;
                    break;
                }
                prev = cur;
                cur = cur->next;
            }
            if (!flag) {
                Node *new_node = malloc(sizeof(Node));
                new_node->key = i;
                new_node->value = v;
                new_node->next = NULL;
                if (cur){
                    cur->next = new_node;
                } else {
                    arr[i%m] = new_node;
                }

            }
        } else if (!strcmp(req, "AT")){
            scanf("%d", &i);
            int flag = 0;
            Node *cur = arr[i%m];
            while (cur){
                if (cur->key == i){
                    printf("%d\n", cur->value);
                    flag = 1;
                    break;
                }
                cur = cur->next;
            }
            if (!flag){
                printf("0\n");
            }
        }
        scanf("%6s", req);
    }
    for (int j = 0; j < m; ++j) {
        Node *cur = arr[j];
        Node* tmp;
        while (cur){
            tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free (arr);
    return 0;
}
