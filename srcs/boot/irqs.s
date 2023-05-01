%macro irq 1
irq_%+%1:
	cli
	push	byte 0
	push	byte 32+%1
	jmp		irq_common_stub
%endmacro

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15

global irq_stub_table
irq_stub_table:
%assign	i 0
%rep	16
		dd irq_%+i
%assign i i+1
%endrep

extern irq_handler
irq_common_stub:
	pusha
	push	ds
	push 	es
	push 	fs
	push 	gs
	mov		ax, 0x10
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		eax, esp
	push	eax
	mov		eax, irq_handler
	call	eax
	pop		eax
	pop		gs
	pop		fs
	pop		es
	pop		ds
	popa
	add		esp, 8
	iret
