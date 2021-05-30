.section .text
.global _start
_start:
call main
mov %eax, %ebx
mov $1, %eax
int $0x80

