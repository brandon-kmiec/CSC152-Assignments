// mix.c by Brandon Kmiec. Submitted for CSC 152 September 24, 2024.

#include <stdint.h>

// Static means that it is not exported for linking and so
// can only be called from this file
static uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32 - n));
} // end rotl32

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


#if 1   // Set to 1 while testing and 0 for submission

#include <stdio.h>

int main() {
    uint32_t a = 0x00010203;
    uint32_t b = 0x04050607;
    uint32_t c = 0x08090A0B;
    uint32_t d = 0x0C0D0E0F;
    mix(&a, &b, &c, &d);
    printf("Is       : %x %x %x %x\n", a, b, c, d);
    printf("Should be: b54718aa afd1b4f0 501eb3c9 4210a1b3\n");
} // end main

#endif
