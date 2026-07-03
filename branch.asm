section .data
    text db "Enter a number:", 10
    msg  db "Nonzero", 10

section .bss
    buf resb 8

section .text
    global _start

_start:
    ; sys_write
    mov rax, 0x01
    mov rdi, 1
    mov rsi, text
    mov rdx, 16
    syscall

    ; sys_read
    xor rax, rax
    xor rdi, rdi
    lea rsi, [buf]
    mov rdx, 8
    syscall

    ; compare
    cmp byte [buf], '0'
    jz .cancel

    ; sys_write (print if nonzero)
    mov rax, 0x01
    mov rdi, 1
    mov rsi, msg
    mov rdx, 8
    syscall

.cancel:
    ; sys_exit
    mov rax, 0x3c
    xor rdi, rdi
    syscall
