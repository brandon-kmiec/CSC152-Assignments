// bits_to_flip by Brandon Kmiec. Submitted for CSC152 September 15, 2024
// function to determine the number of bits to flip to turn a into b

int bits_to_flip(int a, int b) {
    int count = 0;
    int aXorB = a ^ b;
    
    for(int i = 0; i < 32; i++) {
        if((aXorB & (1 << i)) > 0)
            count++;
    } // end for
    
    if((a < 0 && b >= 0) || (a >= 0 & b < 0))
        count++;
    
    return count;
} // end bits_to_flip