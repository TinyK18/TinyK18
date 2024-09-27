.globl test
test:
push %rbp
mov %rsp, %rbp
.L0000:
.L0002:
call debug
mov $2,%rax
.L0006:
call debug
mov $3,%rbx
.L000a:
call debug
mov $4,%rcx
.L000e:
call debug
mov $5,%rdx
.L0012:
call debug
mov $7,%rdi
.L0016:
call debug
and %rdx,%rax
.L0018:
call debug
or %rcx,%rbx
.L001a:
call debug
xor %rdi,%rcx
.L001c:
call debug
not %rsi
.L001e:
call debug
not %rsi
.L0020:
call debug
pop %rbp
ret
