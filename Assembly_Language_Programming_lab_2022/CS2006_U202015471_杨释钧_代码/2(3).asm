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
	str2 DB "Total Time Spent:",0
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
	shr ebx,7
	mov INIT[ecx].SF,ebx
	cmp ebx,100
	jl L2
	je L3
	jg L4
L2:
	mov ebx,(DWORD ptr Init[ecx].SAMID[0])
	mov (DWORD ptr LOWF[ebp].SAMID[0]),ebx
	mov ebx,(DWORD ptr Init[ecx].SAMID[4])
	mov (DWORD ptr LOWF[ebp].SAMID[4]),ebx
	mov bl,(BYTE ptr Init[ecx].SAMID[8])
	mov (BYTE ptr LOWF[ebp].SAMID[8]),bl
	mov ebx,Init[ecx].SDA
	mov LOWF[ebp].SDA,ebx
	mov ebx,Init[ecx].SDB
	mov LOWF[ebp].SDB,ebx
	mov ebx,Init[ecx].SDC
	mov LOWF[ebp].SDC,ebx
	mov ebx,Init[ecx].SF
	mov LOWF[ebp].SF,ebx
	add ebp,TYPE S
	jmp L5
L3:
	mov ebx,(DWORD ptr Init[ecx].SAMID[0])
	mov (DWORD ptr MIDF[esi].SAMID[0]),ebx
	mov ebx,(DWORD ptr Init[ecx].SAMID[4])
	mov (DWORD ptr MIDF[esi].SAMID[4]),ebx
	mov bl,(BYTE ptr Init[ecx].SAMID[8])
	mov (BYTE ptr MIDF[esi].SAMID[8]),bl
	mov ebx,Init[ecx].SDA
	mov MIDF[esi].SDA,ebx
	mov ebx,Init[ecx].SDB
	mov MIDF[esi].SDB,ebx
	mov ebx,Init[ecx].SDC
	mov MIDF[esi].SDC,ebx
	mov ebx,Init[ecx].SF
	mov MIDF[esi].SF,ebx
	add esi,TYPE S
	jmp L5
L4:
	mov ebx,(DWORD ptr Init[ecx].SAMID[0])
	mov (DWORD ptr HIGHF[edi].SAMID[0]),ebx
	mov ebx,(DWORD ptr Init[ecx].SAMID[4])
	mov (DWORD ptr HIGHF[edi].SAMID[4]),ebx
	mov bl,(BYTE ptr Init[ecx].SAMID[8])
	mov (BYTE ptr HIGHF[edi].SAMID[8]),bl
	mov ebx,Init[ecx].SDA
	mov HIGHF[edi].SDA,ebx
	mov ebx,Init[ecx].SDB
	mov HIGHF[edi].SDB,ebx
	mov ebx,Init[ecx].SDC
	mov HIGHF[edi].SDC,ebx
	mov ebx,Init[ecx].SF
	mov HIGHF[edi].SF,ebx
	add edi,TYPE S
	jmp L5
L5:
	add ecx,TYPE S
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