#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define READ 0
#define WRITE 1

int main() {
    int ctop[2];
    pipe(ctop);
    int f = fork();

    if (f) { // parent
        // closing pipes
        close(ctop[WRITE]);
        // gets input
        // sends to child
        // reads from child            
        char line[100];
        read(ctop[READ], line, 100);
        printf("parent got: %s\n",line);
    }
    else { // child
        // closing pipes
        close(ctop[READ]);
        // read from parent
        // random
        // send to parent
        write(ctop[WRITE], "hello", 6);
    }
    return 0;
}