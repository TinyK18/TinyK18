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
add %rcx,%rdx
.L0018:
call debug
sub %rcx,%rdx
.L001a:
call debug
imul %rcx,%rbx
.L001c:
call debug
neg %rax
.L001e:
call debug
neg %rax
.L0020:
call debug
inc %rdi
call debug
dec %rdi
call debug
pop %rbp
ret
