#include<stdio.h>
#include<unistd.h>

int main(void){

    
    printf("PID of the process is : %d\n", getpid());

    char *args[] = { "Hello", "saar", "whatsapp", NULL};


    return 0;
}