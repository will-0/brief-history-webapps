# Chapter 1 - Operating Systems

The first step in understanding how web apps are implemented is understanding how operating systems actually work.
Deep understanding of the core concepts (processes, sockets, etc.) will be foundational for subsequent understanding.

## Approach

- [] "The Linux Programming Interface"

## Definition

OS commonly used with two meanings:

1. Central software that manages and allocates computer resources (i.e. CPU, RAM, devices)
2. Entire package, including the above, as well as accompanying standard software tools (e.g. CLI, GUI, file utilities, editors)

An operating system *kernel* is synonymous with the first definition.

## Kernel tasks

- Scheduling
- Memory management (Linux uses *Virtual* memory management)
- Provision of a file system
- Creation and termination of processes
- Access to devices
- Networking
- System call APIs
- *Virtual private computer \[optional\]*

### Kernel vs user mode

- Implemented at the level of the processor
- Hardware interrupts to switch between the two

## Files

- User processes don't know where on a physical device files are stored, they just know their names
- Each file is marked with a type (e.g. plain, directory)
- Permissions: there are three groups (owner, group, rest-of-world), with read/write/execute bits (9 total) for each.

### Universal I/O

- Kernel essentially provides one file type: a sequential stream of bytes (with optional random access using `lseek`)
- In UNIX, end-of-file is detected by a read that returns no data.
- Kernal I/O system refers to files by a small non-negative integer. Processes usually inherit 0, 1 and 2 as `stdin`, `stdout`, `stderr`.

### Programs

- Create new processes using `fork()`
- A child process initially looks exactly the same. However, it can use `execve()` to load and execute an entirely new program.

### Directories

Directories:special type of file, whose contents are a table of *links*.
Link: a filename + file reference association
Symbolic Link: filename + filename association

## Processes

### Inter-Process Communication (IPC)

## Signals

Signals are essentially "software interrupts". They are sent to specific processes.
Signals can be ignored, used to kill the process, or get suspended until another resume signal arrives.
You can register event handlers for them.

## The shell

On Linux, the shell is just a user process.

## Fun Facts

- C was basically developed as a high-level language for implementing the UNIX kernel
- First 6 editions of UNIX were developed 1971 - 1975
- BSD was created a Berkeley, where they added several new features
- System V was created by AT&T, and then adapted for things like MacOS
- TCP/IP implementation was first done in 4.2BSD in 1983
- GNU was an implementation of a UNIX-like OS that was meant to be legally free (unlike UNIX, which had restrictions from AT&T)
  - It basically had the full implementation, it just didn't have a kernel.
- Linux 1.0 was released in 1994, 2.6 in 2003
- POSIX (an abbreviation of Portable Operating System Interface) refers to a group of standards developed by IEEE
  - POSIX.1 documents an API for a set of services that should be made available to a program by a conforming operating system
- SUSv3 = Single UNIX Specification Version 3
  - Defines definitions/concepts/terms (XBD); system interfaces (XSH); shell/utilities (XCU)