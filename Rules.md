## Summary

1. Always allows casting from smaller type to bigger type. Such as casting `int` to `long`. From bigger type casting to smaller type need explicit conversions. For example: `(int)100L`
2. `int` is always 32-bits. `long` is always 64-bits.
3. NOT allowed to use `int` constructing a `bool` type, or trying converting from `int` to `bool`, or use boolean literals as a number. So, `if (number)` is not allowed.