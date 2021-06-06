a_len = 200
.data
text1: .ascii "Enter your message: "
text1_len = .- text1
text2: .ascii "Your message: "
text2_len = .- text2
.bss
a: .space a_len
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
mov $3, %eax
mov $0, %ebx
mov $a, %ecx
mov $a_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $text2, %ecx
mov $text2_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $a, %ecx
mov $a_len, %edx
int $0x80
mov $0, %eax
ret
