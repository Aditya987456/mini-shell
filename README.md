# Mini-Shell

A minimal Unix-like shell in C to understand how operating systems
execute commands under the hood.

Building this project for  **learning OS fundamentals**.



<br>
<br>
<br>



## Mini Shell — Simple Summary

A shell is a program that:
- takes commands from user
- understands them
- runs programs
- keeps running forever

Example:
```bash
ls
mkdir test
cd folder
```


<br>
<br>



**NOTE -** I am NOT building commands like:

- `ls`
- `mkdir`
- `touch`

Linux already has those programs.

**I am building:** the thing that runs those commands.

My shell: ```Aditya-Shell :>```

- reads input
- parses command
- creates child process using `fork()`
- runs program using `execvp()`
- waits using `wait()`

<br>

Also, Special commands like:

```bash
cd, exit, pwd, help
```

cannot use `execvp()`,
so shell handles them manually using:

<br>
<br>


When I run:

```bash
./shell
```

terminal changes from:

```bash
aditya2981@HP:~/mini-shell$  ---> Aditya-Shell :>
```

<br>
<br>


**i.e** Now my shell is running on top of Bash.

Even if I do:

```bash
cd ../../
```

I am NOT leaving my shell. 
Only current directory changes.


<br>
Commands like:

```bash
mkdir
touch
ls
```

still work because my shell calls Linux executables like:

```bash
/bin/ls
/bin/mkdir
```


<br>
<br>
<br>


> Goal of this project is NOT replacing Bash.

Goal is:

- understanding OS internals
- process creation
- command execution
- how shells work internally

<br>

**Important concepts learned:**

- `fork()`
- `execvp()`
- `wait()`
- processes
- command parsing
- current working directory
- built-in commands



<br>
<br>

> **Future improvements planned:**
- pipes (`|`)
- input/output redirection
- background processes
- signal handling
- command history



<br>
<br>
<br>


## **Learnings** -


```
User
 ↓
Terminal (window / UI)
 ↓
Shell (command interpreter) - A shell is a program that lets users run commands.
 ↓
System Calls - A system call is how a program asks the kernel to do something.
 ↓
Kernel - Core OS component that manages hardware and system resources
 ↓
Hardware



```

<br>

### 1. Operating System (OS) -
 An Operating System (OS) is system software that manages computer hardware and software resources, and provides services for computer programs. It acts as a bridge between the user and the hardware.

 - linux, windows, macOS.
 - **OS** = kernel + system services.

 

<br>

### 2. Kernel - 
- Talks directly to hardware

- Manages CPU scheduling

- Manages memory

- Manages disk & files

- Manages processes

- Enforces security

<br>
<br>


> User space vs Kernel space.

- User space -> shell , GUI, Browsers, Our programs...
- Kernel space -> full hardware access.

- User Program cannot access the hardware directly they need to call system.

<br>
<br>

### 3. Kernel only understand process - everything for him is process...

- Shell = process

- GUI = process

- Browser = process

- Your C program = process

- **Kernel** --> create, schedule, stops and kill processs.

<br>
<br>

### 5. Unix like system means?
There are two big families of OS- <br>
1.unix like world <br>
2.Non unix world


1. UNIX like system means --- follows unix philosophy , uses POAIX style api ( like fork, exec... | (pipe)) concepts.<br>
eg - Linux, MacOS.

2. Non Unix like system - Object-based pipelines (not text), 
NT kernel APIs.<br>
eg - Windows

> **WSL** (Windows Subsystem for Linux) - matlab not we use unix like system on windows it just means that Windows runs a real Linux environment, Windows is hosting Linux.

<br>
<br>

### 4. Shell -- User space program gives interface to interact with kernel using sysytem calls.

> **Shell is as -> REPL** - Read, Evaluate, Print, Loop.

- Interprets commands  --> Talks to kernel

- Program running inside terminal(its just a windows, eg-gnome,windows terminal.)

- eg - bash, zsh, PowerShell

<br>

> why GUI if shell is there - because gui is for begineer task and user friendly but bad for automated system, repetative task , not scale ... 
**GUI under the hood use same kernel api as shell.**

<br>

> **WHY Many shells?**<br>
Because shell = s/w <br>
bash(Linux) - stability, servers<br>
zsh(macOS) - developer productivity<br>
PowerShell(Windows) - Windows automation (object-based)

<br>

> ### Why shell exists if kernel already exists? <br>
Because kernel does not understand human language<br>
Kernel understands- 
Syscalls, 
Memory addresses, 
Registers.


```
Shell translates- 
 “List files” → system calls → kernel actions 
 ```

 ```
 shell → fork → exec(ls) → kernel → disk → output
 ```




<br>
<br>

### steps in creating shell-

1. Process Indentifier (PID) and Parent Process Identifier(PPID).
2. Command Line Argument (argc and argv)
3. Creating Processesn( with execve ststem calll)
4. Creating Processed ( with the fork system call)
5. Suspending Processes ( with the wait system call)
6. File Information ( with the stat system call)
7. Environment ( printenv, etc)


---

---


<br>
<br>
<br>



### 1. Process Identifier (PID) and Parent Process Identifier (PPID)
---

**Process** - It is an instance of an executing program that has a unique ID.
It is basically a program in execution.

> **parent process** - process that creates the child process.

> **Parent Process identifier(PPID)** - uniques identifier of the parent process.

<br>

> **pid_t** - data type is a signed integer capable of representing a process ID.


<br>


```
- Shell is a process
- Commands are child processes
```

<br>
<br>
<br>


> **What happens when we open terminal**

OS starts: 
- terminal program
- shell (like bash)

```
systemd (PID 1)
 └── terminal
      └── bash    
```

- bash becomes the parent process


<br>


> **What is PID = 1?**

PID 1 = first process started by OS (usually systemd)
- Created at system boot
- Parent of all processes
- Adopts orphan processes


<br>
<br>
<br>
<br>
<br>


### fork() system call - used to create processes , It takes no arguments.

---


<br>

Return -
- pid of the child in the parent
- 0 on the child
- -1 if unsuccessful.

<br>

> **fork() returns a value so that parent and child can identify themselves and execute different logic.**

> **Basic operation -** After a new child process is created, both processes will execute the new instruction following the fork() system call.


<br>
<br>

Before fork-
```
Shell (PID 2000)

```

After fork-

```
Shell (PID 2000)  ← parent
└── Shell (PID 2001)  ← child (copy)

```

<br>

**When we open terminal -** <br>
- A shell (like bash) starts<br>
- The shell runs in a loop<br>
- It waits for your commands.


<br>
<br>

```
If a command must change the shell → no fork
If a command can safely die → use fork
```
<br>

```
Shell (always alive)
├── ls      (child, dies)
├── ps      (child, dies)
├── mkdir   (child, dies, folder stays)
├── touch   (child, dies, file stays)
└── cd      (runs inside shell)

```


<br>
<br>


> **Why fork is ALWAYS needed (external commands)**

Because:
- Shell must stay alive
- Without fork:
- bash → exec(ls) → bash gone 


<br>
<br>
<br>


> **Why can’t bash just run your program directly?**

If bash did:  
execvp("./a.out", argv);

Then:    
```
bash → becomes your program → exits → shell gone 
```
- We will lose the terminal

- That’s why fork is needed

-  **fork() protects the shell by running our program in a separate process.**



<br>
<br>
<br>
<br>


> When we call fork(), why does it return a value? Why not just create a process silently?

fork() returns a value so that BOTH processes (parent and child) can know who they are.
Because after fork(), two processes are running the same code.


<br>
<br>
<br>


```After fork()```

Two processes now exist:  
- Process 1 (Parent)  
- Process 2 (Child)

***Both processes run the program — but each process chooses a different branch. Therefore both block runs -***


<br>
<br>

```
getpid() → real process ID
pid (from fork()) → just a signal value
```

```
pid == 0   → child
pid > 0    → parent (value = child PID)
pid == -1  → error (fork failed)
```

<br>
<br>

**When pid = -1?**
- Too many processes
- Not enough memory
- System limit reached

<br>
<br>

> **Mental model (ROOM concept - my observation.)**
-  Child room → pid = 0
-  Parent room → pid > 0 (child PID)


<br>
<br>
<br>


```
pid_t pid = fork();

if (pid == 0) {
    printf("Child\n");
} else {
    printf("Parent\n");
}
```
<br>

Output-
```   
Child
Parent
```

<br>
<br>
<br>

> **Real use of fork returning the pid.**
```
pid = fork();

if (pid == 0) {
    execvp("ls", argv);   // child runs command
} else {
    wait(NULL);           // parent waits
}
```

***Now we can correctly do -***
```
child → exec
parent → wait
```

<br>
<br>
<br>

> **Imp things -** 
 - Parent id of child process changes during execution to 1.
 - child process is removed from process table after exceution.

<br>
<br>
<br>

> **Orphan process** - This is a running process whose parent has finished or terminated.

> **Init process** - is the parent of all processes, executed by the kernel during the **booting** of the system. It has a pid of **1**.

> Note - “In modern Linux systems, orphan processes are not always adopted by PID 1. They may be adopted by an intermediate process acting as a subreaper (like a shell or systemd), which is why the PPID may not be 1.”

> Process Table - is a data structure in the RAM of a computer that holds information about the processes. Currently been handled by the OS.

> **Process Entry** - is created when the process is created by a fork() system call. 



<br>
How code ran in orphan state ? 

- Parents executes and terminates before child.
- Child becomes an orphan because its parent died while it was still alive(executing)
- The init process (mother of all processes of system) adopts the child and becomes its parent until it terminates.
- This adoption changes the ppid of the child to 1 (the ppid of the init process) during its execution.
- Then init process then **removes** or reaps the child from the ***process table*** after its execution 
- This explains why we couldn't find the child process in the process table with the "ps -eaf" command.

<br>
<br>

> **Zombie Process** - A process that has finished execution, but whose parent has NOT collected its exit status.

- Zombie exists ONLY because parent hasn’t called wait() yet

```
Child exits → becomes zombie
        ↓
Parent calls wait()
        ↓
Kernel:
  - gives exit status to parent
  - deletes process table entry
        ↓
Zombie disappears
```

<br>
<br>
<br>

Correct way - 
```
if (fork() == 0) {
    exit(0);
} else {
    wait(NULL);  // cleans zombie immediately
}
```

<br>


```
There is one process table per system. The size of the process table is finite . If too many zombie processes are generated, then the process table will be full. That is , the system will not be able to generate any new process, then the system will come to a standstill. Hence, we need to prevent the creation of zombie processes.

> Process to prevent creation of zombie process - 
1. using wait() system call.
2. 
```


<br>
<br>
<br>
<br>



### **wait() vs sleep()**

> **wait()**
- Used for process management
- Parent waits for child to finish
- Removes zombie process
- Returns child’s PID + exit status


> **sleep()**
- Used for delaying execution
- Pauses process for given time
- Does NOT interact with child processes
- Does NOT remove zombies
-  just a timer


<br>

```
fork();

sleep(10);   // zombie stays

wait(NULL);  // zombie removed
```



<br>
<br>
<br>
<br>



###  **execve()**
---
execve() is a system call that replaces the currently running program inside a process with a new program.

execve() replaces the current process image with a new program without creating a new process, keeping the same PID.

```
int execve(const char *path, char *const argv[], char *const envp[]);
```
- path → exact path of executable (e.g. /bin/ls)<br>
- argv → argument list (must end with NULL) <br>
- envp → environment variables (must end with NULL)

<br>

> If execve() succeeds, it never returns. <br>Code after execve() runs only if it fails.

<br>

> **Why shells need fork() before execve()**

* If a shell called execve() directly:<br>
```shell → becomes command → exits → shell gone ```

* therefore shell do things like this - <br>
 ``` fork() ,  child  → execve(command) , parent → stays shell```


<br>
<br>

```
argv is an array of argument strings passed to the new program. by convention , the first of these strings should contain the filename associated with the file being executed. envp is an array of strings, conventionally of the form key=value, which are passed as environment to the new program. Both argv and envp must be terminated by a NULL pointer. The argument vector and environment can be accessed by the called program's main funvtion, when it is defined as:
```


<br>
<br>
<br>

> **Here use -- execvp() instead of execve()** <br>


**execvp()** is useful because:

- automatically searches PATH
- also lets you pass custom environment variables


Example: ```execvp("ls", args, custom_env);```

Meaning:<br>
Find **ls** automatically using PATH<br>
and run it with custom environment.

 <br>
 <br>
 <br>
 <br>
 <br>


 ### **Getline()** - It reads an entire line of input and automatically allocates enough memory (buffer) to store it.
 ---  

 <br>
 <br>

**Why getline() is needed ?**

In shell programs, input length is unknown. Using fixed-size buffers (like char buf[100]) can:<br>
- Cut long input
- Cause buffer overflow
- Break commands

<br>

<br>

> getline() changes the **pointer** itself. Not just contents.<br>
* allocate memory<br>
* resize memory<br>
* change line<br>

***So function needs access to ORIGINAL pointer.***

<br>

> *getline() solves this by allocating memory dynamically. (DMA)*

> **Buffer** - A buffer is a chunk of memory used to temporarily store input.<br>
With getline(), the buffer is:<br>
Created automatically<br>
Grown automatically if input is long.

<br>
<br>

Syntax -
```
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
```
lineptr → pointer to the buffer (may be allocated or resized)<br>
n → size of allocated buffer<br>
stream → input source (stdin)

<br>

```
getline() dynamically reads a full line from input, allocating or resizing memory automatically, and stores it in a buffer (line) whose size (len) is managed internally.
```
<br>

> **getline() working internally** --- <br>
- Checks if buffer exists

- Allocates memory if needed

- Reads the full line (including spaces)

- Stores the line in buffer

- Appends '\n' and '\0'


<br>

```
1. Check: line == NULL ?
   → YES → malloc(initial_size)

2. Read input character by character

3. If buffer too small:
   → realloc(bigger_size)

4. Store string (with '\n' + '\0')

5. Update:
   line → buffer
   len  → new size

6. Return number of characters read
```

<br>
<br>
<br>


> Why not use int for size?

Because int can overflow and is not portable; size_t safely represents memory sizes.

<br>

> Difference between size_t and ssize_t?

size_t is unsigned and used for sizes, while ssize_t is signed and used for return values that may indicate errors.

<br>

```
size_t = size only
ssize_t = size OR error
```

<br>
<br>

> **Working -**
```
getline() reads an entire line from stream, storing the address of the buffer containing the text into *lineptr. The buffer is null-terminated and includes the newline character, if one was found.

If *lineptr is NULL, then getline() will allocate a buffer for storing the line, which should be freed by the user program.

Alternatively, before calling getline(), *lineptr can contain a pointer to a malloc(3) allocated buffer *n byter in size. If the buffer is not large enough to hold the line, getline() resizes it with realloc(30), updating *lineptr and *n as necessary.
```




<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>



### Strtok() - function that splits a string into pieces using delimiters
---


<br>
<br>
<br>


```
char *strtok(char *str, const char *delim);
```
**str** → input string (only first time) <br>
**delim** → characters where splitting happens.(characters where to split).<br>
**return** → pointer to token

<br>
<br>


> **Best mental model** -
```
strtok = cutter,
string = rope,
delim = places to cut.
```

<br>
<br>

> **strtok does**:

- Find delimiter --> things that we have gave in *delim.
- Replace it with '\0'
- Return start of token
- Remember where it stopped
- Continue next time.

<br>

```
strtok(str, " ");   // first call
strtok(NULL, " ");  // next calls

means --> continue from last position (don’t restart).
```

<br>
for this strtok uses - a hidden static pointer

- static char *saved_ptr;
- first call → start from str
- next calls → continue from saved_ptr

```
Because it remembers position, so
NULL = continue from last cut.
```

<br>
<br>

> **Note** - Input string must be writable.<br>
strtok modifies string -- replaces delimiter with \0 <br>
therefore array not char * i.e string.


<br>
<br>
<br>


> **IMPORTANT NOTE - about strtok...** 

```
1. This is not safe:
    char *str = "hello world";
    strtok(str, " ");

    Because:
    "hello world" is in read-only memory
    strtok tries to modify it → crash / undefined behavior.


2. This is SAFE:
    char str[] = "hello world";
    strtok(str, " ");

    Because:
    string is copied into writable memory
    strtok can modify it.


3. Also safe (copy method):
    char *str = "hello world";
    char newStr[50];
    strcpy(newStr, str);
    strtok(newStr, " ");

    Because:
    we created a writable copy.

```



<br>
<br>
<br>
<br>
<br>
<br>
<br>


### Command line argument - These are argument passed from the command line to the C program when they are executed. 
---

- Inputs passed to program, stored as array of strings (argv) with count (argc)

<br>




```
int main(int argc, char *argv[])
```


<br>
<br>


> **Argument count - [argc]**
stores number of command line arguments passed by the user including the name of the program.

<br>

> **Argument Vectors - [argv]**
This is a NULL terminated array of strings (character pointers) used to store the entire list of command line arguments.


<br>
<br>


```
Example -

./program hello world

argc = 3
argv = ["./program", "hello", "world"]

```


**NOTE** - argv is an array of string pointers, so it can be written as either char *argv[] or char **argv


<br>
<br>
<br>
<br>
<br>


# Shell.c <br>
### Now Implementing everything at one place-

<br>
<br>


> **Full flow -** 
<br>
User types → shell reads → shell splits → shell decides → shell executes → repeat 

<br>
<br>
<br>



##  Pointer concept here...

### Basic Variables

```c
int a = 10;
```

- `a` → normal variable
- type = `int`

Now,  **&a  --> address of a** 

Rule:

```txt
If x is type T
then &x is type T*
```

Examples:

| Variable Type | After `&` |
|---|---|
| `int` | `int *` |
| `int *` | `int **` |
| `char *` | `char **` |

Taking address adds one `*`.

---

### Pointer (`*`)

```c
int *p = &a;
```

Means - p stores **address** of a



<br>

#### Two Meanings of `*`

> In Declaration - means pointer type.<br>
char *p;



<br>

> In Expression - means dereference/access value. <br>
*p

<br>
<br>

---

### Double Pointer (`**`)

```c
int **pp = &p;
```

---

<br>

### Strings in C

```c
char *line;
```

means:

```txt
pointer to string
```

Example: line ---> "hello"


---

<br>


### NULL Pointer

```c
char *line = NULL;
```

means:
- pointer variable exists
- currently points nowhere

NOT that variable doesn't exist.

---

<br>
<br>

### Why `char **` ?

Used when:
- modifying original pointer
- dynamic memory allocation
- arrays of strings

---

### getline()

```c
getline(&line, &len, stdin);
```

Because:

| Expression | Type |
|---|---|
| `line` | `char *` |
| `&line` | `char **` |

`getline()` internally do:

```c
*line = malloc(...);
```

**so it needs:** char **


---

<br>

### strtok()

```c
char *token = strtok(line, " ");
```

- splits string into tokens
- returns `char *`

<br>

`strtok()` modifies original string:

```txt
"ls -la /home"
```

becomes:

```txt
"ls\0-la\0/home\0"
```

---

<br>
<br>

### args Array

```c
char *args[100];
```

stores multiple token pointers:

```txt
args[0] ---> "ls"
args[1] ---> "-la"
args[2] ---> "/home"
args[3] ---> NULL
```


---


<br>
<br>
<br>
<br>


### **getline vs strtok**
-----------------------------------

<br>

> **getline(&line, &len, stdin)**

- allocates/resizes memory
- changes line pointer
- updates len
- stores input content

Internally (under the hood):<br>
- line = malloc(...)<br>
- len = new_size

**Therefore:**<br>
char **line<br>
size_t *len

<br>
<br>

> **strtok(line, " \n")**

- uses existing memory
- dereferences line
- replaces delimiters with '\0'
- returns token pointers

**Internally conceptually:**
*line = '\0'

**Therefore:**
char *line

-----------------------------------

<br>
<br>


```
Rule:
Changing POINTER  -> use **
Changing CONTENT  -> use *
```


-----



<br>
<br>
<br>
<br>
<br>

### execution step -

**User types:**
```
ls -l
```


**After parsing:**
```
args[0] = "ls"
args[1] = "-l"
args[2] = NULL
```

execvp(args[0], args);

becomes: ```execvp("ls", ["ls", "-l", NULL]);```

<br>

> **NOTE -** <br>
***Unix convention -*** argv[0] should contain the program name, so shells pass the command name again inside the argument array.()

<br>

Means:
1. args[0]
   → which program to run
   → "ls"

2. args
   → full argument list passed into program
   → becomes argv[] inside ls program

<br>

**fork():**
    creates child process

**execvp():**
    replaces child with actual program

**wait():**
    parent shell waits for child to finish

> Flow:<br>
shell → fork → child → execvp → ls runs → child exits → shell continues



<br>
<br>
<br>
<br>

### Some extra built in command like cd, exit, pwd, help that need to handle separately not using fork+execve
---

<br>

> **NOTE**: ***Because the shell itself is just a running process.<br>
Some commands need to change or control that exact process, not a temporary child process.***

<br>
<br>


> **cd** - here we use chdir()

chdir() is a system call wrapper.

It asks Linux kernel: 
"Change current working directory
of this process."





<br>
<br>
































