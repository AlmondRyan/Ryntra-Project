#include "ToString.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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

static int rcrt_is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int rcrt_is_digit(char c) {
    return c >= '0' && c <= '9';
}

static int rcrt_read_token(char *buf, size_t size) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE || size == 0) {
        if (size > 0) {
            buf[0] = '\0';
        }
        return 0;
    }

    DWORD read = 0;
    char  ch;
    size_t i = 0;

    for (;;) {
        if (!ReadFile(hIn, &ch, 1, &read, NULL) || read == 0) {
            buf[0] = '\0';
            return 0;
        }
        if (!rcrt_is_space(ch)) {
            break;
        }
    }

    buf[i++] = ch;

    while (i + 1 < size) {
        if (!ReadFile(hIn, &ch, 1, &read, NULL) || read == 0) {
            break;
        }
        if (rcrt_is_space(ch)) {
            break;
        }
        buf[i++] = ch;
    }

    buf[i] = '\0';
    return 1;
}

static int rcrt_parse_long(const char *s, long *out) {
    int   sign = 1;
    long  result = 0;
    const char *p = s;

    if (*p == '+' || *p == '-') {
        if (*p == '-') {
            sign = -1;
        }
        p++;
    }

    if (!rcrt_is_digit(*p)) {
        return 0;
    }

    while (rcrt_is_digit(*p)) {
        result = result * 10 + (*p - '0');
        p++;
    }

    *out = sign * result;
    return 1;
}

static int rcrt_parse_longlong(const char *s, long long *out) {
    int        sign = 1;
    long long  result = 0;
    const char *p = s;

    if (*p == '+' || *p == '-') {
        if (*p == '-') {
            sign = -1;
        }
        p++;
    }

    if (!rcrt_is_digit(*p)) {
        return 0;
    }

    while (rcrt_is_digit(*p)) {
        result = result * 10 + (long long)(*p - '0');
        p++;
    }

    *out = sign * result;
    return 1;
}

static int rcrt_parse_double(const char *s, double *out) {
    int        sign = 1;
    double     result = 0.0;
    double     frac = 0.0;
    double     base = 0.1;
    const char *p = s;
    int        has_digit = 0;

    if (*p == '+' || *p == '-') {
        if (*p == '-') {
            sign = -1;
        }
        p++;
    }

    while (rcrt_is_digit(*p)) {
        has_digit = 1;
        result = result * 10.0 + (double)(*p - '0');
        p++;
    }

    if (*p == '.') {
        p++;
        while (rcrt_is_digit(*p)) {
            has_digit = 1;
            frac += base * (double)(*p - '0');
            base *= 0.1;
            p++;
        }
    }

    if (!has_digit) {
        return 0;
    }

    *out = (result + frac) * (double)sign;
    return 1;
}

int rcrt_builtin_scan_int(void) {
    char buf[64];
    long value;

    if (!rcrt_read_token(buf, sizeof buf)) {
        return 0;
    }

    if (!rcrt_parse_long(buf, &value)) {
        return 0;
    }

    return (int)value;
}

long rcrt_builtin_scan_long(void) {
    char buf[64];
    long value;

    if (!rcrt_read_token(buf, sizeof buf)) {
        return 0;
    }

    if (!rcrt_parse_long(buf, &value)) {
        return 0;
    }

    return value;
}

long long rcrt_builtin_scan_longlong(void) {
    char      buf[64];
    long long value;

    if (!rcrt_read_token(buf, sizeof buf)) {
        return 0;
    }

    if (!rcrt_parse_longlong(buf, &value)) {
        return 0;
    }

    return value;
}

float rcrt_builtin_scan_float(void) {
    char   buf[64];
    double value;

    if (!rcrt_read_token(buf, sizeof buf)) {
        return 0.0f;
    }

    if (!rcrt_parse_double(buf, &value)) {
        return 0.0f;
    }

    return (float)value;
}

double rcrt_builtin_scan_double(void) {
    char   buf[64];
    double value;

    if (!rcrt_read_token(buf, sizeof buf)) {
        return 0.0;
    }

    if (!rcrt_parse_double(buf, &value)) {
        return 0.0;
    }

    return value;
}

int rcrt_builtin_scan_bool(void) {
    char buf[32];
    long value;

    if (!rcrt_read_token(buf, sizeof buf)) {
        return 0;
    }

    if (!rcrt_parse_long(buf, &value)) {
        return 0;
    }

    return value != 0;
}
