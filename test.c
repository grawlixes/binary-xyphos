#include "Node.h"

#include <stdio.h>
#include <string.h>

void add(int * slang) {
    (*slang)++;
}

int main(int argc, char * argv[ ]) {
    int x = 0;

    add(&x);

    printf("%i\n", x);

    return 0;
}
