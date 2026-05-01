#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

// int main(void){

//     __pid_t pid ;
//     __pid_t ppid;

//     printf("before any things like fork is happening ...\n");
//     pid = getpid();
//     ppid = getppid();

//     printf("PPID of the process - %d\n", ppid);
//     printf("PID of the process - %d\n", pid);

//     //pid = fork();
//     // //fork();

//     // if(pid == -1){
//     //     perror("unsuccessfull\n");
//     //     return 1;
//     // }

//     // if(pid == 0){
//     //     sleep(30);
//     //     printf("child process \n");
//     // }

//     // else{
//     //     //wait();
//     //     ppid = getppid();
//     //     printf("Parent process pid is : %u \n", ppid);
//     // }


//     return 0;
// }


int main(){

    __pid_t pid = fork();
    __pid_t ppid;
   
//example-1  
    //printf("HEllo\n");
    //here it will print two time hello one is parent and another is child.




//exampl-2
    // if (pid == 0) {
    //     printf("I am child\n");
    // } else {
    //     printf("I am parent\n");
    // }




//example-3
    // if (pid < 0) {
    //     perror("fork");
    //     return 1;
    // }

    // if (pid == 0) {
    //     //child
    //     printf("Child:  PID=%d, PPID=%d\n", getpid(), getppid());

    // } else {
    //     //parent.
    //     printf("Parent: PID=%d, Parent's Child PID=%d\n", getpid(), pid);
    // }




    




    
    // if(pid == -1){
    //     perror("unsuccessfull");
    //     return 1;
    // }

    // if (pid == 0) {
    //     // printf("Child exiting...\n");
    //     // _exit(0);            // child ends immediately
    //     sleep(40);
    //     printf("I am child\n");

    // }else {
    //     ppid = getpid();
    //     printf("parents pid is -- %u\n", ppid);
    //     //sleep(20);           // keep parent alive without wait()
    // }




//example-4 : Zombie process...
//  if (pid == 0) {
//         // Child process
//         printf("Child PID: %d\n", getpid());
//         printf("Child exiting...\n");
//         exit(0);  // child ends immediately
//     } else {
//         // Parent process
//         printf("Parent PID: %d\n", getpid());
//         printf("Sleeping... check zombie now!\n");
//         sleep(20);  // parent NOT calling wait()

//         // Now clean up
//         wait(NULL);
//         printf("Zombie cleaned!\n");
//     }



//example-5 : orphan process
if (pid == 0) {
        // Child process
        sleep(5);  // wait so parent dies first
        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent exiting...\n");
        exit(0);  // parent dies immediately
    }


    return 0;
}