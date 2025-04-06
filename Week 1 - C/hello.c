#include <stdio.h>

int main(void) {
    char name[10];
    printf("What is your name? ");
    fgets(name, sizeof(name), stdin);
    printf("hello, %s", name);
    return 0;
}
