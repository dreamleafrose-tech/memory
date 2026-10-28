
1. track free space
     - determine how to do this
          - a pointer
          - a free list structure of some kind?
2. determine an allocation strategy for multiple processes / items
3. make allocations for strings instead of processes for now
4. update load/store in memory for strings
5. pass through load/store in mmu for strings and single byte/char
6. update memory bounds check to handle multi-byte writes and reads
7. convenience - dump() memory
8. determine if we're comfortable with process structs free in the main()
     or if we want to manage them some other way

Nate will add dump(), clear(), and size() to Memory