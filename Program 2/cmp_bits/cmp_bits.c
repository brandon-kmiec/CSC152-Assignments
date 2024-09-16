// cmp_bits by Brandon Kmiec. Submitted for CSC 152 September 15, 2024
// function used to compare the number of ON bits between two numbers
// Used https://en.wikipedia.org/wiki/Mask_(computing)#Querying_the_status_of_a_bit to learn how to pick out a single bit

int cmp_bits(int a, int b) {
    if(a == b)
        return 0;
    
    int aCount = 0;
    int bCount = 0;
    int bitMaskA = 0;
    int bitMaskB = 0;
    int tmp = 1;
    
    for(int i = 0; i < 31; i++) {        
        bitMaskA = a & tmp;
        bitMaskB = b & tmp;
        
        if(bitMaskA > 0)
            aCount++;
        
        if(bitMaskB > 0)
            bCount++;
        
        tmp = tmp << 1;
    } // end for
    
    if(aCount > bCount)
        return 1;
    else if(aCount < bCount)
        return -1;
    else
        return 0;
    
} // end cmp_bits