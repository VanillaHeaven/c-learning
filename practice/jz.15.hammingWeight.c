#include<stdio.h>
#include<stdlib.h>


typedef unsigned int uint32_t;


int hammingWeight(uint32_t n) {
    int count = 0;
    while(n) {
        if (n % 2 == 1) count++;
        n /= 2;
    }
    return count;
}


int main(int argc, void *argv) {
    uint32_t n = 4294967293;
    printf("%d\n", hammingWeight(n));
    return 0;
}