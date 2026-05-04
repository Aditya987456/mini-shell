#include<stdlib.h>
#include<stdio.h>
#include<string.h>






//step-1 : Read input.
int read_input(char **line, size_t *len){
    if(getline(line, len, stdin) == -1){
        return 0;
    }
    return 1;
}



//step-2: Parse Input -> splits string into pieces using delimiters
void parse_input(char *line, char **args){
    int i=0;

    char *token = strtok(line, " \n");

    while(token != NULL){
        args[i++] = token;
        strtok(NULL, " \n");
    }
    args[i]=NULL;

}














int main(){

    while(1){
        printf("Aditya-Shell :)");
    



    char *line = NULL;  //here line is a pointer to character(string) , since string becz - not single char is there
    size_t len = 0;
    char *args[100]; //here i think we should define dynamic like things not fixed...



    //#1
    if (!read_input(&line, &len)) {
        printf("\nExiting shell...\n");
        break;
    }
    

    //#2
    parse_input(line, args);



    }

    return 0;
}

