# Binary Representation Continued

## Negative Integers
### 2's Complement

Binary representation formula

<span style="background-color: #0F0FFF"> -x = ~x + 1 </span>

### Examples

1. 10 == 0b00001010

2. -10

> flip the bits: 0b11110101 \
> add 1: 0b11110110

3. 0 == 0b00000000

4. -0
> flip the bits: 0b11111111 \
> add 1: 0b00000000

### Notes
positive/zero numbers - leading/first bit is 0 \
negative numbers - leading bit is 1

### Examples

2. Assume that the following hexadecimal values are 16-bit twos-complement. Convert each to the corresponding decimal value.

    ii. 0x0444
    > binary - 0b0000010001000100 \
    > leading bit is a 0, hence this is a positive number \
    > decimal - 1092

    iii. 0x8000
    > binary - 0b 1000 0000 0000 0000 \
    > leading bit is a 1, hence this is a negative number \
    > this is the binary representation for ~x + 1, undo the operations to find the decimal value for -x

    > minus 1 from 0b 1000 0000 0000 0000: 0b 0111 1111 1111 1111 -> this is the binary representation for ~x

    > flip the bits: 0b 1000 0000 0000 0000 -> this is the binary representation for -x \
    > decimal value of 0b 1000 0000 0000 0000 is 32768

    > decimal value of 0x8000 -32768


3. Give a representation for each of the following decimal values in 16-bit twos-complement bit-strings. Show the value in binary, octal and hexadecimal.

   iii. 1000
    > binary - 0b1111101000 \
    > hexadecimal - 0x3e8 \
    > octal - 01750

   vi. -5
    > binary - 0b 1111 1111 1111 1011 \
    > binary representation of 5 is 0b 0000 0000 0000 0101 \
    > flip the bits: 0b 1111 1111 1111 1010 \
    > add 1: 0b 1111 1111 1111 1011

    > hexadecimcal - 0xFFFB

    > octal - 0177773

### Type Casting

Explore in code: \
int16_t i = -1000 \
uint32_t j = i

In C, type casting to an integer type with more bits, the extra space is filled with the leading sign bit.



## Floating Point Numbers

Rough representation - (-1)<sup>sign</sup> x (1 + fraction) x 2<sup>exponent</sup> \
This idea is similar to scientific notation.

### Scientific Notation Examples

134000 - 1.34 x 10<sup>5</sup> \
0.000134 - 1.34 x 10<sup>-4</sup>

### Base 2 Equivalent Example

0b10001 = 17 x 2<sup>-5</sup> \
0.53125

### Floating Point Numbers Binary Representation

We mainly look at 32 bits floating point numbers - floats in C.

sign - first/most significant bit (0th bit)
exponent - next 8 bits (1-8th bit) -> ranges from 0 - 255
fraction - next 23 bits (9-31th bits)

floating point number - <span style="background-color: #0F0FFF"> (-1) <sup>sign</sup> x (1 + fraction x 2 <sup>-23</sup>) x 2<sup>exponent</sup>  </span>


Convert 2.5 to floating point representation:
- find the greatest power of 2 that is smaller than 2.5 = 1
- exponent = 1 + 127 = 128
- 1 + fraction x 2 <sup>-23</sup> = 2.5 / 2 <sup>128 - 127</sup> = 1.25
- fraction x 2 <sup>-23</sup> = 0.25
- fraction = 0.25 * 2 <sup>23</sup>
- fraction = 2097152
- sign = 0

<pre>
sign   exponent   fraction
0      10000000   01000000000000000000000
</pre>

### General
- sign bit is 1 - negative number -> (-1)<sup>1</sup> = -1
- sign bit is 0 - positive number -> (-1)<sup>0</sup> = 1

### Special Cases

- exact 0 - exponent = 0 and fraction = 0
(1 + 0 x 2 <sup>-23</sup>) x 2 <sup>0 - 127</sup>
= 1 x 2 <sup>-127</sup> = 5.877471754111438e-39
  - sign bit = 0, +0
  - sign bit = 1, -0

- infinity - exponent = 255 and fraction = 0
(1 + 0 x 2 <sup>-23</sup>) x 2 <sup>255 - 127</sup>
= 1 x 2 <sup>128</sup>
  - sign bit = 0, +inf
  - sign bit = 1, -inf

- NaN (not a number) - e.g. 1/0, exponent = 255 and fraction != 0
