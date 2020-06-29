/* 
 * Engineering 96C Assignment No. 1
 * 
 * Summer 2020
 * 
 * bits.c - Source file with your solutions to the Lab.
 *
 * WARNING: Do not include the <stdio.h> header. You can still use
 * printf for debugging without including <stdio.h>, although you
 * might get a compiler warning. In general, it's not good practice
 * to ignore compiler warnings, but in this case it's OK.  
 */
 

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this assignment by
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

NOTES:
  1. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     Note that '=' is not counted; you may use as many of these as you
     want without penalty.
  2. Use the btest test harness to check your functions for correctness.
  3. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according the coding rules.
 */

#endif

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 * and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 *   
 *   x: sign bit 0, others 1  
 *      '0b1111111111111111111111111111111'
 *      '0x7f'
 * 
 *    unsigned int max = ~0;
 *    int  max  = ~0 >> 1
 */
int isTmax(int x) {
  
    int max = 0x7fffffff ^ x ;
     
    return !( ((max|(max+0x7FFFFFFF)) >>31 ) &1 );
}

/* 
 * fitsShort - return 1 if x can be represented as a 
 * 16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 1
 */
int fitsShort(int x) {

     int same  = x<<16>>16 ^ x;
     return ! (  ((same|(same + 0x7FFFFFFF)) >>31 ) &1  ) ;
 
}

/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {

    int n_shift = n << 3;
    int m_shift = m << 3;
    return x ^ (x & ((255 << n_shift) ^ (255 << m_shift))) ^ ((((x & (255 << n_shift)) >> n_shift) & 255) << m_shift) ^ ((((x & (255 << m_shift)) >> m_shift) & 255) << n_shift);

   
}

/*  signed !!  check middle 000?
 * fitsBits - return 1 if x can be represented as an 
 * n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    
    int shift = 33 + ~n;
    return !(x ^ ((x << shift) >> shift));
}

/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int isGreater(int x, int y) {

    int diff = x ^ y;
    diff |= diff >> 1;
    diff |= diff >> 2;
    diff |= diff >> 4;
    diff |= diff >> 8;
    diff |= diff >> 16;

    diff &= ~(diff >> 1) | 0x80000000;
    diff &= (x ^ 0x80000000) & (y ^ 0x7fffffff);

    return !!diff;
    
}

/*   bit rotate
 * rotateRight - Rotate x to the right by n  (2's)
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 15
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
    
    int DROPPED_LSB;

    // The effective rotation
    n %= 32;


    // Loop till rotation becomes 0
    while(n--)
    {
        // Get LSB of num before it gets dropped
        DROPPED_LSB = x & 1;

        // Right shift num by 1 and  Clear its MSB
        x = (x >> 1) & (~(1 << 31));

        // Set its dropped LSB as new MSB
        x = x | (DROPPED_LSB << 31);
    }

    return x;
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int bitParity(int x) {
  x = x ^ (x >> 1);
  x = x ^ (x >> 2);
  x = x ^ (x >> 4);
  x = x ^ (x >> 8);
  x = x ^ (x >> 16);
  return x & 1;
}