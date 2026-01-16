#pragma once

char *rcrt_builtin_intToString(int value);
char *rcrt_builtin_longToString(long value);
char *rcrt_builtin_longlongToString(long long value);
char *rcrt_builtin_floatToString(float value, int precision);
char *rcrt_builtin_doubleToString(double value, int precision);
void  rcrt_builtin_free(void *ptr);