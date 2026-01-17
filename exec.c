#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main() {
    pid_t pid;

    printf("Shell process PID: %d\n", getpid());

    pid = fork();

    if (pid == 0) {
        // CHILD
        printf("Child PID: %d (before exec)\n", getpid());

        char *args[] = {"/bin/ls", "-l", NULL};
        execve("/bin/ls", args, environ);

        // runs only if execve fails
        perror("execve failed");
    } 
    else {
        // PARENT
        wait(NULL);
        printf("Back in shell (parent still alive)\n");
    }

    return 0;
}
