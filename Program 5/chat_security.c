// chat_security.c by Brandon Kmiec. Submitted for CSC 152 October 6, 2024
// Followed "EVP Symmetric Encryption and Decryption" example from wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
//#include <openssl/conf.h>
//#include <openssl/evp.h>

// Encrypt plain text message pt of length ptlen using key k.  Place encrypted message in ct
void chat_encrypt(void *k, void *pt, int ptlen, void *ct) {
    unsigned char count[4] = {0,0,0,0};
    unsigned char nonce[12]; 
    unsigned char iv[16];
    int len;

    // Generate random nonce
    RAND_bytes(nonce, 12);

    // Fill iv with 12 bytes from nonce and 4 bytes from count
    for(int i = 0; i < 16; i++) {
        if(i < 12)
            iv[i] = nonce[i];
        else
            iv[i] = count[i - 12];
    } // end for

    // Create and initialize ctx
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
   
    // Initialize encryption operation using EVP_aes_256_ctr
    EVP_EncryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, k, iv);
    
    // Fill first 12 bytes of ct with nonce
    memcpy(ct, nonce, 12);

    // Send pt to be encrypted and place encypted message in pt
    EVP_EncryptUpdate(ctx, (unsigned char *)ct + 12, &len, pt, ptlen);
    
    // Finalize encryption
    EVP_EncryptFinal_ex(ctx, (unsigned char *)ct + 12 + len, &len);

    // Free memory allocated to ctx
    EVP_CIPHER_CTX_free(ctx);
} // end chat_encrypt


// Decrypt encrypted message ct of length ctlen using key k.  Place decrypted message in pt
void chat_decrypt(void *k, void *ct, int ctlen, void *pt) {
    unsigned char iv[16];
    unsigned char nonce[12];
    unsigned char count[4] = {0,0,0,0};
    int len;

    // Fill nonce with first 12 bytes of ct
    memcpy(nonce, ct, 12);

    // Fill iv with 12 bytes from nonce, and 4 bytes from count
    for(int i = 0; i < 16; i++) {
        if(i < 12)
            iv[i] = nonce[i];
        else
            iv[i] = count[i - 12];
    } // end for

    // Create and initialize ctx 
    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    
    // Initialize decryption operation using EVP_aes_256_ctr
    EVP_DecryptInit_ex(ctx, EVP_aes_256_ctr(), NULL, k, iv);

    // Send ct to be decrypted and place decrypted message in pt
    EVP_DecryptUpdate(ctx, pt, &len, (unsigned char *)ct + 12, ctlen - 12);

    // Finalize decryption
    EVP_DecryptFinal_ex(ctx, pt + len, &len);
    
    // Free memory allocated to ctx
    EVP_CIPHER_CTX_free(ctx);
} // end chat_decrypt


#if 0   // Set to 1 while testing and 0 for submission

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Test #1: Decrypt provided test case, encrypt and then decrypt again
    printf("\nTest #1: \n");

    unsigned char k[32] = {1,2,3,4};   // First 4 bytes are 1,2,3,4; rest are 0
    unsigned char pt[100];
    unsigned char ct[112] = {0x45,0x29,0x18,0x7D,0x4D,0x1C,0xF3,0x1D,0x51,0xBF,
                             0x1A,0xB9,0x25,0x57,0xCD,0xE3,0x87,0x07,0xED,0x72,
                             0xA2,0x9E,0xD2,0xA8,0xEA,0x3F,0xA9,0x2E,0xE5,0x08,
                             0x88,0xB8,0xE5,0xC3,0xA4,0xEC,0xE1,0x2F,0xD3,0x6E,
                             0x5E,0x92,0xAA,0x21,0x2A,0x9C,0x7C,0xFC,0x62,0x43,
                             0xA9,0x95,0x4B,0x0C,0x7F,0xB8,0x6C,0x59,0x5D,0x5C,
                             0x56,0x8C,0x08,0x52,0x31,0xD9,0x03,0x32,0x8D,0xA4,
                             0x09,0x86,0x0B,0xBE,0x5A,0xE1,0x28,0x4C,0x57,0xCE,
                             0xE3,0xAA,0x4F,0x7A,0x0E,0x11,0x97,0xAF,0x89,0x6D,
                             0x34,0xD8,0x1B};
    printf("\nCipher Text: ");
    for(int i = 0; i < 112; i++)
        printf("%02x ", ct[i]);

    chat_decrypt(k, ct, 112, pt);
    printf("\n\nPlain Text:  %s\n", pt);

    chat_encrypt(k, pt, 100, ct);
    printf("\nCipher Text: ");
    for(int i = 0; i < 112; i++)
        printf("%02x ", ct[i]);

    chat_decrypt(k, ct, 112, pt);
    printf("\n\nPlain Text:  %s\n", pt);

    
    // Test #2: Encrypt plainText message and decrypt to verify message
    printf("\n\nTest #2: \n");
    
    unsigned char plainText[100] = "The quick brown fox jumps over the lazy dog";
    unsigned char cipherText[112];
    
    printf("\nPlain Text:  %s\n", plainText);

    chat_encrypt(k, plainText, 100, cipherText);
    printf("\nCipher Text: ");
    for(int i = 0; i < 112; i++)
        printf("%02x ", cipherText[i]);

    chat_decrypt(k, cipherText, 112, plainText);
    printf("\n\nPlain Text:  %s\n\n", plainText);
} // end main

#endif 
