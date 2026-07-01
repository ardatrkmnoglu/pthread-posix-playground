section .data
    endl: db 10
    msg:  db "The message is:", 10

section .bss
    buf: resb 24

section .text
    global _start

_start:
    ; reserve space in the stack
    sub rsp, 24

    ; sys_read
    xor rax, rax
    xor rdi, rdi
    lea rsi, [buf]
    mov rdx, 24
    syscall

    ; sys_write
    mov rax, 0x01
    mov rdi, 1
    mov rsi, msg
    mov rdx, 16
    syscall
    mov rax, 0x01
    mov rdi, 1
    mov rsi, buf
    mov rdx, 24
    syscall

    ; sys_exit
    mov rax, 0x3c
    xor rdi, rdi
    syscall
