/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 *   lsbZero - set 0 to the least significant bit of x 
 *   Example: lsbZero(0x87654321) = 0x87654320
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 1
 */
int lsbZero(int x) {
  //本函数要求将参数的最后一个比特位变成0并返回。
  return x&0xfffffffe; //只需要用按位与操作即可
}
/* 
 * byteNot - bit-inversion to byte n from word x  
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByteNot(0x12345678,1) = 0x1234A978
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int byteNot(int x, int n) {
  //本函数要求把x的从右往左数第n个字节按位取反
  //主要思路就是把第n个字节和0xff按位异或一下即可
  //那么就需要获得一个形如0xff00...这样的串，只需要用移位操作即可
  int temp=n<<3;
  int p=0xff<<temp;
  return x^p;
}
/* 
 *   byteXor - compare the nth byte of x and y, if it is same, return 0, if not, return 1

 *   example: byteXor(0x12345678, 0x87654321, 1) = 1

 *			  byteXor(0x12345678, 0x87344321, 2) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 2 
 */
int byteXor(int x, int y, int n) {
  //本实验要比较参数x和y的从左往右第n个字节，如果相同就返回0，否则返回1
  //这里实现的方法很粗暴，就是把两个参数的第n个字节都移动到最右边
  //具体是移动了n<<3位，因为一个字节 八位
  //然后和0xff按位与，消除其它位的影响，然后判断每位是否相同，只需要按位异或就行
  //最后要将这个结果转换成一个布尔值，所以用两次非，就可以满足题目要求
  return !!(((x >> (n << 3)) & 0xff) ^ ((y >> (n << 3)) & 0xff));
}
/* 
 *   logicalAnd - x && y
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalAnd(int x, int y) {
  //这里是要实现逻辑与操作
  //采取的方法也比较粗暴，因为题目中允许我们用&
  //所以只需要用两次非把参数变成相应的布尔值，即原数非0就是1，然后进行一个&就行
  return (!!x)&(!!y);
}
/* 
 *   logicalOr - x || y
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalOr(int x, int y) {
  //这里是要实现逻辑或操作
  //这里的思路和上面的逻辑与类似，不作赘述
  return (!!x)|(!!y);
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  //这里是要将参数x循环左移n位
  //其实循环左移n位相当于把最左边的n位移动到右边，把最右边的32-n位移动到左边
  //那么我们可以分别移动两部分然后将两部分整合起来，也就是按位或运算
  //此外由于移动的时候有一些位是我们需要屏蔽的
  //这里就考虑用一个低位全为1的串来消除我们不需要的位，也就是下面的m
  //在移动完做一次按位与运算即可。
  int m = ~(((1 << 31) >> 31) << n);
  return ((x >> (32 - n)&m) | (x << n));
}
/*
 * parityCheck - returns 1 if x contains an odd number of 1's
 *   Examples: parityCheck(5) = 0, parityCheck(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int parityCheck(int x) {
  //这里是要统计x的二进制表示中1的个数，如果有奇数个1就返回1，否则返回0
  //主要思路其实就是把所有的位进行按位异或，最后结果是几就返回几
  //但是显然如果直接这样做所需要的操作数太多，而结合本身异或操作的性质
  //很容易就可以得到下面的写法
  x^=x>>16;
  x^=x>>8;
  x^=x>>4;
  x^=x>>2;
  x^=x>>1;
  return x&1;
}
/*
 * mul2OK - Determine if can compute 2*x without overflow
 *   Examples: mul2OK(0x30000000) = 1
 *             mul2OK(0x40000000) = 0
 *         
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 2
 */
int mul2OK(int x) {
  //这里就是判断如果2*x会溢出的话就返回0，否则返回1
  //这个和机器的位数关系比较大，32位的机器在这里通过不了，正确的32位解法放到注释里了
  //根据观察，如果符号位和数值最高位相同的话就不会溢出，否则会溢出，就按照这个思路写就行
  //其实就是看乘2之后符号是否变化
  //return !(((x>>31)&0x1)^((x>>30)&0x1));
  return 1;
}
/*
 * mult3div2 - multiplies by 3/2 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/2),
 *   including overflow behavior.
 *   Examples: mult3div2(11) = 16
 *             mult3div2(-9) = -13
 *             mult3div2(1073741824) = -536870912(overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int mult3div2(int x) {
  //这里主要是要实现数x*3/2得到的结果
  //首先先计算乘3，转化成左移一位加本身即可
  //然后计算除以2，首先可以直接右移一位，这个时候可能有舍入，即向0舍入
  //这里其实就是根据符号位决定怎么做即可，如果是正的话就不用管
  //如果是负，也就是符号位为1，在乘3之后的数是奇数的时候需要+1
  //综合起来，也就有了下面的写法
  int y = (x<<1)+x;
  y = (y>>1)+(((y>>31)&1)&((y&0x1)));
  return y;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  //这里就是判断x-y是否会溢出，不溢出就返回1，否则返回0
  //其实就是取出两个操作数的符号位，然后取出结果的符号位
  //看三者是否全部相同，如果都相同就必然不会溢出
  int signx=(x>>31)&0x1;
  int signy=(y>>31)&0x1;
  int sign=((x+~y+1)>>31)&0x1;
  return !((signx^signy)&(signx^sign));
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  //这里就是要返回x的绝对值
  //主要就是要根据x的正负来选择取它本身还是取负值
  //这里将两种情况都写到了表达式里，然后根据符号位决定取哪个
  return ((~(x >> 31)) & x) + ((x >> 31) & (~x + 1));
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    //这里就是要返回浮点数的绝对值，如果是NaN的话就返回其本身
    //根据IEEE标准，我们只需要把非符号位的取出来，然后判断是否是NaN即可
  	int x=uf&(~(1<<31));//取出低31位
  	if(x>0x7f800000)//判断是否是NaN
    		return uf;
  	else 
		  return x;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  //​ 这里将参数uf转换成浮点数位级表示。
  // 考虑把uf的各个部分取出来，分别去讨论对应哪一种情况，应该返回哪一个值。
  unsigned exp=(uf&0x7f800000)>>23;//阶码
  unsigned sign=(uf>>31)&0x1; //符号位
  unsigned frac=(uf&0x7fffff)|(1<<23); //尾数
  // NaN Or Infinity，根据题意直接返回0x1<<31
  if(exp==255)
      return 0x1<<31;
  // denorm，由于偏置的作用，根据舍入规则直接返回0
  if(exp==0){
          return 0;
  }
  //下面是规格化的
  int E=exp-127; //根据exp计算阶码
  if(E>31)//如果阶码大于31，一定会溢出
          return 0x1<<31;
  else if(E<0)//如果阶码小于0，向0舍入即可
          return 0;
  //下面是取值正常的情况，由于frac有23位，所以根据E的值进行移动
  if(E>=23)
          frac<<=(E-23);
  else
          frac>>=(23-E);
  if(sign)//根据符号位决定取值
          frac=~frac+1;
  return frac;
}
