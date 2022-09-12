#############################################################
#测试jal,jalr指令，
#############################################################
.text
 addi s1,zero, 1   #测试jal,jalrr指令
 j jmp_next1       #jal x0,8
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next1:
 j jmp_next2
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next2:
 j jmp_next3
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next3:
 j jmp_next4
 addi s1,zero, 1
 addi s2,zero, 2
 addi s3,zero, 3
jmp_next4:jal jmp_count

#移位测试  需要支持超addi,sll,add,ecall,srl,sll,sra,beq,j,ecall    revise date:2015/12/16 tiger

.text
addi s0,zero,1     #简单移位，循环测试，0号区域显示的是初始值1左移1位重复15次的值，1号区域是累加值
addi s1,zero,1  
slli s1, s1, 31   #逻辑左移31位 s1=0x80000000
 

###################################################################
#                逻辑左移测试 
# 显示区域依次显示0x80000000 0x20000000 0x08000000 0x02000000 0x00800000 0x00200000 0x00080000 0x00020000 0x00008000 0x00002000 0x00000800 0x00000200 0x00000080 0x00000020 0x00000008 0x00000002 0x00000000  
###################################################################
LogicalRightShift:            #逻辑右移测试，将最高位1逐位向右右移直至结果为零

add    a0,zero,s1       #display s1
addi   a7,zero,34        # display hex
ecall                 # we are out of here.  
     
srli s1, s1, 2   
beq s1, zero, shift_next1
j LogicalRightShift

shift_next1:

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


###################################################################
#                逻辑右移测试 
# 显示区域依次显示0x00000004 0x00000010 0x00000040 0x00000100 0x00000400 0x00001000 0x00004000 0x00010000 0x00040000 0x00100000 0x00400000 0x01000000 0x04000000 0x10000000 0x40000000 0x00000000 
###################################################################

addi s1,zero, 1   
LogicalLeftShift:         #逻辑左移测试，将最低位1逐位向左移直至结果为零
slli s1, s1, 2  

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  
      
beq s1, zero, ArithRightShift
j LogicalLeftShift


###################################################################
#                算术右移测试 
# 显示区域依次显示0x80000000 0xf0000000 0xff000000 0xfff00000 0xffff0000 0xfffff000 0xffffff00 0xfffffff0 0xffffffff 
###################################################################
ArithRightShift:          #算术右移测试，#算术移位测试，80000000算术右移，依次显示为F0000000,FF000000,FFF00000,FFFF0000直至FFFFFFFF

addi s1,zero,1  
slli s1, s1, 31   #逻辑左移31位 s1=0x80000000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  

srai s1, s1, 3    #s1=0X80000000-->0XF0000000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    #0XF0000000-->0XFF000000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    #0XFF000000-->0XFFF00000

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  

srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  

srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    

add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.  


srai s1, s1, 4    


add    a0,zero,s1       #display s1
addi   a7,zero,34         # display hex
ecall                 # we are out of here.    

#############################################################
#走马灯测试,测试addi,andi,sll,srl,sra,or,ori,nor,ecall  LED按走马灯方式来回显示数据
#############################################################

.text
addi s0,zero,1 
slli s3, s0, 31      # s3=0x80000000
srai s3, s3, 31      # s3=0xFFFFFFFF   
add s0,zero,zero   # s0=0         
addi s2,zero,12 

addi s6,zero,3  #走马灯计数
zmd_loop:

addi s0, s0, 1    #计算下一个走马灯的数据
andi s0, s0, 15  

#######################################
addi t0,zero,8    
addi t1,zero,1
left:

slli s3, s3, 4   #走马灯左移
or s3, s3, s0

add    a0,zero,s3       # display s3
addi   a7,zero,34         # system call for LED display 
ecall                 # display 

sub t0,t0,t1
bne t0,zero,left
#######################################

addi s0, s0, 1   #计算下一个走马灯的数据
addi t6,zero,15
and s0, s0, t6
slli s0, s0, 28     

addi t0,zero,8
addi t1,zero,1

zmd_right:

srli s3, s3, 4  #走马灯右移
or s3, s3, s0

add    a0,zero,s3       # display s3
addi   a7,zero,34         # system call for LED display 
ecall                 # display 

sub t0,t0,t1
bne t0,zero,zmd_right
srli s0, s0, 28  
#######################################

sub s6,s6,t1
beq s6,zero, exit
j zmd_loop

exit:

add t0,zero,zero
xori t0,t0,-1      #test r  xori
slli t0,t0,8
ori t0,t0,255

add   a0,zero,t0       # display t0
addi   a7,zero,34         # system call for LED display 
ecall                 # display 

#################################################################################
#本程序实现0-15号字单元的降序排序,此程序可在rars 仿真器中运行
#运行时请将rars Setting中的Memory Configuration设置为Compact，data at address 0
#################################################################################
 .text
sort_init:
 addi s0,zero,-1
 addi s1,zero,0
 
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
 sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
  sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
    sw s0,0(s1)
 addi s0,s0,1
 addi s1,s1,4
   
 addi s0,s0,1
 
 add s0,zero,zero   
 addi s1,zero,60   #排序区间
sort_loop:
 lw s3,0(s0)     
 lw s4,0(s1)
 slt t0,s3,s4
 beq t0,zero,sort_next   #降序排序
 sw s3, 0(s1)
 sw s4, 0(s0)   
sort_next:
 addi s1, s1, -4   
 bne s0, s1, sort_loop  
 
 add    a0,zero,s0       #display s0
 addi   a7,zero,34         # display hex
 ecall                 # we are out of here.  DISP: disp r0, 0
 
 addi s0,s0,4
 addi s1,zero,60
 bne s0, s1, sort_loop


 addi   a7,zero,50         # system call for pause
 ecall                  # we are out of here.   
 
 
#############################################
# insert your ccmb benchmark program here!!!
#############################################
#sll   revise date:2018/3/12 tiger
#依次输出  0x00000876 0x00008760 0x00087600 0x00876000 0x08760000 0x87600000 0x76000000 0x60000000 0x00000000

.text

addi t0,zero,1     
addi t1,zero,3     
addi s1,zero,  0x8
slli s1,s1,8
addi s1,s1,0x76     

add a0,zero,s1           
addi a7,zero,34         # system call for print
ecall                  # print

addi t3,zero,8

sll_branch:
sll s1,s1,t0       #1
sll s1,s1,t1       #娴嬭瘯
add a0,zero,s1          
addi a7,zero,34         # system call for print
ecall                  # print
addi t3,t3, -1    
bne t3,zero,sll_branch

addi   a7,zero,10         # system call for exit
ecall                  # we are out of here.   





#sra移位测试    revise date:2021/1/24 tiger
#依次输出  0x87600000 0xf8760000 0xff876000 0xfff87600 0xffff8760 0xfffff876 0xffffff87 0xfffffff8 0xffffffff

.text

addi t0,zero,1     #sll 移位次数
addi t1,zero,3     #sll 移位次数
addi s1,zero,  0x8
slli s1,s1,8
addi s1,s1,0x76     

slli s1,s1,20     #

add a0,zero,s1           
addi a7,zero,34         # system call for print
ecall                  # print

addi t3,zero,8

sra_branch:
sra s1,s1,t0     #先移1位
sra s1,s1,t1     #再移3位
add a0,zero,s1          
addi a7,zero,34         # system call for print
ecall                  # print
addi t3,t3, -1    
bne t3,zero,sra_branch   #循环8次

addi   a7,zero,10         # system call for exit
ecall                  # we are out of here.   



#SB 测试    revise date:2018/3/14 tiger
#依次输出   0x00000000 0x00000001 0x00000002 0x00000003 0x00000004 0x00000005 0x00000006 0x00000007 0x00000008 0x00000009 0x0000000a 0x0000000b 0x0000000c 0x0000000d 0x0000000e 0x0000000f 0x00000010 0x00000011 0x00000012 0x00000013 0x00000014 0x00000015 0x00000016 0x00000017 0x00000018 0x00000019 0x0000001a 0x0000001b 0x0000001c 0x0000001d 0x0000001e 0x0000001f 0x03020100 0x07060504 0x0b0a0908 0x0f0e0d0c 0x13121110 0x17161514 0x1b1a1918 0x1f1e1d1c
.text

addi t1,zero,0     #init_addr 
addi t3,zero,32     #counter

#sb写入 01,02,03,04
addi s1,zero, 0x00  #
addi s2,zero, 0x01  #

sb_store:
sb s1,(t1)
add a0,zero,s1          
addi a7,zero,34        # system call for print
ecall                  # print

add s1,s1,s2          #data +1
addi t1,t1,1           # addr ++  
addi t3,t3,-1          #counter
bne t3,zero,sb_store

addi t3,zero,8
addi t1,zero,0    # addr   
sb_branch:
lw s1,(t1)       #读出数据 
add a0,zero,s1          
addi a7,zero,34        # system call for print
ecall                  # print
addi t1,t1,4    
addi t3,t3, -1    
bne t3,zero,sb_branch

addi   a7,zero,10      # system call for exit
ecall                  # we are out of here.   


#bltu 测试    小于等于零跳转     累加运算，从负数开始向零运算  revise date:2022/1/24 tiger  
#依次输出0xfffffff1 0xfffffff2 0xfffffff3 0xfffffff4 0xfffffff5 0xfffffff6 0xfffffff7 0xfffffff8 0xfffffff9 0xfffffffa 0xfffffffb 0xfffffffc 0xfffffffd 0xfffffffe 0xffffffff 0x00000000
.text

addi s1,zero,-15       #初始值
bltu_branch:
add a0,zero,s1          
addi a7,zero,34         
ecall                  #输出当前值
addi s1,s1,1  
bltu zero,s1,bltu_branch   
add a0,zero,s1          
addi a7,zero,34         
ecall                  #输出当前值
end:
addi   a7,zero,10         
ecall                  # 暂停或退出


                 
 addi   a7,zero,10         # system call for exit
 ecall                  # we are out of here.   
 
 #处理器实现中请用停机指令实现ecall

jmp_count: addi s0,zero, 0
       addi s0,s0, 1
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 2
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 3
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 4       
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  
       
       addi s0,s0, 5              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  

       addi s0,s0, 6              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  

       addi s0,s0, 7              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       ecall                 # we are out of here.  

       addi s0,s0, 8              
       add    a0,zero,s0      
       addi   a7,zero,34         # display hex
       addi   a7,zero,34         # display hex       
       ecall                 # we are out of here.  
       
       ret  #persudo instruction  jalr x0,x1,0
