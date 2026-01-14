#include<stdio.h>
#include<unistd.h>

int main(){

    __pid_t pid ;

    printf("before any things like fork is happening ...\n");

    pid = fork();
    fork();

    if(pid == -1){
        perror("unsuccessfull\n");
        return 1;
    }

    if(pid == 0){
        printf("child process \n");
    }

    else{
        //wait();
        sleep(30);
        printf("Parent process\n");
    }


    return 0;
}
