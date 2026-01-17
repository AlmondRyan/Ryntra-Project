# OpCodes (Operation Code)

This is the OpCode reference of RVM (Ryntra VM), the backend of Ryntra Compiler. A stack-based Virtual Machine (VM).

### `LD_CONST` (Load Constant)

| Name       | Argument                      |
|:-----------|:------------------------------|
| `LD_CONST` | Index in constant pool, `int` |

Load Const (aka. `LD_CONST`) is a operation that load the given index constant from the constant pool. For example, the pool is like:
```
CONST_POOL: ["Hello World", "What", "How", "Hi"]
```

Call `LD_CONST 0` will load `Hello World` onto the top of the stack.

****

### `NOP` (No Operation)

| Name  | Argument    |
|:------|:------------|
| `NOP` | No Argument |

Do nothing.

****

### `B_CALL` (Builtin Call)

| Name     | Argument                             |
|:---------|:-------------------------------------|
| `B_CALL` | Index of the Builtin Function, `int` |

Call Builtin Function by given index. 

| Index | Builtin Function  |
|:------|:------------------|
| 0     | `__builtin_print` |
| 1     | `__builtin_scan`  |

After calling, it will push the return value onto the top of the stack.

****

### `HALT` (Halt)

The end of the operating.

****

### `STORE_VAR`

| Name        | Argument                             |
|:------------|:-------------------------------------|
| `STORE_VAR` | The index that point to the variable |

Store variable into Operand Stack. The index you given will be point to the variable.