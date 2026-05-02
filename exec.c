#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main() {
    pid_t pid;

    printf("Shell process PID: %d\n", getpid());

    pid = fork();

    if (pid == 0) {
        // child.
        printf("Child PID: %d (before exec)\n", getpid());

        char *args[] = {"/bin/ls", "-l", NULL};
        int val = execve("/bin/ls", args, environ);
        if(val == -1){
            perror("Error in exceve return -1.");
        }

        // runs only if execve fails
        perror("execve failed");
    } 
    else {
        // parentbecz pid>0...
        wait(NULL);
        printf("Back in shell (parent still alive)\n");
    }

    return 0;
}
