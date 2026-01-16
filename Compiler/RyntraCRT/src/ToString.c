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

char *rcrt_builtin_longToString(long value) {
    int len = snprintf(NULL, 0, "%ld", value);
    if (len < 0) return NULL;

    char *buf = malloc((size_t)len + 1);
    if (!buf) return NULL;

    snprintf(buf, (size_t)len + 1, "%ld", value);
    return buf;
}

char *rcrt_builtin_longlongToString(long long value) {
    int len = snprintf(NULL, 0, "%lld", value);
    if (len < 0) return NULL;

    char *buf = malloc((size_t)len + 1);
    if (!buf) return NULL;

    snprintf(buf, (size_t)len + 1, "%lld", value);
    return buf;
}

char *rcrt_builtin_floatToString(float value, int precision) {
    char format[16];
    snprintf(format, sizeof format, "%%.%df", precision);
    int len = snprintf(NULL, 0, format, value);
    if (len < 0) return NULL;

    char *buf = malloc((size_t)len + 1);
    if (!buf) return NULL;

    snprintf(buf, (size_t)len + 1, format, value);
    return buf;
}

char *rcrt_builtin_doubleToString(double value, int precision) {
    char format[16];
    snprintf(format, sizeof format, "%%.%df", precision);
    int len = snprintf(NULL, 0, format, value);
    if (len < 0) return NULL;

    char *buf = malloc((size_t)len + 1);
    if (!buf) return NULL;

    snprintf(buf, (size_t)len + 1, format, value);
    return buf;
}