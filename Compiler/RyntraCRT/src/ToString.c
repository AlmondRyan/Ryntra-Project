#include "ToString.h"
#include <stdio.h>
#include <stdlib.h>

char *rcrt_builtin_intToString(int value) {
    char *buffer = (char*)malloc(32);
    sprintf(buffer, "%d", value);
    return buffer;
}

void rcrt_builtin_free(void *ptr) {
    free(ptr);
}