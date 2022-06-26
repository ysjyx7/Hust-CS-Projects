.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :VARARG
 scanf    PROTO C :vararg
 includelib  libcmt.lib
 GetTickCount   Proto stdcall
 includelib  legacy_stdio_definitions.lib
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
  so dd 0
  startTime dd 0
  LOWF S 5 dup(<>)
  MIDF S 5 dup(<>)
  HIGHF S 5 dup(<>)
  INIT S <'00000001',2540,1,1000,>,<'00000002',2540,1,1,>,<'00000003',2540,1000,1,>,
		<'00000004',2540,44,44,>,<'00000005',2540,666,666,>
  STR1 db "please enter your username",0
  STR2 db "please enter your password",0
  password   db  ('1'-20H)*3  ;真实密码为"123456"，采用函数（X-20H）*3对保存的密码进行编码
			 db  ('2'-20H)*3
			 db  ('3'-20H)*3
			 db  ('4'-20H)*3
			 db  ('5'-20H)*3
			 db  ('6'-20H)*3
			 db  0  
  username db 'ysj',0
  output1 db 'OK!',0
  output2 db 'Incorrect Input!',0
  flag db 0
  error db 0
  input   db  10 dup(0) 
  P1 dd 0
  P2 dd 0
  E1 dd 0
.STACK 200
.CODE
Scopy proc  des:dword,sou:dword
	push esi
	push edi
	push eax
	push ebx
	mov ebx,0
	mov esi,sou
	mov edi,des
S0:
	mov eax,[esi+ebx*4]
	mov [edi+ebx*4],eax
	inc ebx
	cmp ebx,6
	jne S0
	mov al,[esi+24]
	mov [edi+24],al
	pop ebx
	pop eax
	pop edi
	pop esi
	ret
Scopy endp
func proc data:dword,fx:dword
	push esi
	push ebx
	mov esi,data
	mov	ebx,[esi+9]
	imul ebx,5
	sub ebx,[esi+17]
	add ebx,[esi+13]
	add	ebx,100
	shr ebx,7
	mov [esi+21],ebx
	mov fx,ebx
	pop ebx
	pop esi
	ret
func endp
MIDprint proc 
	 push esi
	 push ebx
	 mov ebx,0
	 lea esi,MIDF
L0:
	 invoke printf,offset lpFmt,esi
	 invoke printf,offset lpFmt3,MIDF[ebx].SDA
	 invoke printf,offset lpFmt3,MIDF[ebx].SDB
	 invoke printf,offset lpFmt3,MIDF[ebx].SDC
	 invoke printf,offset lpFmt3,MIDF[ebx].SF
	 add ebx,TYPE S
	 add esi,TYPE S
	 cmp ebx,75
	 jne L0
	 pop ebx
	 pop esi
	 ret
MIDprint endp
main proc c
   mov P1,offset Pass  ;建立地址表用于间接转移,但是在windows下无法使用
   mov P2,offset L2
   mov E1,offset exit
L0:
   invoke printf,offset lpFmt,OFFSET STR1
   invoke scanf,offset lpFmt1,offset input
   strcmp username,input,flag
   cmp flag,1
   jne L1
   invoke printf,offset lpFmt,OFFSET STR2
   invoke scanf,offset lpFmt1,offset input
   invoke GetTickCount   ;开始计时
   mov startTime,eax
   mov eax,0123H    ;无关代码，减弱程序可读性，增大破解难度
   mov ebx,0456H
   add ax,bx
   add ax,ax
   mov ax,4c00H
   invoke GetTickCount    ;结束计时
   sub eax,startTime
   cmp eax,10
   ja exit
OK:
   push offset P0          ;堆栈检查单步调试
   pop ecx
   mov ecx,ebx
   add ecx,ecx
   mov ebx,[esp-4]
   jmp ebx
P0:       ;对输入的字符串进行加密操作
   sub input[eax],20H
   mov bl,input[eax]
   imul bx,3
   mov input[eax],bl
   inc eax
   cmp eax,6
   jnz P0 
Pass:
   push eax
   invoke GetTickCount
   mov startTime,eax
   strcmp password,input,flag
   invoke GetTickCount
   sub eax,startTime
   cmp eax,100
   ja exit
   pop eax
   cmp flag,1
   jne L1
   jmp P2
L1:
	invoke printf,offset lpFmt,OFFSET output2
	inc error
	cmp error,3
	je exit
	jmp L0
L2:
	invoke printf,offset lpFmt,OFFSET output1
	mov a,0
	mov x,0
	mov y,0
	mov z,0
	mov f,0
L3:
	mov eax,a
	lea esi,INIT[eax]
	mov so,esi
	invoke func,so,f
	cmp f,100
	jl L4
	je L5
	jg L6
L4:
	mov eax,x
	lea esi,LOWF[eax]
	mov de,esi
	invoke Scopy,de,so
L5:
	mov eax,y
	lea esi,MIDF[eax]
	mov de,esi
	invoke Scopy,de,so
L6:
	mov eax,z
	lea esi,HIGHF[eax]
	mov de,esi
	invoke Scopy,de,so
exit:
   invoke ExitProcess, 0
main endp
END