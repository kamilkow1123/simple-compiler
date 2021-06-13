age_len = 200
age_str_len = 200
.data
text1: .ascii "How old are you?\n"
text1_len = .- text1
text2: .ascii "You are "
text2_len = .- text2
text3: .ascii "\n"
text3_len = .- text3
.bss
age: .space age_len
age_str: .space age_str_len
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
mov $3, %eax
mov $0, %ebx
mov $age_str, %ecx
mov $age_str_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $text2, %ecx
mov $text2_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $age_str , %ecx
mov $age_str_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $text3, %ecx
mov $text3_len, %edx
int $0x80
ret
.global main
main:
call greet
mov $0, %eax
ret
