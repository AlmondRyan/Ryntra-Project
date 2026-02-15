# IR Reference

Ryntra IR (RIR) is a typical Stack-Based IR, just like Assembly.

Here is an example.

```asm
sec .cdata

sec .code
_entry:
    define @add(i32, i32) -> i32 {
        add.i32                       ; pop a, pop b, push result
        ret
    }
    
    define @main() -> i32 {
        local i32 %a
        local i32 %c
        
        loadc 10                     ; load 10
        store %a                     ; pop 10
        
        loadc 20                     ; load 20, stack [20]
        load %a                      ; load 10, stack [10, 20]
        
        call @add                    ; call 'add', pop 10, pop 20, push 30
        store %c                     ; store 30 to %c, stack []
        
        load %c
        syscall 0
        halt
    }
```

This IR represents the following code:

```ryntra
public int add(int a, int b) {
    return a + b;
}

public int main() {
    int a = 10;
    const int b = 20;
    
    int c = add(a, b);
    __builtin_print(c);
    return 0;
}
```