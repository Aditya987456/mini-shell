#include<stdio.h>
#include<string.h>

int main(void){

    char str[] = "Aditya raj ji";
    char *delim = " ";
    char *token;


    // token = strtok(str, delim);
    // printf("%s ", token);

    // token = strtok(NULL, delim);
    // printf("%s \n", token);

    token = strtok(str, delim);

    while(token!=NULL){
        printf("%s\n", token);
        token=strtok(NULL, delim);
    }



    return 0;
}