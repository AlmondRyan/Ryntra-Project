# ROADMAP

## Binary Expression Support (only for `int`)

1. [x] Semantic Analysis: 
    - In `SemanticAnalyzer.cpp -> visitBinaryExpression()`:
        - Call `evaluate()` to get lhs type and rhs type
        - Check type compatibility
        - Error Handling
        - Set Result
2. [x] IR Generating

## Control Stream Support `if...else...`

