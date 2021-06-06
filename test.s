.data
text1: .ascii "Hello world!\n"
text1_len = .- text1
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
mov $text1, %ecx
mov $text1_len, %edx
int $0x80
mov $0, %eax
ret
