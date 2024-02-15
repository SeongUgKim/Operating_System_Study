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
