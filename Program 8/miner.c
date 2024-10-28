// miner.c by Brandon Kmiec. Submitted for CSC 152 October 27, 2024
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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


        } // end if
        else {
            printf("\nPlease try again using a non-zero multiple of 4 integer 
                    for n.\n\n");
        } // end else

    } // end if
} // end main
