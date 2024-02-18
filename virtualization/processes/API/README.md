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

## Motivating the API

- separation of `fork()` and `exec()` is essential in building a UNIX shell
- this separation lets the shell run code after the call to `fork()` but before the call to `exec()`
  - able to alter the env of the about-to-be-run program
  - enables a variety of interesting features to be readily built.

1. shows a prompt and wait for user to type something into it
2. after getting the input, shell figures out where in the file system the executable resides
3. calls `fork()` to create a new child process to run the command
4. calls some variant of `exec()` to run the command
5. waits for the command to complete by calling `wait()`
6. child completes, the shell returns from `wait()` and prints out a prompt again

- ex)
- `prompt > wc p3.c > newfile.txt`
  - the way the shell accoomplishes this task is simple:
  - child process is created, before calling `exec()`, the shell closes standard output and opens the file `newfile.txt`

### Pipeline

- UNIX pipes are implemented in a similar way but with the pipe() system call
  - output of one process is connected to an in-kernel pipe, and the input of another process is connected to that same pipe
  - the output of one process seamlessly is used as input to the next
  - useful chains of commands
- ex)
- `grep -o foo file | wc -l`
  - grab a word foo => using output and count word

## Process Control and Users

### Sending Signals to a Process

- Beyond fokr(), exec(), and wait(), there are a lot of other interfaces for interacting with processes in UNIX system
- `kill()` system call: used to send signals to a process, including directives to pause, die and other useful imperatives
- signal subsystem => deliver external events to processes (receive, process, and send those signals within individual processes)
  - to use this form of communication, a process should use the `signal()` system call to catch various signals
  - ensure that when a particular signal is delivered to a process, it will suspend its normal execution and run a particular piece of code in response to the signal

### Giving Control of Processes to Users

- users generally can only control their own processes
- job of os: parcel out resources (cpu, memory, and disk) to each user to meet overall system goals
- `Superuser (Root)`
  - a user who can administer the system
  - not limited in the way most users are
  - able to run powerful commands such as `shutdown`
  - with great power comes great responsibility => need to increase security
