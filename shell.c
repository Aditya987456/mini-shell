#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>






//step-1 : Read input.
int read_input(char **line, size_t *len){
    if(getline(line, len, stdin) == -1){
        return 0;
    }
    return 1;
}



//step-2: Parse Input -> splits string into pieces using delimiters
/*
Why char **args ?

Because:

char *args[100];
is: array of char pointers

When passed to function:
array decays into pointer

So type becomes:
char **

| Code              | Meaning                      |
| ----------------- | ---------------------------- |
| `char *line`      | one string pointer           |
| `char *args[100]` | array of 100 string pointers |

*/
void parse_input(char *line, char **args){
    int i=0;

    char *token = strtok(line, " \n");

    while(token != NULL){
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i]=NULL;

}




//step-3: Execute command - 
void execute_command(char **args){
    pid_t pid = fork();

    if(pid == 0){
        //child ...

        execvp(args[0], args);
        perror("Exec error");
        exit(1);
    }else{
        //parent
        wait(NULL);
    }
}
















int main(){

    while(1){
        printf("Aditya-Shell :) ");
        fflush(stdout);  //output may wait in buffer so it force print now.
    


/*  here line is a pointer to character(string) , 
    since string becz - not single char is there multiple char is there */
    char *line = NULL;  

    size_t len = 0;
    char *args[100]; //here i think we should define dynamic like things not fixed...



    //#1
    if (!read_input(&line, &len)) {
        printf("\nExiting shell...\n");
        break;
    }
    

    //#2
    parse_input(line, args);



    //#3: 
    execute_command(args);




    }

    return 0;
}

