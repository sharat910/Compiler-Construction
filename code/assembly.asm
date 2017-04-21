extern printf
extern scanf

section .bss
	x:	resb   8
	sum:	resb   8
	k_212:	resb   8

section .data
	scanint:	dw "%d", 0
	putint:	db "%d", 10, 0

section .text

global main
main:


	push rbp
	mov	rsi,x
	mov	rdi,scanint
	call scanf

	push rax

	mov rax,100
	push rax

	mov [sum],rax
	pop rax

	pop rax

	mov 	rdi, 1
loop0:
	mov 	[k_212],rdi
	push rdi
	push rax

	mov rax,[sum]
	push rax

	mov rax,[k_212]
	push rax

	mov rax,[x]
	push rax

	pop rbx
	pop rax
	mul rbx
	push rax

	pop rbx
	pop rax
	add rax,rbx
	push rax

	mov [sum],rax
	pop rax

	pop rax

	mov	rsi,[sum]
	push rdi

	mov	rdi,putint
	call printf

	pop rdi

	pop	rdi
	add	rdi, 1
	cmp	rdi, 10
	jle	loop0
	push rdi
	mov	rsi,[sum]
	push rdi

	mov	rdi,putint
	call printf

	pop rdi


	pop rbp
	ret
