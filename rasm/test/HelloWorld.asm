section .data
msg db "Hello World", 0Ah

section .text
global _start

_start:
    mov rax, 1              ; System Call 1 -> sys_write
    mov rdi, 1              ; File Descriptor 1 -> stdout
    mov rsi, msg
    mov rdx, 12
    syscall

    mov rax, 60             ; System Call 60 -> sys_exit
    xor rdi, rdi
    syscall