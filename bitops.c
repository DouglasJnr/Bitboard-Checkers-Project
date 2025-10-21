#include <stdio.h>
#include "bitops.h"

/**
 * Sets a specific bit to 1
 * @param value The original value
 * @param position The bit position (0-63)
 * @return The modified value
 */
unsigned long long SetBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value | (1ULL << position);
}

/**
 * Clears a specific bit to 0
 * @param value The original value
 * @param position The bit position (0-63)
 * @return The modified value
 */
unsigned long long ClearBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value & ~(1ULL << position);
}

/**
 * Toggles a specific bit (0->1 or 1->0)
 * @param value The original value
 * @param position The bit position (0-63)
 * @return The modified value
 */
unsigned long long ToggleBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return value;
    return value ^ (1ULL << position);
}

/**
 * Gets the value of a specific bit
 * @param value The value to check
 * @param position The bit position (0-63)
 * @return 1 if bit is set, 0 otherwise
 */
int GetBit(unsigned long long value, int position) {
    if (position < 0 || position >= 64) return 0;
    return (value >> position) & 1ULL;
}

/**
 * Counts the number of 1 bits in a value
 * @param value The value to count
 * @return Number of bits set to 1
 */
int CountBits(unsigned long long value) {
    int count = 0;
    while (value) {
        count += value & 1ULL;
        value >>= 1;
    }
    return count;
}

/**
 * Shifts bits to the left
 * @param value The value to shift
 * @param positions Number of positions to shift
 * @return The shifted value
 */
unsigned long long ShiftLeft(unsigned long long value, int positions) {
    if (positions < 0 || positions >= 64) return 0;
    return value << positions;
}

/**
 * Shifts bits to the right
 * @param value The value to shift
 * @param positions Number of positions to shift
 * @return The shifted value
 */
unsigned long long ShiftRight(unsigned long long value, int positions) {
    if (positions < 0 || positions >= 64) return 0;
    return value >> positions;
}

/**
 * Prints a value in binary format (64 bits)
 * @param value The value to print
 */
void PrintBinary(unsigned long long value) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", GetBit(value, i));
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}

/**
 * Prints a value in hexadecimal format
 * @param value The value to print
 */
void PrintHex(unsigned long long value) {
    printf("0x%016llX\n", value);
}

/**
 * Runs tests on Phase 1 bit manipulation functions
 */
void TestBitFunctions() {
    printf("\n═══════════════════════════════════════\n");
    printf("  TESTING PHASE 1: BIT OPERATIONS\n");
    printf("═══════════════════════════════════════\n\n");
    
    unsigned long long test = 0;
    
    printf("1. Testing SetBit:\n");
    test = SetBit(test, 3);
    printf("   After setting bit 3: ");
    PrintBinary(test);
    printf("   In hex: ");
    PrintHex(test);
    
    printf("\n2. Testing CountBits:\n");
    printf("   Number of 1s: %d (expected: 1)\n", CountBits(test));
    
    printf("\n3. Testing SetBit multiple times:\n");
    test = SetBit(test, 7);
    test = SetBit(test, 15);
    printf("   After setting bits 3, 7, 15: ");
    PrintBinary(test);
    printf("   Number of 1s: %d (expected: 3)\n", CountBits(test));
    
    printf("\n4. Testing ClearBit:\n");
    test = ClearBit(test, 7);
    printf("   After clearing bit 7: ");
    PrintBinary(test);
    printf("   Number of 1s: %d (expected: 2)\n", CountBits(test));
    
    printf("\n5. Testing ToggleBit:\n");
    test = ToggleBit(test, 3);
    printf("   After toggling bit 3: ");
    PrintBinary(test);
    printf("   Number of 1s: %d (expected: 1)\n", CountBits(test));
    
    printf("\n6. Testing GetBit:\n");
    printf("   Bit 15 is: %d (expected: 1)\n", GetBit(test, 15));
    printf("   Bit 3 is: %d (expected: 0)\n", GetBit(test, 3));
    
    printf("\n7. Testing ShiftLeft:\n");
    unsigned long long shift_test = 0b1010;
    printf("   Original (1010 binary): %llu\n", shift_test);
    printf("   Shifted left by 2: %llu (expected: 40)\n", ShiftLeft(shift_test, 2));
    
    printf("\n8. Testing ShiftRight:\n");
    printf("   Original: %llu\n", shift_test);
    printf("   Shifted right by 1: %llu (expected: 5)\n", ShiftRight(shift_test, 1));
    
    printf("\n✓ Phase 1 tests completed!\n");
    printf("═══════════════════════════════════════\n\n");
}