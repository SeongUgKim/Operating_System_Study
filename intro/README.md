## Virtualization

- physical resource -> general virtual form => refer os as virtual machine
- provides interfaces (APIs)
  - system call
  - standard library
- programs share CPU, memory, disk -> os = resource manager

## Virtualizing the CPU

- `Spin()`: repeatedly checks the time and returns once it has run for a second
- `./cpu A & ./cpu B & ./cpu C & ./cpu D &`
  - with only one processor, all four of these programs seem to be running at the same time
  - illusion that the system has very large number of virtual CPUs
- virtualizing the CPU: turning a single cpu (or a small set of them) into a seemingly infinite # of CPUs
  - allowing many programs to seemingly run at once

## Virtualizing Memory

- memory: array of bytes
  - read: specify an address to access data stored
  - write: specify the data to be written to the given address
- program keeps data structures in memory
- instruction of program is in memory too

### mem.c

- `malloc()`: allocates some memory
- run mem.c with multiple instances of the same program
- p is allocated on same memory but each instance updates value at p independently
  - each running program has its own private mem (not sharing same physical memory)
- each process accesses its own private virtual address space
  - os maps onto the physical memory of the machine

## Concurrency

- OS is juggling many things at once

### Multi Threaded Programs

- thread: as a function running with the same memory space as other functions, with more than one of them active at a time
- in `thread.c`:
  - each thread starts running in a routine (`worker`)
  - with high number of `loops` => result = unusual value
  - shared `counter` is incremented requires three instructions
  1. load the value of the counter from memory into a register
  2. increment
  3. store it back to memory
  - these three instructions do not execute atomically => problem of concurrency

## Persistence

- DRAM => volatile storage => data can be easily lost
- need hardware & software to be able to store data persistently
- hardware => I/O device, hard drive is common repo for long term info (also solid state drives (SSD))
- software => file system
- os does not create a private virtualized disk for each application

### io.c

- three system calls

1. `open()`: opens the file and creates it
2. `write()`: writes some data to the file
3. `close()`: closes the file

- these system calls are routed to the part of the os called `file system`
