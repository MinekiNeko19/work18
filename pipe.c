#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define READ 0
#define WRITE 1

int main() {
    int ptoc[2];
    int ctop[2];
    char line[100];
    pipe(ctop);
    pipe(ptoc);
    int f = fork();

    if (f) { // parent
        // closing pipes
        close(ctop[WRITE]);
        close(ptoc[READ]);
        // gets input
        fgets(line, 100, stdin);
        write(ptoc[WRITE], line, 100);
        // sends to child
        // reads from child            
        char line[100];
        read(ctop[READ], line, 100);
        printf("parent got: %s\n",line);
    }
    else { // child
        // closing pipes
        close(ctop[READ]);
        close(ptoc[WRITE]);
        // read from parent
        read(ptoc[READ], line, 100);
        // random
        // send to parent
        write(ctop[WRITE], line, 100);
    }
    return 0;
}