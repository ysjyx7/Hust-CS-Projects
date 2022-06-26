.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib 
 printf          PROTO C :VARARG
 scanf    PROTO C :vararg
 Scopy proto:dword,:dword
 func proto:dword
 MIDprint proto
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 public lpFmt
 public lpFmt3
 public MIDF
 public f
 public y
 strcmp macro str1,str2,flag
	local S0,S1,S2
	push eax
	push ebx
	mov bh,0
	mov eax,0
S0:
	mov bh,str1[eax]
	cmp bh,str2[eax]
	jne S1
	inc eax
	cmp bh,0
	jne S0
	mov flag,1
	jmp S2
S1:
	mov flag,0
S2:
	pop ebx
	pop eax
	endm
S struct
	SAMID DB 9 dup(0)
	SDA   DD 0
	SDB   DD 0
	SDC   DD 0
	SF    DD 0
S ENDS
.DATA
  lpFmt	db	"%s",0ah, 0dh, 0
  lpFmt1  db  "%s",0
  lpFmt2 db "%s:%s",0ah,0dh,0
  lpFmt3 db "%d",0ah,0dh,0
  a dd 0
  x dd 0
  y dd 0
  z dd 0
  f dd 0
  de dd 0
  N dd 6
  so dd 0
  LOWF S 5 dup(<>)
  MIDF S 5 dup(<>)
  HIGHF S 5 dup(<>)
  INIT S <'00000000',2539,6,1,>,<'00000001',2539,6,1,>,<'00000002',2540,1,1,>,<'00000003',2540,1000,1,>,
		<'00000004',2540,44,44,>,<'00000005',2540,666,666,>,<'00000006',5,4,1,>
  STR1 db "please enter your username",0
  STR2 db "please enter your password",0
  str3 db "Rerun or Quit(R/Q)",0
  password   db  '123456',0
  username db 'ysj',0
  output1 db 'OK!',0
  output2 db 'Incorrect Input!',0
  flag db 0
  error db 0
  opt db ?
  input   db  7 dup(0)   
.STACK 200
.CODE
main proc c
L0:
   invoke printf,offset lpFmt,OFFSET STR1
   invoke scanf,offset lpFmt1,offset input
   strcmp username,input,flag
   cmp flag,1
   jne L1
   mov error,0
   invoke printf,offset lpFmt,OFFSET STR2
   invoke scanf,offset lpFmt1,offset input
   strcmp password,input,flag
   cmp flag,1
   jne L1
   jmp L2
L1:
	invoke printf,offset lpFmt,OFFSET output2
	inc error
	cmp error,3
	je exit
	jmp L0
L2:
	mov a,0
	mov x,0
	mov y,0
	mov z,0
	mov f,0
L3:
    cmp a,6
	je L7
	mov eax,a
	IMUL EAX,TYPE S
	lea esi,INIT[eax]
	mov so,esi
	mov f,0
	invoke func,so
	INC a
	cmp f,100
	jl L4
	je L5
	jg L6
L4:
	mov eax,x
	imul eax,TYPE S
	inc x
	lea esi,LOWF[eax]
	mov de,esi
	invoke Scopy,de,so
	jmp L3
L5:
	mov eax,y
	imul eax,TYPE S
	inc y
	lea esi,MIDF[eax]
	mov de,esi
	invoke Scopy,de,so
	jmp L3
L6:
	mov eax,z
	imul eax,TYPE S
	inc z
	lea esi,HIGHF[eax]
	mov de,esi
	invoke Scopy,de,so
	jmp L3
L7:
	call MIDprint	
	invoke printf,offset lpFmt,offset str3
	invoke scanf,offset lpFmt2,offset opt
	mov al,opt
	cmp al,82
	je L2
	cmp al,114
	je L2
exit:
   invoke ExitProcess, 0
main endp
END
