#pragma once

char *rcrt_builtin_intToString(int value);
char *rcrt_builtin_longToString(long value);
char *rcrt_builtin_longlongToString(long long value);
char *rcrt_builtin_floatToString(float value);
char *rcrt_builtin_doubleToString(double value);
void  rcrt_builtin_free(void *ptr);