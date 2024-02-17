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
