// miner.c by Brandon Kmiec. Submitted for CSC 152 October 27, 2024
// output a datum whose SHA2-256 hash output begins with n number of 0 bits
//      where n is a multiple of 4 
// Followed "EVP Message Digest" example from wiki.openssl.org/index.php/EVP_MESSAGE_DIGESTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Obtain the SHA256 hash for a message and store in digest 
void digest_message(const unsigned char *message, size_t message_len, 
        unsigned char *digest, unsigned int *digest_len) {
    EVP_MD_CTX *mdctx;
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, message, message_len);
    EVP_DigestFinal_ex(mdctx, digest, digest_len);
    EVP_MD_CTX_free(mdctx);
} // end digest_message

// Increment asciiSeq starting from '0'. When asciiSeq[i] reaches 'z', reset to
// '0' and recursively increment as needed.
// Chars 0-9 are decimal 48-57, A-Z are decimal 65-90, a-z are decimal 97-122.
static void incrementAsciiSeq(unsigned char asciiSeq[], size_t *len, int i) {
    if (i < *len) {
        asciiSeq[i]++;
        
        if(asciiSeq[i] > '9' && asciiSeq[i] < 'A')
            asciiSeq[i] = 'A';
        if(asciiSeq[i] > 'Z' && asciiSeq[i] < 'a')
            asciiSeq[i] = 'a';
        if(asciiSeq[i] > 'z') {
            asciiSeq[i] = '0';
            incrementAsciiSeq(asciiSeq, len, i + 1);
        } // end if
    } // end if
    else {
        asciiSeq[i] = '0';
        (*len)++;
    } // end else
} // end incrementAsciiSeq

// Verify that digest contains the proper number of bits
int checkDigest(unsigned char* digest, int numBits) {
    // check full bytes
    for(int i = 0; i < (numBits / 8); i++)
        if(digest[i] != 0)
            return 0;
   
    // check remaining bits if numBits < 8
    if(numBits % 8 != 0) { 
        int bitsRemaining = numBits % 8;
        unsigned char mask = (1 << (8 - bitsRemaining)) - 1;
        
        if((digest[numBits / 8] & mask) != 0)
            return 0;
    } // end if
    
    return 1;
} // end checkDigest

int main(int argc, char* argv[]) {
    // error check for wrong number of arguments
    if(argc != 2) {
        printf("\nWrong command line argument format.\n");
        printf("Please enter the prefered format:\n");
        printf("./miner n (where n is a non-zero multiple of 4 integer)\n\n");
    } // end if

    // only allow 2 arguments
    if(argc == 2) {
        int n = atoi(argv[1]);

        // check if argument argv[1] is a multiple of 4 and != 0, else give error
        if(n % 4 == 0 && n != 0) {
            unsigned char buf[60] = {0}; // no more than 60 characters
            buf[0] = '0';

            size_t buf_len = 1; 

            unsigned char digest[32];
            unsigned int digest_len = 32;

            digest_message(buf, buf_len, digest, &digest_len);
           
            // loop until a valid digest is found 
            while(checkDigest(digest, n) == 0) {
                incrementAsciiSeq(buf, &buf_len, 0);
                digest_message(buf, buf_len, digest, &digest_len);
            } // end while

            // display found asciiSeq
            printf("%s\n", buf);

            // display found digest
            for(unsigned int i = 0; i < digest_len; i++)
                printf("%02x", (unsigned int)digest[i]);

            printf("\n");
        } // end if
        else {
            printf("\nPlease try again using a non-zero multiple of 4 integer for n.\n\n");
        } // end else
    } // end if
} // end main
