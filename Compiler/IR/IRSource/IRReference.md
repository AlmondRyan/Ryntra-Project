## Types

```
type ::=
        void
        | i1 | i8 | i16 | i32 | i64 | f32 | f64
        | string         // 语言内置字符串引用 (GC)
        | class <name>   // 类引用 (GC, 也就是 ref<class>)
        | struct <name>  // 结构体值类型
        | array <type>   // 数组引用 (GC, ref<array>)
        | ptr <type>     // 临时内部指针 (Transient Interior Pointer), 不可跨 SafePoint
        | fn(<type>*) -> <type>
        // 泛型在 IR 阶段已消除 (Monomorphized)
```

### 类型系统约束
1.  **泛型消除**: 所有的 `List<T>` 在此阶段必须已经展开为 `List_int`, `List_float` 等具体类型。IR 中不应包含 `generic <T>`。
2.  **ptr 的生命周期约束**:
    *   `ptr <type>` 仅用于本地内存访问优化（如连续的字段读取）。
    *   **禁止跨越 SafePoint**: 编译器后端必须保证 `ptr` 类型的值不会在 `call`, `alloc`, `loop_backedge` 等 SafePoint 处存活。如果需要跨越，必须重新从基对象 (`class`/`array`) 计算。
    *   *目的*: 简化 GC，GC 扫描栈时只需要关注对象引用，不需要处理复杂的内部指针更新。

## Values

1.  **SSA 虚拟寄存器**: `%1`, `%a`。
2.  **字面量**: `1`, `3.14`, `null`.

## Commands

### 1. 纯值运算 (No Side Effect)
```
add, sub, mul, div, rem
and, or, xor, shl, shr
cmp [eq|ne|gt|ge|lt|le]
neg, not
cast <type>
```

### 2. 内存与对象操作 (Side Effects & Barriers)

**所有修改堆内存的操作都隐含写屏障 (Write Barrier)。**

```
// 1. 字段读写
// 读取对象字段。如果 %obj 为 null，触发 Panic。
%val = load_field %obj, field_index

// 写入对象字段。
// * 必须触发写屏障 (Write Barrier)，如果 %val 是引用类型。
// * 显式副作用 (Side Effect)。
store_field %obj, field_index, %val

// 2. 数组读写
// 读取数组元素。带边界检查。
%val = load_elem %arr, %index

// 写入数组元素。
// * 必须触发写屏障。
// * 带边界检查。
store_elem %arr, %index, %val

// 3. 临时指针操作 (Transient Pointers)
// 仅用于紧凑的局部操作，禁止跨 SafePoint 使用！
%ptr = gep %base, index...
%val = load %ptr
store %ptr, %val  // 写入时如果 val 是引用，仍需写屏障，但建议仅用于值类型
```

### 3. 对象管理 (GC SafePoints)

**分配指令是必然的 SafePoint。**

```
// 分配对象
// * SafePoint: 可能会触发 GC。
// * StackMap: 必须生成，记录当前活跃的引用变量。
%obj = new <class_name>

// 分配数组
// * SafePoint
%arr = new_array <type>, %len
```

### 4. 函数调用 (GC SafePoints)

**所有调用都是 SafePoint。**

```
// 常规调用
// * SafePoint: 必须生成 StackMap。
%ret = call @func(%args...)

// 可能会触发异常/展开的调用
// * SafePoint
%ret = invoke @func(%args...) to label_normal unwind label_unwind
```

### 5. 控制流 (Loop SafePoints)

```
// 循环回边 (Backedge) 必须插入 Poll 点
// * 编译器后端需在循环头或尾插入 safepoint_poll 指令。
// * 保证长时间运行的循环能响应 GC 请求。
br label
cond_br %cond, label_true, label_false
ret %val
```

## VM Design Guidelines

### 1. 内存布局
*   **Object Header**: 包含 GC 标记位、类元数据指针 (VTable)。
*   **Array Header**: 包含 Length。

### 2. Stack Maps (栈图)
*   **生成时机**: 在所有 `call`, `invoke`, `new`, `new_array` 以及循环回边处。
*   **内容**: 这是一个位图 (BitMap) 或索引列表，指出当前栈帧中哪些 Slot 存储的是对象引用 (`class`, `array`, `string`)。
*   **精确性**: GC 扫描时，根据 StackMap 精确判断，不猜测。

### 3. 写屏障 (Write Barrier)
*   **场景**: `store_field`, `store_elem` 指令，且写入的值是引用类型时。
*   **实现建议 (Card Marking / Remembered Set)**:
    *   如果是分代 GC (Generational GC)，当老年代对象引用了新生代对象时，记录该老年代对象（或其所在的 Card）。
    *   *伪代码*:
      ```c
      void store_field(Obj* obj, int offset, Obj* val) {
          obj->fields[offset] = val;
          if (val != NULL && is_in_young_gen(val) && !is_in_young_gen(obj)) {
              record_barrier(obj);
          }
      }
      ```

### 4. 显式副作用与优化
*   IR 中的 `load_field` / `store_field` 明确了内存依赖。
*   优化器不能随意重排 `store` 指令，除非通过别名分析 (Alias Analysis) 证明无冲突。
*   `ptr` 的限制使得优化器可以将一组 `gep` + `load` 序列视为一个原子操作单元，不必担心中间发生 GC 导致指针失效。

