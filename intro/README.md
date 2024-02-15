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
