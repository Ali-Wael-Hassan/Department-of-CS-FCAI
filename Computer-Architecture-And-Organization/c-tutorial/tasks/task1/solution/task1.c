#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        printf("Name can't be null");
        return 1;
    }

    printf("Hello, %s!", argv[1]);
    return 0;
}