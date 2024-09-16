// reverse_bits by Brandon Kmiec. Submitted for CSC152 September 15, 2024
// function to reverse the order of bits in a 1-byte value of type unsigned char

unsigned char reverse_bits(unsigned char num) {
    unsigned char ret = 0;
    
    for(int i = 0; i < 8; i++) {
        if((num & (1 << i)) > 0) {
            ret = ret | (1 << (7 - i));
        } // end if
    } // end for
    
    return ret;
} // end reverse_bits