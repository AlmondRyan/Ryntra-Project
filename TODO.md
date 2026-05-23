Something will do afterward:
- Add `--strict` (`-s`) command argument, will treat RCW002 (etc.) as an error.
- Add `do...while()` block

****

Semantic Note:

- `ref<T>` auto dereference, always valid, non-null, alias semantics, no rebinding, no ownership
- `ptr<T>` nullable, rebinding, arithmetic operations (in unsafe block), unsafe, no automatic lifetime guarantee

****

- ✅ V0.0.1 Hello World
- ✅ V0.0.2.1 `int` Variable Declaration
- ✅ V0.0.2.2 `int` Variable Arithmetic Operation (w/ Modulation)
- ✅ V0.0.2.3 `int` Variable Assignment and Compound Assignment
- ✅ V0.0.2.4 `int` Variable Bitwise Operation (w/ lshift and rshift)
- ✅ V0.0.3.1 `long` Variable Declaration
- ✅ V0.0.3.2 `long` Variable Arithmetic Operation
- ✅ V0.0.3.3 `long` Variable Bitwise Operation and Assignment
- ✅ V0.0.3.4 Operations and Casting between `int` and `long`.
- ✅ V0.0.3.5 `__builtin_scan()` Function
- ✅ V0.0.4.1 `bool` Variable Declaration and Assignment
- ✅ V0.0.4.2 Comparison Operators
- ✅ V0.0.4.3 `if` Blocks
- ✅ V0.0.4.4 `else` And `else if` Blocks
- ✅ V0.0.4.5 Condition NOT operator
- ✅ V0.0.5.1 `while` Blocks
- ✅ V0.0.5.2 `break` Blocks
- ✅ V0.0.5.3 `continue` Blocks
- ✅ V0.0.5.4 Self Increase/Decrease Operator
- ✅ V0.0.5.5 `for` Blocks
- ✅ V0.0.6.1 Array Declaration
- ✅ V0.0.6.2 Array Index Access
- ✅ V0.0.6.3 Array Index Assignment
- ✅ V0.0.7.1 Angle bracket syntax for type parameters `<>`
- ✅ V0.0.7.2 Reference `ref<T>` (automatically dereference, always safe)
- ✅ V0.0.7.3 Unsafe Block `unsafe`
- ✅ V0.0.7.4 Unsafe Pointer `ptr<T>`
- ✅ V0.0.7.5 Pointer dereference `ptr<T>.load()` (manually dereference, lowering to `ptrload` instruction)
- ✅ V0.0.7.6 `ptr<T>.store` (lowering to `ptrstore` instruction)
- ✅ V0.0.7.7 `null` Keyword
- ✅ V0.0.7.8 Pointer + integer (move), Pointer - integer (move), Pointer - pointer (get distance, must in same memory area)
- ✅ V0.0.7.9 Dynamically apply for memory (`new` and `delete`) on heap
- ✅ V0.0.7.10 Pointer comparison (`==, !=`)
- ✅ V0.0.7.11 (Huge Modification) Make array with pointer, `fixed` keyword (avoid GC move it), array access `[]` returns `ref<T>`, just like:
```
int[] arr = new int[5];
arr[0] = 10;
arr[1] = 20;
arr[2] = 30;
arr[3] = 40;
arr[4] = 50;
unsafe {
    fixed ptr<int> p = ptr(arr);
    __builtin_print(p.load()); __builtin_print("\n"); // 10
    __builtin_print(ptr(p + 1).load); __builtin_print("\n"); // 20
    __builtin_print(p[3]); __builtin_print("\n"); // 40
    p[3] = 400; // write 400
}
__builtin_print(p[3]); // 400
```