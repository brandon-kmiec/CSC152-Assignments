// miner.c by Brandon Kmiec. Submitted for CSC 152 October 27, 2024
// output a datum whose SHA2-256 hash output begins with n number of 0 bits
//      where n is a multiple of 4 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void digest_message(unsigned char *message, size_t message_len, 
                    unsigned char **digest, unsigned int *digest_len) {
    EVP_MD_CTX *mdctx;
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, message, message_len);
    //*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()));
    EVP_DigestFinal_ex(mdctx, *digest, digest_len);
    EVP_MD_CTX_free(mdctx);
} // end digest_message

/*
static void incrementAsciiSeq(char* asciiSeq[]) {
    int i = 0;
    while(i < 30) {
        asciiSeq[i] += 1;

        if(asciiSeq[i] > '9' && asciiSeq[i] < 'A')
            asciiSeq[i] = 'A'
        if(asciiSeq[i] > 'Z' && asciiSeq[i] < 'a')
            asciiSeq[i] = 'a'
        if(asciiSeq[i] > 'z')
            asciiSeq[i] = '0'
    } // end while
} // end incrementAsciiSeq
*/

int main(int argc, char* argv[]) {
    if(argc < 2 || argc > 2) {
        printf("\nWrong command line argument format.\n");
        printf("Please enter the prefered format:\n");
        printf("./miner n (where n is a non-zero multiple of 4 integer)\n\n");
    } // end if
    
    if(argc == 2) {
        int n = atoi(argv[1]);

        if(n % 4 == 0 && n != 0) {
            printf("\nn: %d\n\n", n);

            //char* asciiSeq[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; 
            //chars 0-9 are decimal 48-57, chars A-Z are decimal 65-90, 
            //  chars a-z are decimal 97-122

            unsigned char buf[] = "abcdefghij";
            size_t buf_len = sizeof(buf) - 1; //len of buf + null terminating char //strlen((char)buf);

            unsigned char* digest[32];
            //unsigned int* digest_len = 0;

            digest_message(buf, buf_len, digest, 32/*digest_len*/);

            for(int i = 0; i < 32/**digest_len*/; i++)
                printf("%02x", (unsigned int)digest[i]);
        } // end if
        else {
            printf("\nPlease try again using a non-zero multiple of 4 integer for n.\n\n");
        } // end else

    } // end if
} // end main
