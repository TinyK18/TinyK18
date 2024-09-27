.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
.L0002:
call debug
mov $1,%rax
.L0006:
call debug
jmp .L0012
.L000a:
call debug
mov $3,%rax
.L000e:
call debug
jmp .L001a
.L0012:
call debug
mov $2,%rax
.L0016:
call debug
jmp .L000a
.L001a:
call debug
mov $4,%rax
.L001e:
call debug
pop %rbp
ret
