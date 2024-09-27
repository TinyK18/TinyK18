.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
.L0002:
call debug
mov $0,%rax
.L0006:
call debug
mov $1,%rbx
.L000a:
call debug
mov $2,%rcx
.L000e:
call debug
test %rbx,%rbx
setnz %r15b
.L0010:
call debug
test %rbx,%rcx
setnz %r15b
.L0012:
call debug
cmp %rbx,%rcx
setg %r15b
.L0014:
call debug
cmp %rbx,%rbx
setg %r15b
.L0016:
call debug
cmp %rcx,%rbx
setg %r15b
.L0018:
call debug
cmp %rbx,%rbx
sete %r15b
.L001a:
call debug
cmp %rbx,%rcx
sete %r15b
.L001c:
call debug
pop %rbp
ret
