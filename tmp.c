#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CLEAR_CONSOLE system("clear") == 1 ? system("cls") : system("clear")
int main() {
    CLEAR_CONSOLE;
    printf("HelloWorld!");
    printf("%d", strcmp("a", "A"));
    return 0;
}
