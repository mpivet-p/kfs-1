global gdt_flush
extern gdt
gdt_flush:
	lgdt	[gdt]
	mov		ax, 0x10
	mov		ds,	ax
	mov		es,	ax
	mov		fs,	ax
	mov		gs,	ax
	mov		ss,	ax
	jmp		0x08:flush_done
flush_done:
	ret
