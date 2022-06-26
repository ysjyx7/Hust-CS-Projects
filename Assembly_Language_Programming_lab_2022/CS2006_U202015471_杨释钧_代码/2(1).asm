.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :VARARG
 scanf			PROTO C :VARARG
 GetTickCount   Proto stdcall
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
	IpFmt db "%d",0ah,0dh,0
	IpFmt2 db "%s",0
	LOWF S 10 dup(<>)
	MIDF S 10 dup(<>)
	HIGHF S 10 dup(<>)
	INIT S 10 dup(<,256809,-1023,1265,>)
	STR1 DB "Please input the data",0
	STR2 DB "Total TIMES Spent:",0
	startTime DWORD ?
	i DD 0
.STACK	200
.code
main proc c
	INVOKE GetTickCount
	mov startTime,eax
	mov i,0
L0:
	inc i
	mov ecx,0
	mov ebx,0
	mov edi,0
	mov ebp,0
	mov esi,0
L1:
	mov	ebx,INIT[ecx].SDA
	imul ebx,5
	sub ebx,INIT[ecx].SDC
	add ebx,INIT[ecx].SDB
	add	ebx,100
	mov eax,ebx
	cdq
	mov ebx,128
	idiv ebx
	mov ebx,eax
	mov INIT[ecx].SF,ebx
	mov edx,0
	cmp ebx,100
	jl L2
	je L3
	jg L4
L2:
	mov bl,(BYTE ptr Init[ecx])
	mov (BYTE ptr LOWF[ebp]),bl
	inc ebp
	inc ecx
	inc edx
	cmp edx,TYPE S
	jb L2
	jmp L5
L3:
	mov bl,(BYTE ptr Init[ecx])
	mov (BYTE ptr MIDF[esi]),bl
	inc esi
	inc ecx
	inc edx
	cmp edx,TYPE S
	jna L3
	jmp L5
L4:
	mov bl,(BYTE ptr Init[ecx])
	mov (BYTE ptr HIGHF[edi]),bl
	inc edi
	inc ecx
	inc edx
	cmp edx,TYPE S
	jna L4
	jmp L5
L5:
	cmp ecx,9*(TYPE S)
	jle L1
	cmp i,100000000
	jna L0
	INVOKE GetTickCount
	sub eax,startTime
	push eax
	invoke printf,offset IpFmt2,offset str2
	pop eax
	invoke printf,offset IpFmt,eax
	invoke ExitProcess,0
main endp
END