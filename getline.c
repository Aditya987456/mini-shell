#include<stdio.h>
#include<stdlib.h>

int main (){

    size_t n = 10;
    //char *buf = malloc(sizeof(char)*n);
    char *buf = NULL;

    printf("Enter name : ");
    getline(&buf, &n, stdin);

    printf("name is %sBuffer size is %ld\n", buf,n);
    

    free(buf); //we should the buf memory after done...


    return 0;
}
