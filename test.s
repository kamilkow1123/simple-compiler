.data
text1: .ascii "Hello\n"
text1_len = .- text1
text2: .ascii "Say hello\n"
text2_len = .- text2
.bss
.text
.global _start
_start:
call main
mov %eax, %ebx
mov $1, %eax
int $0x80

.global greet
greet:
mov $4, %eax
mov $1, %ebx
mov $text1, %ecx
mov $text1_len, %edx
int $0x80
ret
.global main
main:
mov $4, %eax
mov $1, %ebx
mov $text2, %ecx
mov $text2_len, %edx
int $0x80
call greet
mov $0, %eax
ret
