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
mov $65535,%rbx
.L000a:
call debug
mov $0,%rcx
.L000e:
call debug
mov $10,%rdx
.L0012:
call debug
mov $65526,%rsi
.L0016:
call debug
mov $256,%rdi
.L001a:
call debug
mov %rax,%rbx
.L001c:
call debug
pop %rbp
ret
