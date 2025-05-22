Two file descriptors share an offset if they were derived from the same original file descriptor by a sequence of fork and dup calls. Otherwise file descriptors do not share offsets, even if they resulted from open calls for the same file.

If no data is available, a read on a pipe waits for either data to be written or for all file descriptors referring to the write end to be closed; in the latter case, read will return 0, just as if the end of a data file had been reached. p[1] is write, p[0] is read. 


### Page tables
The central data structure is `pagetable_t`, which is really a pointer to a RISC-V root page-table age; a `pagetable_t` may be either the kernel page table, or one of the per-process page tables.


### Locking
 `__sync_synchronize()` is a **memory barrier**: it tells the compiler and CPU to not reorder loads or stores across the barrier.