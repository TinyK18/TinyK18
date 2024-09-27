.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
mov $72,%rax
.L0004:
mov $101,%rax
.L0008:
mov $108,%rax
.L000c:
mov $108,%rax
.L0010:
mov $111,%rax
.L0014:
mov $10,%rax
.L0018:
pop %rbp
ret
