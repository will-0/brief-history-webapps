# Inter-process Communication

The purpose of interprocess communication is to allow two programs to communicate with each other. Ths is required because individual processes have their own, separated memory spaces.

## Pipes

Pipes are essentially a FIFO data structure. The sending process is able to add information to the pipe, and the receiving process is able to read information from the pipe. When the pipe has been closed by the writer, the reader gets an EOF when attempting to read.

### C implementation

A call to `int pipe(int filedes[2])` instantiates two ***open*** file descriptors (the read and write ends, respectively).
A read will generate an EOF response ONLY when all file descriptors (i.e. including an forked processes) close the file.

### Why close file descriptors?

* If reading process doesn't close write descriptors: read will block even when writing process has called `close`.
* If the writing process doesn't close read descriptors: write won't then generate an error if writing to a pipe with read descriptors closed.

In general, also good for memory. Pipe remains open until all file descriptors in all processes have been closed.

### Usage for synchronization



### Key points

* A pipe is literally just a buffer in kernel memory.
* Multiple processes can write to a pipe
* The pipe will typically be created by a common ancestor (can't just be between two arbitrary processes).
  - There's an exception to this rule if using UNIX domain sockets, but this is abnormal.
* It's implemented with a pipe buffer. Write will block until some data has been made available in pipe.
* Linux pipe capacity is 65,536 since 2.6.11