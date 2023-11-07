# FILES

## File Systems

Directories/Folders and Files

![Alt text](image.png)

a) full pathname of the web directory -> /home/cs1521/web
b) ~jas/../..
~jas - /home/jas
~jas/../.. -> root or /
c) link to parent directory -> ..
d) cat -> file

### Useful Commands
- cd .. moves the directory back by one directory, i.e., go to the parent directory
  - link to parent directory is stored as ..
- cd ~ to get to the root home directory
  - ~ is the shorthand for the HOME directory pathname

### Symbolic Links
A special kind of file that simply contains the name of another file. They allow arbitrary links between filesystem objects.


## Files in C
FILE * - file pointer is a typedef'd structure used by the standard io library to hold the appropriate data for use of fopen, and its family of functions.

Main items it contains:
- the file contents
- the position up to in the file

- typedef: a keyword used to provide existing data types with a new name
> e.g. \
> typedef struct students { \
> &nbsp; &nbsp; char name[50]; \
> &nbsp; &nbsp; char branch[50]; \
> &nbsp; &nbsp; int ID_no; \
> } stu;

### File functions
Most need "#include <stdio.h>".

- FILE *fopen(path, mode)
  - modes:
    - "r" - read
    - "w" - write
    - "a" - append
    - "r+", "w+", "a+"
  - special cases
    - NULL is returned and errno is set to indicate the error
    - Reasons:
      - If the file you tried to open for reading does not exist.
      - If you try to open a file you do not have permission to access.
      - If the "mode" string was invalid.
      - If the system is out of memory.
      - If you try to create a file and your quota of disk blocks or inodes has been exhausted.
      - If the pathname was too long.
      - Etc...

FILE *file = fopen("test.txt", "r"); \
if (file == NULL) // if there is an error, do some error handling

- fclose
- fseek
- fprintf - more general version of printf
- fgetc
- fgets

## Streams
- stdin
- stdout
- they are FILE * objects

### Stream and File Functions
- fprintf -> printf
- fgetc -> getc
- fputc -> putc



## Syscalls
- make direct requests to our operating system
- like MIPS syscalls

li $v0, 1 \
li $a0, 2 \
syscall

C is similar: like parsing in $v0 and $a0 as function arguments \
syscall(... 1, ... 2)

### Syscall wrapper functions
- fseek - FILE *file version instead of int fd
- lseek

off_t lseek(int fd, off_t offset, int whence); \
options for whence:
  - SEEK_SET - go to offset number of bytes from the start
  - SEEK_CUR - go to offset number of bytes from your current position
  - SEEK_END - go to offset number of bytes from the end of your file

how do you get the file descriptor fd? can you pass in any int?
- open("test.txt", "r") -> int fd - index to an entry, don't need to know too much but passing around fd can be used for other file functions that use an integer (i.e. lseek)
- find out more here: https://www.man7.org/linux/man-pages/man2/open.2.html

1.  
    1.  lseek(fd, 0, SEEK_END) - offset 10,000
    2.  lseek(fd, -1000, SEEK_CUR) - offset 10,000 - 1,000 = 9,000
    3.  lseek(fd, 0, SEEK_SET) - offset 0
    4.  lseek(fd, -100, SEEK_SET) - ERROR returns -1
    5.  lseek(fd, 1000, SEEK_SET) - offset 1000
    6.  lseek(fd, 1000, SEEK_CUR) - offset 2000
