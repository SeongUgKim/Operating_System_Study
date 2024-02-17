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
