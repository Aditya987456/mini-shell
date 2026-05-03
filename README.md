# Mini-Shell

A minimal Unix-like shell in C to understand how operating systems
execute commands under the hood.

Building this project for  **learning OS fundamentals**.





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


### Command line argument
---



































<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>




## Printf basics -
| Specifier | Meaning           |
| --------- | ----------------- |
| `%s`      | string (`char *`) |
| `%d`      | int               |
| `%u`      | unsigned int      |
| `%c`      | char              |
| `%f`      | float             |
| `%p`      | pointer           |

















