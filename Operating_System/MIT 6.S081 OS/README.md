Two file descriptors share an offset if they were derived from the same original file descriptor by a sequence of fork and dup calls. Otherwise file descriptors do not share offsets, even if they resulted from open calls for the same file.



A file’s name is distinct from the file itself; the same underlying file, called an *inode*, can have multiple names, called *links*.

