// contains.c by Brandon Kmiec. Submitted for CSC 152 September 8, 2024
// Used the pseudo code from krovetz.net/152/w01/hw_prog.html as a starting point

#include <stdio.h>
#include <stdlib.h>

int contains(void*, int, void*, int);
int is_equal(unsigned char*, unsigned char*, int);

// a points to an alen byte buffer, b points to a blen byte buffer,
// Returns non-zero iff b's buffer is found contiguously inside a's.
int contains(void *a, int alen, void *b, int blen) {
    // convert void* to unsigned char*
    unsigned char *aP = a;
    unsigned char *bP = b;

    // return true whenever blen is 0 (a will always contain b)
    if((alen > 0 && blen == 0) || (alen == 0 && blen == 0))
        return 1;

    // return false if blen > alen (a is unable to contain b)
    if(blen > alen)
        return 0;

    // loop through contents of aP, call helper function is_equal
    for(int i = 0; i < alen; i++) {
        // return true if is_equal returns true (a contains b)
        if(is_equal(&aP[i], bP, blen))
            return 1;
    } // end for

    // return false if a does not contain b
    return 0;
} // end contains

// helper function for contains function
int is_equal(unsigned char *a, unsigned char *b, int blen) {
    // loop and compare contents of a and b.  If a and b are not equal
    // at position j, return false, otherwise return true
    for(int j = 0; j < blen; j++) {
        if(a[j] != b[j])
            return 0;
    } // end for

    return 1;
} // end is_equal

/*
// main function for test cases
int main(int argc, char *argv[]) {
    // Test #1: alen > blen, aBuf contains bBuf
    char *aBuf = "00110011";
    char *bBuf = "1001";
    int aBufLen = 8;
    int bBufLen = 4;
    printf("\nTest #1: ");
    if(contains(aBuf, aBufLen, bBuf, bBufLen) != 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    // Test #2: alen > blen, aBuf does not contain bBuf
    aBuf = "01010101";
    bBuf = "0000";
    aBufLen = 8;
    bBufLen = 4;
    printf("\nTest #2: ");
    if(contains(aBuf, aBufLen, bBuf, bBufLen) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    // Test #3: alen = blen, aBuf contains bBuf
    aBuf = "1010";
    bBuf = "1010";
    aBufLen = 4;
    bBufLen = 4;
    printf("\nTest #3: ");
    if(contains(aBuf, aBufLen, bBuf, bBufLen) != 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    // Test #4: alen = blen, aBuf does not contain bBuf
    aBuf = "1010";
    bBuf = "0101";
    aBufLen = 4;
    bBufLen = 4;
    printf("\nTest #4: ");
    if(contains(aBuf, aBufLen, bBuf, bBufLen) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    // Test #5: alen < blen
    aBuf = "1001";
    bBuf = "100101";
    aBufLen = 4;
    bBufLen = 6;
    printf("\nTest #5: ");
    if(contains(aBuf, aBufLen, bBuf, bBufLen) == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    // Test #6: alen > 0, blen = 0
    aBuf = "1001";
    bBuf = "";
    aBufLen = 4;
    bBufLen = 0;
    printf("\nTest #6: ");
    if(contains(aBuf, aBufLen, bBuf, bBufLen) != 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    // Test #7: alen = 0, blen = 0
    aBuf = "";
    bBuf = "";
    aBufLen = 0;
    bBufLen = 0;
    printf("\nTest #7: ");
    if(contains(aBuf, aBufLen, bBuf, bBufLen) != 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    return 0;
} // end main
*/
