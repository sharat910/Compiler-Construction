extern printf
extern scanf

section .bss
	x:	resb   2
	y:	resb   2
	z:	resb   2
	sum:	resb   2
	value:	resb   2

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

	mov	rsi,y
	mov	rdi,scanint
	call scanf

	push rax

	mov rax,19
	push rax
	mov [z],rax
	pop rax

	push rax

	mov rax,[x]
	push rax
	mov rax,20
	push rax
	pop rbx
	pop rax
	mul rbx
	push rax
	mov rax,[y]
	push rax
	mov rax,4
	push rax
	pop rbx
	pop rax
	div rbx
	push rax
	pop rbx
	pop rax
	mul rbx
	push rax
	mov [sum],rax
	pop rax

	push rax

	mov rax,[sum]
	push rax
	mov rax,[z]
	push rax
	mov rax,2
	push rax
	pop rbx
	pop rax
	mul rbx
	push rax
	mov rax,[x]
	push rax
	mov rax,[y]
	push rax
	pop rbx
	pop rax
	mul rbx
	push rax
	pop rbx
	pop rax
	sub rax,rbx
	push rax
	pop rbx
	pop rax
	add rax,rbx
	push rax
	mov [value],rax
	pop rax

loop0:
	mov rax,[z]
	push rax
	mov rax,2
	push rax
	pop rbx
	pop rax
	cmp rax,rbx
	jle endloop0
	mov	rsi,[sum]
	mov	rdi,putint
	call printf

	push rax

	mov rax,[z]
	push rax
	mov rax,1
	push rax
	pop rbx
	pop rax
	sub rax,rbx
	push rax
	mov [z],rax
	pop rax

	jmp loop0
endloop0:
	mov	rsi,[value]
	mov	rdi,putint
	call printf


	pop rbp
	ret
