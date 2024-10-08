// p152.c by Brandon Kmiec. Submitted for CSC 152 September 24, 2024.
// Implement the permutation described in the video "A cryptographic permutation"

#include <stdint.h>
#include <string.h>

// Step 1
// Static means that it is not exported for linking and so
// can only be called from this file
static uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32 - n));
} // end rotl32

// Step 1
// ap - dp are references to four variables to be mixed.
// A good compiler will keep everything in registers, so even
// though it looks like we're reading memory, we probaably aren't.
void mix(uint32_t *ap, uint32_t *bp, uint32_t *cp, uint32_t *dp) {
    // Receive the four words to be mixed
    uint32_t a = *ap;
    uint32_t b = *bp;
    uint32_t c = *cp;
    uint32_t d = *dp;

    // Mix the four words
    a = (a + b) % 0x100000000;
    d = d ^ a;
    d = rotl32(d, 16);
    c = (c + d) % 0x100000000;
    b = b ^ c;
    b = rotl32(b, 12);
    a = (a + b) % 0x100000000;
    d = d ^ a;
    d = rotl32(d, 8);
    c = (c + d) % 0x100000000;
    b = b ^ c;
    b = rotl32(b, 7);

    // Update the caller's values
    *ap = a;
    *bp = b;
    *cp = c;
    *dp = d;
} // end mix

// Step 2
void p152(void *in, void *out) {
    // copy 64 bytes into an auto-allocated array of 16 uint32_t
    uint32_t arr[16];
    memcpy(arr, in, 64);
    
    // loop 10 times through mix function calls
    for(int i = 0; i < 10; i++) {
        // mix columns
        mix(&arr[0], &arr[4], &arr[8], &arr[12]);
        mix(&arr[1], &arr[5], &arr[9], &arr[13]);
        mix(&arr[2], &arr[6], &arr[10], &arr[14]);
        mix(&arr[3], &arr[7], &arr[11], &arr[15]);
        // mix diagonals
        mix(&arr[0], &arr[5], &arr[10], &arr[15]);
        mix(&arr[1], &arr[6], &arr[11], &arr[12]);
        mix(&arr[2], &arr[7], &arr[8], &arr[13]);
        mix(&arr[3], &arr[4], &arr[9], &arr[14]);
    } // end for

    // copy 64 bytes into out
    memcpy(out, arr, 64);
} // end p152


#if 0   // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    // Step 1
    printf("\nStep 1:\n");
    uint32_t a = 0x00010203;
    uint32_t b = 0x04050607;
    uint32_t c = 0x08090A0B;
    uint32_t d = 0x0C0D0E0F;
    mix(&a, &b, &c, &d);
    printf("Is       : %x %x %x %x\n", a, b, c, d);
    printf("Should be: b54718aa afd1b4f0 501eb3c9 4210a1b3\n");

    // Step 2
    printf("\nStep 2:\n");
    unsigned char buf[64] = {1}; // Puts 1 in first byte, rest get auto zeroed
    p152(buf, buf);
    // As a test, output the first 16 bytes of the output
    printf("Is       : ");
    for(int i = 0; i < 16; i++)
        printf("%02x", buf[i]);
    printf("\n");
    printf("Should be: 14627e9771052d97a8a025cc5531572f\n");
    
    printf("\n");
} // end main

#endif
