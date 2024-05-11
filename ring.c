#include <stdio.h>
#include<sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void computeFibonacci(int mypid, int in_fd, int out_fd) {
    int a, b, c;
    
    // Read the initial numbers from the previous process
    if (read(in_fd, &a, sizeof(int)) < 0 || read(in_fd, &b, sizeof(int)) < 0) {
        perror("Read error");
        exit(1);
    }
    
    // Compute the next Fibonacci number
    c = a + b;
    
    // Output the result
    printf("My pid is: %d and I received %d %d and sent %d %d\n", mypid, a, b, b, c);
    
    // Send the result to the next process
    if (write(out_fd, &b, sizeof(int)) < 0 || write(out_fd, &c, sizeof(int)) < 0) {
        perror("Write error");
        exit(1);
    }
    
    // Terminate the process
    exit(0);
}

int main(int argc, char* argv[]) {
 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s nprocs\n", argv[0]);
        return 1;
    }

    int nprocs = atoi(argv[1]);
    int pid;
    int in_fd, out_fd;
    int first_in_fd, first_out_fd;

    for (int i = 1; i <= nprocs; i++) {
        int pipe_fd[2];
        if (pipe(pipe_fd) < 0) {
            perror("Pipe creation error");
            exit(1);
        }

        pid = fork();
        if (pid < 0) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(pipe_fd[1]); // Close the write end
            in_fd = pipe_fd[0];
            out_fd = first_out_fd;
            computeFibonacci(getpid(), in_fd, out_fd);
        } else {
            // Parent process
            close(pipe_fd[0]); // Close the read end
            in_fd = first_in_fd;
            out_fd = pipe_fd[1];
            first_in_fd = in_fd;
            first_out_fd = out_fd;
        }
    }

    // The first process sends the initial values
    int initial_values[] = {1, 1};
    if (write(first_out_fd, initial_values, sizeof(initial_values)) < 0) {
        perror("Write error");
        exit(1);
    }

    // Wait for the last child to terminate
    wait(NULL);
    
    return 0;
}
