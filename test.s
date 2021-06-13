name_len = 200
name_str_len = 200
.data
text1: .ascii "Podaj swoje imie: "
text1_len = .- text1
text2: .ascii "Witaj, "
text2_len = .- text2
text3: .ascii "!\n"
text3_len = .- text3
text_str: .ascii "Jest rok "
text_str_len = .- text_str
year: .int 2021
year_str: .ascii "2021"
year_str_len = .- year_str
text4: .ascii "\n"
text4_len = .- text4
.bss
name: .space name_len
name_str: .space name_str_len
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
mov $name_str, %ecx
mov $name_str_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $text2, %ecx
mov $text2_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $name_str , %ecx
mov $name_str_len, %edx
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
mov $4, %eax
mov $1, %ebx
mov $text_str , %ecx
mov $text_str_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $year_str , %ecx
mov $year_str_len, %edx
int $0x80
mov $4, %eax
mov $1, %ebx
mov $text4, %ecx
mov $text4_len, %edx
int $0x80
mov $0, %eax
ret
