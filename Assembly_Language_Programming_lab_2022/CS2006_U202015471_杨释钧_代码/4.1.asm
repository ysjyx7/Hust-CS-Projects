.386
STACK SEGMENT USE16 STACK ; 主程序的堆栈段
DB 200 DUP(0)
STACK ENDS
;
CODE SEGMENT USE16
ASSUME CS: CODE,DS: CODE,SS: STACK
; 新的 INT 08H 使用的变量
COUNT DB 18 ; “滴答”计数
HOUR DB ?,?,':' ; 时的 ASCII 码
MIN DB ?,?,':' ; 分的 ASCII 码
SEC DB ?,? ; 秒的 ASCII 码
BUF_LEN = $-HOUR ; 计算显示信息长度
CURSOR DW ? ; 原光标位置
OLD_INT DW 0,0 ; 原 INT 08H 的中断矢量
XLOC DB 2
YLOC DB 1

; 新的 INT 08H 的代码
NEW08H PROC FAR
    JMP $+6
    DW 0,0
    PUSHF
    CALL DWORD PTR CS:OLD_INT
    ; 完成原功能(变量在汇编后使用的默认段寄存器
    ; 为 DS,故必须加段前缀 CS: )
    DEC CS:COUNT ; (倒)计数
    JZ DISP ; 计满 18 次,转时钟显示
    IRET ; 未计满,中断返回
    DISP: MOV CS: COUNT,18 ; 重置计数初值
    STI ; 开中断
    PUSHA ; 保护现场
    PUSH DS
    PUSH ES
    MOV AX,CS ; 将 DS、ES 指向 CS
    MOV DS,AX
    MOV ES,AX
    CALL GET_TIME ; 获取当前时间,并转换成 ASCII 码
    MOV BH,0 ; 获取 0 号显示页面当前的光标位置
    MOV AH,3
    INT 10H
    MOV CURSOR,DX ; 保存原光标位置
    MOV BP,OFFSET HOUR ; ES: [BP]指向显示信息的起始地址
    MOV BH,0 ; 显示到 0 号页面
    ; MOV DH,0 ; 显示在 0 行
    ; MOV DL,80 -BUF_LEN ; 显示在最后几列(光标位置设到右上角)
    MOV DH,YLOC
    MOV DL,XLOC
    MOV BL,70H ; 显示字符的属性(白色)
    MOV CX,BUF_LEN ; 显示的字符串长度
    MOV AL,0 ; BL 包含显示属性,写后光标不动
    MOV AH,13H ; 调用显示字符串的功能
    INT 10H ; 在右上角显示出当前时间
    MOV BH,0 ; 对 0 号页面操作
    MOV DX,CURSOR ; 恢复原来的光标位置
    MOV AH,2 ; 设置光标位置的功能号
    INT 10H ; 还原光标位置(保证主程序的光标位置不受影
    ; 响)
    POP ES
    POP DS
    POPA ; 恢复现场
    IRET ; 中断返回
NEW08H ENDP


; 取时间子程序。 从 RT/CMOS RAM 中取得时分秒并转化成 ASCII 码存放到对应变量中
GET_TIME PROC
    MOV AL,4 ; 4 是"时"信息的偏移地址
    OUT 70H,AL ; 设定将要访问的单元是偏移值为 4 的“时”信息
    NOP
    NOP
    IN AL,71H ; 读取“时”信息
    MOV AH,AL ; 将 2 位压缩的 BCD 码转换成未压缩的 BCD 码
    AND AL,0FH
    SHR AH,4
    ADD AX,3030H ; 转换成对应的 ASCII 码
    XCHG AH,AL ; 高位放在前面显示
    MOV WORD PTR HOUR,AX
    ; 保存到 HOUR 变量指示的前 2 个字节中
    MOV AL,2 ; 2 是“分”信息的偏移地址
    OUT 70H,AL
    JMP $ +2
    IN AL,71H ; 读取"分"信息
    MOV AH,AL ; 转换成对应的 ASCII 码
    AND AL,0FH
    SHR AH,4
    ADD AX,3030H
    XCHG AH,AL
    MOV WORD PTR MIN,AX ; 保存到 MIN 变量指示的前 2 个字节中
    MOV AL,0 ; 0 是“秒”信息的偏移地址
    OUT 70H,AL
    JMP $ +2
    IN AL,71H ; 读取“秒”信息
    MOV AH,AL ; 转换成对应的 ASCII 码
    AND AL,0FH
    SHR AH,4
    ADD AX,3030H
    XCHG AH,AL
    MOV WORD PTR SEC,AX ; 保存到 SEC 变量指示的 2 个字节中
    RET
GET_TIME ENDP


; 初始化(中断处理程序的安装)及主程序
BEGIN:
; LEA DI,[$+1]
PUSH CS
POP DS

; 如果已经安装，则退出程序
; MOV AX,35E1H ; 获取原 F2H 的中断矢量
; INT 21H
XOR AX,AX
PUSH DS
MOV DS,AX
MOV BX,DS:[0E1H*4]
CMP BX,1145H
POP DS
JE HASINST

; 安装中断处理程序
MOV AX,3508H ; 获取原 08H 的中断矢量
INT 21H
MOV OLD_INT,BX ; 保存中断矢量
MOV OLD_INT[2],ES
;保存一个中断矢量，在下次运行中可以发现已经在运行力
XOR AX,AX
PUSH DS
MOV DS,AX
MOV AX,1145H
MOV DS:[0E1H*4],AX
POP DS

; 设置新的 08H 中断矢量
; MOV DX,OFFSET NEW08H
; MOV AX,2508H
; INT 21H
XOR AX,AX
PUSH DS
MOV DS,AX
MOV AX,OFFSET NEW08H
MOV DS:[08H*4],AX
MOV AX,CS
MOV DS:[08H*4+2],AX
POP DS

JMP HASNTINST

HASINST:
MOV AX,0200H
MOV DL,'X'
INT 21H
JMP EXITPROC

HASNTINST:
MOV AH,02H
MOV DL,'L'
INT 21H
MOV DX,OFFSET BEGIN+15
MOV CL,4
SHR DX,CL
ADD DX,100H
MOV AX,3100H
INT 21H


EXITPROC:
MOV AX,4C00H;EXIT
; MOV AX,3100H;STAY
INT 21H ; 退出
CODE ENDS
END BEGIN
