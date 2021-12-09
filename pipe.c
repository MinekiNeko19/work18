#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

int main() {
    int ptoc[2];
    int ctop[2];
    char line[100];
    pipe(ctop);
    pipe(ptoc);
    int f = fork();
    
    int e = 1;

    while (e) {
        if (f) { // parent
            // closing pipes
            close(ctop[WRITE]);
            close(ptoc[READ]);
            // gets input
            printf("Enter input (exit to exit): ");
            fgets(line, 100, stdin);
            if (!strcmp(line, "exit\n")) {
                e = 0;
            } else {
            // sends to child
            write(ptoc[WRITE], line, 100);
            // printf("sent to child: %s\n", line);
            // reads from child            
            char line[100];
            read(ctop[READ], line, 100);
            printf("parent got from child: %s\n",line);
            }
        }
        else { // child
            // closing pipes
            close(ctop[READ]);
            close(ptoc[WRITE]);
            // read from parent
            read(ptoc[READ], line, 100);
            // random
            int i = 0;
            while (line[i] != '\n') {
                line[i] = toupper(line[i]);
                i++;
            }
            // send to parent
            write(ctop[WRITE], line, 100);
        }
    }
    return 0;
}