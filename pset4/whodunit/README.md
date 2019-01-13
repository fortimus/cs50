# Questions

## What's `stdint.h`?

header file that defines standard intergers

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

using these to assign types to a variable allows you to ensure that formatting and function can be standard throughout the program.
this can include the use of signed or unsigned intergers and the set length of the memory set aside for use

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

bfSize indicates the entire size of the file (BITMAPINFOHEADER + BITMAPFILEHEADER + Pixels + Padding) while
biSize only indicates the size of the BITMAPINFOHEADER (40)

## What does it mean if `biHeight` is negative?

the bmp is top-down with the origin in the top left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

the target file may not exist or may not be in a format that is readable

## Why is the third argument to `fread` always `1` in our code?

the program is only expected to read each pixel (or other data point) 1 time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

moves the point to a new location

## What is `SEEK_CUR`?

tells the function fseek to count the offset from the current pointer location

## Whodunit?

It was Professor Plum with the candlestick in the library.
