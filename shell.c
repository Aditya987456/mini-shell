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





//## handles built in commands here - cd, pwd, help, exit 
//(we can do many more but i am just taking this main main things...)

int handle_builtIn(char **args){

    // 1. exit  --> if exit types by user check by comparing and then, exit, since exit(0) - becz no error exit it is just by user.
    if(strcmp(args[0], "exit") == 0){
        exit(0);
    }



    // 2. cd 
    if(strcmp(args[0], "cd") == 0){
        if(args[1] == NULL){
        printf("cd: missing argument\n");

        } else {
            if(chdir(args[1]) != 0){  //folder doesn't exist here...therefore it not return success i.e 0
                perror("cd failed");
            }
        }
        return 1;  //means found the cd
    }



    //3. pwd
    if(strcmp(args[0], "pwd") == 0){

        char cwd[1024];   //i should use dma later...

        if(getcwd(cwd, sizeof(cwd)) != NULL){
            printf("%s\n", cwd);
        }else{
            perror("pwd failed");
        }


        return 1;
    }




    //4. help
    if(strcmp(args[0], "help") == 0){

        printf("Hey thsese are some built-in commands:\n");
        printf("cd <dir>\n");
        printf("pwd\n");
        printf("exit\n");
        printf("help\n");

        return 1;
    }





    return 0; //means builtin is not there so return 0 now it will do execute work...using execute funtion.
}













int main(){

    while(1){
        printf("Aditya-Shell :> ");
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



    // Check is there is any builtin command ??? if there handling manually...by own builtin function
    if(handle_builtIn(args) == 1){
        continue;
    }




    //#3: 
    execute_command(args);




    }

    return 0;
}

