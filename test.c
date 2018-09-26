#include "Node.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[ ]) {
    char c = 0;
    char b = 0;
    char a = 0;
    c |= 126;
    b |= 127;
    a |= 129;

    printf("%i, %i, %i\n", c,b, a);

    return 0;
}
