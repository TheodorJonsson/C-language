#include <stdio.h>
#include <stdlib.h>

int main(void){
    char a[] = "ABC";
    char *b = "123";
    char *c = malloc(6);
    char *d = c + 1;
    char *e = a + 3;
    c = "ABC";

    printf("a \n");
    putchar(a[0]);
    putchar(a[1]);
    putchar(a[2]);
    printf("\nb \n");
    putchar(b[0]);
    putchar(b[1]);
    putchar(b[2]);

    printf("\nc \n");
    putchar(c[0]);
    putchar(c[1]);
    putchar(c[2]);
    putchar(c[3]);
    putchar(c[4]);
    putchar(c[5]);
    printf("\nd \n");
    putchar(d);
    printf("\ne \n");
    putchar(e[0]);
}