#include <stdlib.h>
#include <stdio.h>

int main() {
    int x = 0x87654321;
    int n = 4;
    int ar = x >> n;
    int a = 0x1;
    a = a << 30;
    a = a >> n;
    printf(ar & a);
}