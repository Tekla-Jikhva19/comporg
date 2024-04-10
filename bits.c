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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* Compute the bitwise AND of x and y using only ~ and |.
       We use De Morgan's Law to express the bitwise AND operation
       as the negation of the OR of the negations of x and y. */
  return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /* Shift x to the right by n*8 bits to bring the byte of interest to the least significant position.
    Then, use a mask (0xFF) to extract the least significant byte, which corresponds to byte n.*/

int shiftAmount = n << 3; // n * 8
    int shifted = x >> shiftAmount;

int mask = 0xFF;
    return shifted & mask;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*Shift x to the right by n bits using arithmetic shift,
  then create a mask to clear the sign extension 
  and finally apply the mask to perform a logical shift.
  */

   int shifted = x >> n;
   int mask = ~(1 << 31 >> n << 1);
    
   return shifted & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /*To count the number of set (1) bits in the input word, 
  we divide it into bytes and count the set bits in each byte separately. 
  Then, we add up these counts to get the total number of set bits in the word.
  */
  // Create a mask to extract the least significant bit of each byte
	int mask = 0x1 | (0x1 << 8) | (0x1 << 16) | (0x1 << 24);

	// Count the number of set bits in each byte of x
	int count = x & mask;
	count += (x >> 1) & mask;
	count += (x >> 2) & mask;
	count += (x >> 3) & mask;
	count += (x >> 4) & mask;
	count += (x >> 5) & mask;
	count += (x >> 6) & mask;
	count += (x >> 7) & mask;

	// Sum the counts of each byte to get the total count
	count = (count & 0xFF) + ((count >> 8) & 0xFF) + ((count >> 16) & 0xFF) + ((count >> 24) & 0xFF);

	return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /*The function checks if the input number x is zero or not. 
  If x is zero, it returns 1, indicating true. Otherwise, it returns 0, indicating false.
  */
  int sign = (x | (~x + 1)) >> 31; // Get the sign of x
	return sign + 1;
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //The function returns the smallest negative integer.
  return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*The function checks if the number x can fit into n bits. 
  If it can, it returns 1; otherwise, it returns 0.
  */
   	int shift = (1 << (n + ~0)); // Compute the shift value
 	  int shifted_x = x >> 31; // Get the sign of x
   	return !(((x ^ shifted_x) + shift) >> n); // Check if x can be represented as an n-bit integer
 }

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  /*The function divides the number x by 2^n, rounding towards zero. 
  It adjusts x by adding a bias if it's negative, and then performs the division.
  */
    int sign = x >> 31; // Get the sign of x
	int bias = (1 << n) + ~0; // Compute the bias based on n
	return (x + (sign & bias)) >> n; // Add bias if x is negative, then perform the division
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*The function returns the negation of the input number x 
  by flipping all its bits and adding 1.*/
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  // check if x is positive by checking if the sign bit is 0 and x is not 0 
    // Return 0 otherwise
  return !((x >> 31) | !x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
    int isLessOrEqual(int x, int y) {
      /*The function determines if x is less than or equal to y. 
      It first calculates the sign of x and y, then computes the sign difference between x and y. 
      Finally, it combines the sign information and the sign difference to check if x is less than or equal to y.*/

  int sing_of_x = x >> 31;
	int sign_of_y = y >> 31;
	int sign_difference = (y + (~x + 1)) >> 31; // Get the sign of (y - x)
	return ((sing_of_x & !sign_of_y) | (!(sing_of_x ^ sign_of_y) & !sign_difference)) & 1; // Check if x <= y
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  /*The function calculates the highest power of 2 that is less than or equal to the input number x. 
  It does this by checking which bits are set in x, 
  starting from the most significant bit, 
  and counting how many times x can be divided by 2 until it becomes 0.*/
      int result = 0;
result = (!!(x>> 16)) << 4; //Check if the most significant 16 bits have any set bits
result = result + ((!!(x >> (result +8))) << 3); //Check if the next 8 bits have any set bits
result = result + ((!!(x >> (result +4))) << 2); //Check if the next 4 bits have any set bits
result = result + ((!!(x >> (result +2))) << 1); //Check if the next 2 bits have any set bits
result = result + (!!(x >> (result +1))); //Check if the last bit has any set bits
  return result;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  /*The function float_neg negates the input floating-point number f by flipping its sign bit. 
  It also checks if f is NaN (Not a Number) and returns f unchanged in that case.
  */
        unsigned int result = uf ^ 0x80000000; //Toggle the sign bit
        unsigned int exp = uf & 0x7F800000; // Extract the exponent bits
        unsigned int frac = uf & 0x007FFFFF; //Extract the fraction bits

        if (exp == 0x7F800000 && frac != 0) {
          return uf; //Return the argument if it is Nan
        }
        else
        {
          return result; //Return the negated value

        }
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  /*The function converts an integer x to its single-precision 
   floating-point representation by determining its sign, exponent, and fractional parts.
   It then combines these parts to produce the final result.*/
  unsigned int exponent, fraction, sign_bit, shift_count, result;

  if (!x) {
     return x;
}
 sign_bit = 0x80000000;
 sign_bit &= x; //Extract the sign bit

if (sign_bit) {
  x = -x;

}

exponent = x;
	shift_count = 126;
	
	while (exponent) {
		exponent >>= 1;
		shift_count += 1; // Calculate the exponent by counting the number of shifts
	}
	
	sign_bit += (shift_count << 23);
	x <<= (157 - shift_count); // Shift x to the left to align the most significant bit
	
	fraction = 0x007FFFFF; // Mask to extract the fractional part

	result = x >> 7; // Extract the fractional part
	
	result &= fraction; // Apply mask to get the fractional part
	sign_bit += result;
	
	sign_bit += (0x40 & x) && (0x40 ^ (x & 0xff)); // Round the result
	
	return sign_bit; // Return the final result
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  /*The function float_twice doubles the input floating-point number f by changing its bit pattern. 
  It looks at the sign and exponent parts of the number. 
  If the number is special (like NaN), it just gives back the input. 
  If it's a small number (with a small exponent), it multiplies it by 2 by shifting its bits. 
  If it's a regular number, it doubles it by increasing its exponent. 
  This way, the function correctly handles different kinds of numbers to give the right result.
*/
  unsigned int sign = uf & 0x80000000; // Extract sign bit
	unsigned int exponent = uf & 0x7F800000; // Extract exponent bits
	
	if (exponent == 0x7F800000) { // Check if NaN
		return uf;
	}
	
	if (!exponent) { // Denormalized number
		return sign | (uf << 1); // Multiply by 2 by shifting left
	}
	
	return uf + (1 << 23); // Multiply by 2 by incrementing the exponent

}
