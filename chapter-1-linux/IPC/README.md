# Inter-process Communication

The purpose of interprocess communication is to allow two programs to communicate with each other. Ths is required because individual processes have their own, separated memory spaces.

## Pipes

Pipes are essentially a FIFO data structure. The sending process is able to add information to the pipe, and the receiving process is able to read information from the pipe. When the pipe has been closed by the writer, the reader gets an EOF when attempting to read.

### C implementation

A call to `int pipe(int filedes[2])` instantiates two ***open*** file descriptors (the read and write ends, respectively).

### Key points

* A pipe is literally just a buffer in kernel memory.
* Multiple processes can write to a pipe
* It's implemented with a pipe buffer. Write will block until some data has been made available in pipe.
* Linux pipe capacity is 65,536 since 2.6.11