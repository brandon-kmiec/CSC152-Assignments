// p152stream.c by Brandon Kmiec. Submitted for CSC 152 September 24, 2024.
// Implement the permutation described in the video "A cryptographic permutation"

#include <stdint.h>
#include <stdlib.h>
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

// Step 3
// Increment buf as if it's a 64 byte big-endian integer
static void increment_block(void *buf) {
    unsigned char *blk = buf;
    int i = 63;
    blk[i] += 1;
    while(blk[i] == 0) {
        i -= 1;
        blk[i] += 1;
    } // end while
} // end increment_block

// Step 3
// k is 32 bytes, n is 16 bytes, 0* is 16 bytes
// User blk = k || n || 0* to produce output as blk xor p152(blk), then increment blk
// This output is xor'd with the next 64 bytes of buf to encrypt/decrypt
void p152stream(void *k, void *n, void *inbuf, void *outbuf, int nbytes) {
	unsigned char *pinbuf = inbuf;
	unsigned char *poutbuf = outbuf;
	unsigned char in[64];
	unsigned char out[64];
    int temp = nbytes;
	
    // Init in as k || n || 0*
	memcpy(in, k, 32);
	memcpy(in + 32, n, 16);
	memset(in + 48, 0, 16);

	// your code here
    while(nbytes >= 64) {
        p152(in, out);
        for(int i = 0; i < 64; i++) {
            out[i] = out[i] ^ in[i];
            out[i] = out[i] ^ pinbuf[i + (temp - nbytes)];
            poutbuf[i + (temp - nbytes)] = out[i];
        } // end for
        increment_block(in);
        nbytes -= 64;
    } // end while
    if(nbytes > 0) {
        p152(in, out);
        for(int i = 0; i < nbytes; i++) {
            out[i] = out[i] ^ in[i];
            out[i] = out[i] ^ pinbuf[i + (temp - nbytes)];
            poutbuf[i + (temp - nbytes)] = out[i];
        } // end for
    } // end if
} // end p152stream

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
    
    // Step 3
    printf("\nStep 3:\n");
    unsigned char inbuf[200] = {1};
    unsigned char outbuf[200];
    unsigned char k[32] = {1, 2, 3, 4};
    unsigned char n[16] = {1, 2, 3, 4};
    p152stream(k, n, inbuf, outbuf, 200);
    printf("Is       : ");
    for(int i = 0; i < 200; i++)
        printf("%02x", outbuf[i]);
    printf("\n");
    printf("Should be: d6c0e5ef8745f9fc4657510ce896e96b9f27c18ba5a8cadc7e2a"
           "6872c51c704983726c6633a9e924a5e9a75b8b9980cfad91501f74315fea6da"
           "0936286e5866ac66e8c3d766b6248f88ee99b468dd9fdcf2c4e65e6df35637b"
           "b245246e0cb97ce689c0b91dbd7212257f98744fae42484ea3afbd419db90ca"
           "38a96d4c6e68cd6c003af8b842733ad4162099b2b2d10bfd48a3fb6e8c5e5ea"
           "59dde8bae3206ce3e80f0acad1540e83e2858f39bccec0a4ece5172194f6d15"
           "e7fd5a26a05cb3b8b8fea979965daf5c1\n");
} // end main

#endif
