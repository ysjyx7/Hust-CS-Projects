.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :VARARG
 scanf			PROTO C :VARARG
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 S struct
	SAMID DB 9 dup(0)
	SDA   DD 0
	SDB   DD 0
	SDC   DD 0
	SF    DD 0
S ENDS
.DATA
	IpFmt db "%s",0ah,0dh,0
	IpFmt2 db "%s",0
	LOWF S 10 dup(<>)
	MIDF S 10 dup(<>)
	HIGHF S 10 dup(<>)
	INIT S 10 dup(<,1,2,3,>)
	STR1 DB "Please input the data",0
.STACK	200
.code
main proc c
	mov eax,0
	mov ebx,0
	mov edi,0
	mov ebp,0
	mov esi,0
;	invoke printf,offset IpFmt,offset STR1
;L0:
;	invoke scanf,offset	IpFmt2,offset IpFmt2,offset	IpFmt2,(S ptr INIT[eax]).SDA,(S ptr INIT[eax]).SDB,(S ptr INIT[eax]).SDC
;	add eax,TYPE S
;	cmp eax,10*(TYPE S)
;	jl L0
;	mov eax,0
L1:
	mov	ebx,(S ptr INIT[eax]).SDA
	imul ebx,5
	add ebx,(S ptr INIT[eax]).SDB
	sub ebx,(S ptr INIT[EAX]).SDC
	add	ebx,100
	shr ebx,7
	mov (S ptr INIT[eax]).SF,ebx
	cmp ebx,100
	jl L2
	je L3
	jg L4
L2:
	mov ebx,(S ptr Init[eax]).SDA
	mov (S ptr LOWF[ebp]).SDA,ebx
	mov ebx,(S ptr Init[eax]).SDB
	mov (S ptr LOWF[ebp]).SDB,ebx
	mov ebx,(S ptr Init[eax]).SDC
	mov (S ptr LOWF[ebp]).SDC,ebx
	mov ebx,(S ptr Init[eax]).SF
	mov (S ptr LOWF[ebp]).SF,ebx
	add ebp,TYPE S
	jmp L5
L3:
	mov ebx,(S ptr Init[eax]).SDA
	mov (S ptr MIDF[esi]).SDA,ebx
	mov ebx,(S ptr Init[eax]).SDB
	mov (S ptr MIDF[esi]).SDB,ebx
	mov ebx,(S ptr Init[eax]).SDC
	mov (S ptr MIDF[esi]).SDC,ebx
	mov ebx,(S ptr Init[eax]).SF
	mov (S ptr MIDF[esi]).SF,ebx
	add esi,TYPE S
	jmp L5
L4:
	mov ebx,(S ptr Init[eax]).SDA
	mov (S ptr HIGHF[edi]).SDA,ebx
	mov ebx,(S ptr Init[eax]).SDB
	mov (S ptr HIGHF[edi]).SDB,ebx
	mov ebx,(S ptr Init[eax]).SDC
	mov (S ptr HIGHF[edi]).SDC,ebx
	mov ebx,(S ptr Init[eax]).SF
	mov (S ptr HIGHF[edi]).SF,ebx
	add edi,TYPE S
	jmp L5
L5:
	add eax,TYPE S
	cmp eax,9*(TYPE S)
	jle L1
	invoke ExitProcess,0
main endp
END
