## Introduction

- process: running program (informal def)
- program: lifeless itself -> a bunch of instructions in disk
- os: running the program into something useful
- typical os maybe seemingly running tens or even hundreds of processes at the same time

### Time Sharing

- OS's virtualizing the CPU -> illusion that many virtual CPUs exists
- mechanisms: lovw-level methods or protocols that implment a needed piece of functionality
  - ex) context switch

### Policies

- poliices: algorithms for making some kind of decision within the os
  - ex) scheduling policy

## Abstraction

- machine state: what a program can read or update when it is running

### How memory constitutes a process?

- `Memory`: one component of a machine state in process
  - instructions and data lie in memory
- `Registers`
  - `program counter (PC)`: tells which instruction of the program will execute next
  - `frame pointer`: used to manage the stack for function parameters, local variables, and return address (stack pointer)
- `I/O`: persistent storage device

## Process Creation

- how programs are transformed into processes?
  - how does the OS get a program up and running?

### Transforming a pogram into a process

- `load` program code and static data into memory (address space of the process)
- program: initially resides on dis in some kind of executable format
  - loading program requires the OS to read those bytes from disk and place them in memory
- early OS: loading process is done eagerly
- modern OS: loading process is don lazily
  - `paging` and `swapping` topics are related

### Memory allocation

- after loading the program into memory, some memory must be allcoated for the program's run-time stack
- os also allocates some memory for the program's heap
  - dynamically allocated data (`malloc()` and `free()`)

### I/O related setup

- file descriptors

- finally jumping to the `main()` routine -> os transfers control of the CPU to the newly created process
  - program begins its execution

## Process States

### The Three States fo a Process

1. `Running`: a process is running on a processor => executing instructions
2. `Ready`: a process is ready to run but os has chosen not to run it yet
3. `Blocked`: a process has performed some kind of operation that make it not ready to run until some other event takes place
   - ex) I/O request to a disk

### Transitioning from one state to another

- a process can be moved between the ready and running states at the discretion of the os
  - scheduled: ready -> running
  - descheduled: running -> ready
- a process has become blocked the os keep it as such until some event occurs (I/O) => moves to the ready state again
- this is made by the os scheduler

## Data Structures

### Information of a Process that the OS tracks

- `xv6 kernel`'s process information tracking data sturcture

```
// the registers xv6 will save and restore
// to stop and subsequently restart a process
struct context {
    int eip;
    int esp;
    int ebx;
    int ecx;
    int edx;
    int esi;
    int edi;
    int ebp;
}

// the different states a process can be in
enum proc_state {
    UNUSED,
    EMBRYO,
    SLEEPING,
    RUNNABLE,
    RUNNING,
    ZOMBIE,
};

// the information xv6 tracks about each process
// including its register context and state
struct proc
{
    char *mem;                  // Start of process memory
    uint sz;                    // Size of process memory
    char *kstack;               // Bottom of kernel stack for this process
    enum proc_state state;      // Process state
    int pid;                    // Process ID
    struct proc *parent;        // Parent process
    void *chan;                 // If !zero, sleeping on chan
    int killed;                 // If !zero, has been killed
    struct file *ofile[NOFILE];   // Open files
    struct inode *cwd;          // Current directiory
    struct context context;     // Switch here to run process
    struct trapfram *tf;        // Trap frame for the current interrupt
};
```

- `register context`: contents of process's registers
  - process is stopped => its registers will be saved to this memory location
  - by restoring these registers (placing their values back into the actual physical registers), the OS can resume running the process
- `zombie state`: `final`state where it has exited but has not been cleaned up yet
  - useful as it allows other processes to examine the return code of the process and see if the just-finished process executed successfullly

## Simulator
