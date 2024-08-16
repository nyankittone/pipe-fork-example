#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function that takes a char, and hand back a corresponding string.
const char *expandChar(const char character) {
    switch(character) {
        case 'b':
            return "bruh!";
        case 'B':
            return "BRUH!";
        case 'g':
            return "grouse...";
        case 'G':
            return "GROUSE???";
        case '3':
            return ":3 :3 :3";
        case 'c':
        case 'C':
            return "cat cat meow purrr meow <3";
        case 'p':
            return "peepee poopoo";
        case 't':
            return "toilet";
        case 'T':
            return "TOILET!!!! >:3";
        case 'q':
        case 'Q':
            return "quail? KWAIL!! QUAIL! rshfakgrskges";
        default:
            return NULL;
    }
}

// On failure, `true` is returned. Else, `false` is returned instead.
bool forkIt(void) {
    // the_pipe[0] is the read end of the pipe
    // the_pipe[1] is the write end
    int the_pipe[2];
    if(pipe(the_pipe) == -1) {
        fputs("\33[91mFailed to create pipe!!!\33[m\n", stderr);
        return true;
    }

    pid_t pid = fork();
    if(pid == -1) {
        fputs("\33[91mFailed to create child!!!\33[m\n", stderr);
        return true;
    }

    if(pid == 0) {
        close(the_pipe[1]); // closing write end here because we don't need it
        char got;
        while(read(the_pipe[0], &got, 1) == 1) {
            const char *to_print = expandChar(got);
            if(to_print) printf("\33[1;97m> \33[93m%s\33[m\n", to_print);
        }

        close(the_pipe[0]);
        exit(EXIT_SUCCESS);
    } else {
        close(the_pipe[0]); // closing read end here because we don't need it
        char got;
        while(read(STDIN_FILENO, &got, 1) == 1) {
            write(the_pipe[1], &got, 1);
        }

        close(the_pipe[1]);
        wait(NULL);
    }

    return false;
}

int main(void) {
    return forkIt() ? EXIT_FAILURE : EXIT_SUCCESS;
}

