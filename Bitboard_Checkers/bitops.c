#include <stdio.h>
#include "bitops.h"

// Sets a specific bit to 1
unsigned long long SetBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value | (1ULL << position);
}

// Clears a specific bit to 0
unsigned long long ClearBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value & ~(1ULL << position);
}

// Toggles a specific bit (0->1 or 1->0)
unsigned long long ToggleBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value ^ (1ULL << position);
}

// Gets the value of a specific bit
int GetBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return 0;
    return (value >> position) & 1ULL;
}

// Counts the number of 1 bits in a value
int CountBits(unsigned long long value) {
    int count = 0;
    while (value) {
        count += value & 1ULL;
        value >>= 1;
    }
    return count;
}

// Shifts bits to the left
unsigned long long ShiftLeft(unsigned long long value, int positions) {
    if (positions < 0 || positions >= 64) return 0;
    return value << positions;
}

// Shifts bits to the right
unsigned long long ShiftRight(unsigned long long value, int positions) {
    if (positions < 0 || positions >= 64) return 0;
    return value >> positions;
}

// Prints a value in binary format (64 bits)
void PrintBinary(unsigned long long value) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", GetBit(value, i));
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

// Prints a value in hexadecimal format
void PrintHex(unsigned long long value) {
    printf("0x%016llX\n", value);
}
