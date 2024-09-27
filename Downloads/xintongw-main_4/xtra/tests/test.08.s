.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
jmp .L001a
.L0004:
push %rax
.L0006:
push %rbx
.L0008:
mov $0,%rax
.L000c:
mov $0,%rbx
.L0010:
.L0012:
call debug
.L0014:
pop %rbx
.L0016:
pop %rax
.L0018:
ret
.L001a:
mov $42,%rax
.L001e:
push %rax
.L0020:
mov $13,%rax
.L0024:
push %rax
.L0026:
mov %rsp,%rax
.L0028:
mov $8,%rbx
.L002c:
add %rax,%rbx
.L002e:
mov (%rax),%rcx
.L0030:
mov (%rbx),%rdx
.L0032:
call .L0004
.L0036:
mov %rcx,(%rbx)
.L0038:
mov %rdx,(%rax)
.L003a:
mov (%rax),%rcx
.L003c:
mov (%rbx),%rdx
.L003e:
call .L0004
.L0042:
pop %rax
.L0044:
pop %rax
.L0046:
pop %rbp
ret
