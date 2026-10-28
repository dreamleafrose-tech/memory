# Memory!

## Create Memory

Create a Memory class which functions as an "array of bytes".

- start with a std::vector to hold the data
- in C, we commonly use the type **unsigned char** to store byte data
  - char, uint8_t, a typdef'd byte or, in modern c++ std::byte will all work too
- Write methods to store() and load() a byte to a specific memory location
- Write a bounds check to use when store() and load() are called
  - throw a std::out_of_range exception when out of bounds
- Test the Memory class by writing a main which stores and then loads a character
- Expand your main.cpp to write and read a string!

## Next Steps

1.  Multi-byte load/store

Add store16/store32 and load16/load32, or a templated store<T>.

- Endianness. Choose a byte order and test it, e.g. store 0x12345678, then `load()` returns 0x78".
- Bounds at the edge. A 4-byte store at size - 2 is in bounds for its first byte but not its last byte, so inBounds(address) alone doesn't work.
- Overflow. address + 3 can wrap around a uint64_t.

2. MMU with base and limit registers

This changes the model from memory as an array of bytes to "every address a process uses is translated":

- logical vs. physical addresses, with physical = base + logical checked against limit
- protection: a fault is a check in the translation step, which generalizes the inBounds()
- a context switch is saving and restoring two registers (base and limit), which enables relocation

Make the MMU a separate class in front of Memory. Later, it lets us swap in segmentation or paging later without modifying Memory.

3. Memory-access tracing

A memory-access trace tool logs each access. Then we can compute access statistics or replay a trace through our memory system. 

4. Allocator over all of physical memory

The OS, with our current memory model, allocates contiguous segments to processes. 

- create a **free list** to track memory allocations
- implement first fit, best fit and worst fit allocation policies
- understand external fragmentation
- How to coalesce, or reclaim freed memory


## Makefile

The **Makefile** is configured to build the project using `make`.

The Makefile targets include code for:
- `make`: build the project which can be run by default with **./main**
- `make test`: build the tests, which can be run by default with **./test**
- `make format`: format *.h and *.cpp using `clang-format`
- `make valgrind`: run valgrind against **main** to check for memory issues
- `make clean`: remove all .o files, **main** and **test**

## Tests

Tests are configured using [libgtest](https://github.com/google/googletest).

The **Makefile** is configured to build the tests using `make test`.
Run the tests, after compiling them, with `./test`

