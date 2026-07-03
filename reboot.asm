section .data
    text db "1: Restart 0: Abort", 10

section .bss
    buf resb 8

section .text
    global _start

_start:
    ; sys_write
    mov rax, 0x01
    mov rdi, 1
    mov rsi, text
    mov rdx, 20
    syscall

    ; sys_read
    xor rax, rax
    xor rdi, rdi
    lea rsi, [buf]
    mov rdx, 8
    syscall

    ; conditional branch
    cmp byte [buf], '1'
    jne .cancel

    ; sys_reboot
    mov rax, 0xa9
    mov rdi, 0xfee1dead
    mov rsi, 0x28121969
    mov rdx, 0x01234567
    xor r10, r10
    syscall

.cancel:
    ; sys_exit
    mov rax, 0x3c
    xor rdi, rdi
    syscall
