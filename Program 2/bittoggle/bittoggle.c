// bittoggle by Brandon Kmiec. Submitted for CSC 152 September 15, 2024
// function to toggle a specific bit

int bittoggle(int num, int pos) {
    return num ^ (1 << pos);
} // end bittoggle