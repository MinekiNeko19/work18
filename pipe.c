#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {
    // gets input
    char line[100];
    printf("Enter input: ");
    fgets(line, 100, stdin);
    printf("%s\n",line);


    int f = fork();
    if (f) { // parent
        printf("Parent: %s\n", line);
    }
    else { // child
        printf("Child: i can't read so that sign won't stop me\n");
    }

    return 0;
}