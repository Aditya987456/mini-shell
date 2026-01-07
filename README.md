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

### 6. 






