#pragma once

char *rcrt_builtin_intToString(int value);
char *rcrt_builtin_longToString(long value);
char *rcrt_builtin_longlongToString(long long value);
char *rcrt_builtin_floatToString(float value, int precision);
char *rcrt_builtin_doubleToString(double value, int precision);
void  rcrt_builtin_free(void *ptr);

int         rcrt_builtin_scan_int(void);
long        rcrt_builtin_scan_long(void);
long long   rcrt_builtin_scan_longlong(void);
float       rcrt_builtin_scan_float(void);
double      rcrt_builtin_scan_double(void);
int         rcrt_builtin_scan_bool(void);
