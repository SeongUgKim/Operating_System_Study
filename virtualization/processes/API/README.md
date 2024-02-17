## Introduction

- process creation in UNIX system
- `fork()`, `exec()`, `wait()`

## The fork() System Call

- `fork()`: system call
  - used to create a new process

### `p1.c`

- process prints out a hello world message including its process id (PID)
  - PID: used to name the process if one wants to do something with the process
- `fork()` system call
  - the process that is created is (almost) exact copy of the calling process
  - there are two copies of the program `p1` running and both are about to return from the `fork()`
  - newly-created process (child): does not start running at `main()` => no print out hello world message in `main()`
    - it just comes into life as if it had called `fork` itself
    - different value is returned to the caller of `fork`
    - parent: receives the PID of the child
    - child: receives the zero PID

### Non-dterministic output

- `p1.c` does not have determinisitic output
- child process is created => two active processes in the system
- single CPU => either the child or the parent might run at that point
- CPU scheduler determines which process runs at a given moment in time

## The wait() System Call

- it is quite useful for a parent to wait for a child process to finish
- call `wait()` system call

### p2.c

- parent process calls `wait()` => delay its execution until the child finishes executing

## The exec() System Call

### p3.c

- `execvp()`: run the program `wc` in child process
- `fork()` system call is starnge
- `exec()` is not normal too
- given the name of the executable (e.g., `wc`) and some arguments (e.g., `p3.c`)
  - `exec()` loads code (and static data) from that executable and overwirtes its current code segment (and current static data) with it
  - the heap, stck, and other parts of memory space of the program are re-initialized
  - then os simply runs that program => it does not create a new process, but it transforms the currently running program into a different running program
    - p3 -> wc
