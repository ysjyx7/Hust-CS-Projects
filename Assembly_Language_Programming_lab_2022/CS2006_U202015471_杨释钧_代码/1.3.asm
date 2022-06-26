.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :VARARG
 scanf    PROTO C :vararg
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib

.DATA
lpFmt	db	"%s",0ah, 0dh, 0
lpFmt1  db  "%s",0
  STR1 db "please enter a password of length 6",0
  password   db  '123456',0
  output1 db 'OK!',0
  output2 db 'Incorrect Password！',0
  input   db  7 dup(0)   ; 
.STACK 200
.CODE
main proc c
   invoke printf,offset lpFmt,OFFSET STR1
   invoke scanf,offset lpFmt1,offset input
   mov ECX,0
   mov ebp,0
L0:
   inc ebp
   cmp input[ebp],0
   jne L0
   cmp ebp,6
   jne L1
L2:
   mov ah,input[ECX]
   cmp ah,password[ECX]
   jne L1
   inc ECX
   cmp ECX,5
   jbe L2
   invoke printf,offset lpFmt,OFFSET output1
   invoke ExitProcess, 0
L1:
   invoke printf,offset lpFmt,OFFSET output2
   invoke ExitProcess, 0
main endp
END