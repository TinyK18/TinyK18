.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
.L0002:
call debug
mov $1,%rbx
.L0006:
call debug
mov $2,%rcx
.L000a:
call debug
cmp %rbx,%rcx
sete %r15b
.L000c:
call debug
test $1,%r15
jne .L0016
.L000e:
call debug
cmp %rbx,%rbx
sete %r15b
.L0010:
call debug
test $1,%r15
jne .L001a
.L0012:
call debug
jmp .L0016
.L0016:
call debug
mov $65535,%rax
.L001a:
call debug
pop %rbp
ret
