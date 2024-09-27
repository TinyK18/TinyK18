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
mov $4660,%rax
.L001e:
push %rax
.L0020:
mov %rsp,%rax
.L0022:
mov $1,%rbx
.L0026:
add %rax,%rbx
.L0028:
movb (%rax),%cl
.L002a:
movb (%rbx),%dl
.L002c:
call .L0004
.L0030:
movb %cl,(%rbx)
.L0032:
movb %dl,(%rax)
.L0034:
movb (%rax),%cl
.L0036:
movb (%rbx),%dl
.L0038:
call .L0004
.L003c:
pop %rax
.L003e:
pop %rbp
ret
