.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
.L0002:
call debug
jmp .L000c
.L0006:
call debug
mov $2,%rax
.L000a:
call debug
ret
.L000c:
call debug
mov $1,%rax
.L0010:
call debug
call .L0006
.L0014:
call debug
mov $3,%rax
.L0018:
call debug
pop %rbp
ret
