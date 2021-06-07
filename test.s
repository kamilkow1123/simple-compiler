a_len = 200
a_str_len = 200
.data
a: .int 5
a_str: .ascii "5"
a_str_len = .- a_str
.bss
a: .space a_len
a_str: .space a_str_len
.text
.global _start
_start:
call main
mov %eax, %ebx
mov $1, %eax
int $0x80

.global main
main:
mov $4, %eax
mov $1, %ebx
mov $a_str , %ecx
mov $a_str_len, %edx
int $0x80
mov $0, %eax
ret
