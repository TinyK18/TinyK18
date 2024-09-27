.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
.L0002:
call debug
mov $42,%rax
.L0006:
call debug
mov $13,%rbx
.L000a:
call debug
push %rax
.L000c:
call debug
push %rbx
.L000e:
call debug
pop %rcx
.L0010:
call debug
pop %rdx
.L0012:
call debug
pop %rbp
ret
