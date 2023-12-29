#include <stdio.h>
#include <stdlib.h>

#define BINAR_11111 31
#define BINAR_1111 15
#define BINAR_111111 63
#define BITI_ZI 5
#define BITI_LUNA 4
#define START_YEAR 1970

int main () {
    unsigned int data = 0, an = 0, luna = 0, zi = 0;
    scanf("%u%u%u", &zi, &luna, &an);
    data = ((an - START_YEAR) << (BITI_LUNA + BITI_ZI)) + (luna << BITI_ZI) + zi;
    printf("%u\n", data);

    return 0;
}