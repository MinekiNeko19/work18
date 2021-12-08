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
    int f = fork();

    pipe(ptoc);
    pipe(ctop);
        
    while (1) {
        if (f) { // parent
            // closing pipes
            close(ptoc[READ]);
            close(ctop[WRITE]);

            // gets input
            printf("Enter input (type exit to end program): ");
            fgets(line, 100, stdin);
            if (strcmp(line,"exit")) {
                exit(0);
            }
            write(ptoc[WRITE], line, 100);
        }
        else { // child
            // closing pipes
            close(ptoc[WRITE]);
            close(ctop[READ]);

            // read from parent
            read(ptoc[READ], line, 100);
            // printf("from parent: %s\n",line);
            line[0] = 'p';
            write(ctop[WRITE], line, 100);

            // random
            // printf("Child: i can't read so that sign won't stop me\n");
        }
    }
    return 0;
}