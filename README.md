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


### fork() system call - used to create processes , It takes no arguments.

---


<br>

Return -
- pid of the child in the parent
- 0 on the child
- -1 if unsuccessful.

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

> **Orphan process** - This is a rinning process whose parent has finished or terminated.

> **Init process** - is the parent of all processes, executed by the kernel during the **booting** of the system. It has a pid of **1**.

> Process Table - is a data structure in the RAM of a computer that holds information about the processes. Currently been handled by the OS.

> **Process Entry** - is created when the process is created by a fork() system call. 



<br>
How code ran in orphan state ? 

- Parents executes and terminates before child.
- Child becomes an orphan because its parent died while it was still alive(executing)
- The init process (mother of all processes of system) adopts the child and becomes its parent until it terminates.
- This adoption changes the ppid of the child to 1 (the ppid of the init process) during its execution.
- Then init process then removes or reaps the child from the process table after its execution 
- This explains why we couldn't find the child process in the process table with the "ps -eaf" command.

















