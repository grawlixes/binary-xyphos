#include "Node.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[ ]) {
    struct Node * arr[3];
    arr[0] = malloc(sizeof(struct Node));
    arr[1] = malloc(sizeof(struct Node));
    arr[2] = malloc(sizeof(struct Node));

    arr[1]->c = '1';
    arr[1]->count = 1;
    arr[2]->count = 2;
    arr[2]->c = '2';
    arr[0]->count = 3;
    arr[0]->left = arr[1];
    arr[0]->right = arr[2];

    printf("%c %c %c %c %i %i %i %i %i\n", arr[2]->c, arr[1]->c, arr[0]->left->c, arr[0]->right->c, arr[0]->count, arr[1]->count, arr[0]->left->count, arr[2]->count, arr[0]->right->count);

    return 0;
}
