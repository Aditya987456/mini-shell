#include<stdio.h>
#include<unistd.h>   //need this header for pid_t data type...



//pid -- change in each execution of the process....
// int main( void ){

//     int a = 3;
//     int b = 5;
//     int sum = a+b;

//     __pid_t pid;   //defining the variable that represent the process ID
//     pid = getpid();

//     printf("Sum is %d\n", sum);
//     printf("PID is %u\n", pid);
//     return 0;
// }



//ppid --- here all id will be same.... only change when exit...
int main( void ){

    int a = 3;
    int b = 5;
    int sum = a+b;

    __pid_t ppid;   //defining the variable that represent the process ID
    ppid = getppid();

    printf("Sum is %d\n", sum);
    printf("PPID is %u\n", ppid);
    return 0;
}


