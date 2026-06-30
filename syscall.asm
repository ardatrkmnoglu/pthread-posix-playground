section .bss
    uname_buf: resb 400

section .data
    endl: db 10

section .text
    global _start

_start:
    ; fetch uname data to memory (sys_uname)
    mov rax, 0x3f
    lea rdi, [uname_buf]
    syscall

    ; write output to stdout (sys_write)
    mov rax, 0x01
    mov rdi, 1      ; fd of stdout
    lea rsi, [uname_buf]
    mov rdx, 8      ; character count
    syscall
    mov rax, 0x01
    mov rdi, 1
    mov rsi, endl
    mov rdx, 1
    syscall

    ; exit program (sys_exit)
    mov rax, 0x3c
    xor rdi, rdi
    syscall
