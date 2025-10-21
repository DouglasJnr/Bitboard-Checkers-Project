#ifndef BITOPS_H
#define BITOPS_H

// Basic bit operations
unsigned long long SetBit(unsigned long long value, int position);
unsigned long long ClearBit(unsigned long long value, int position);
unsigned long long ToggleBit(unsigned long long value, int position);
int GetBit(unsigned long long value, int position);

// Counting and finding
int CountBits(unsigned long long value);

// Shift operations
unsigned long long ShiftLeft(unsigned long long value, int positions);
unsigned long long ShiftRight(unsigned long long value, int positions);

// Display functions
void PrintBinary(unsigned long long value);
void PrintHex(unsigned long long value);

// Testing function
void TestBitFunctions();

#endif // BITOPS_H