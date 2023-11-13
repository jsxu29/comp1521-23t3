# Files Continued

### Notes
> ~ - pwd

> $HOME - environment variable that stores the pathname of the HOME directory that contains the files of the user (defined automatically when the user is created)

> sprintf - writes to a string variable \
> snprintf - also has an additional argument to specify the max number of bytes written to the buffer variable

## Stat

Stat contains information about your file (or metadata). 

The relevant components of stat are here:
```
struct stat {
    ino_t st_ino;         /* inode number */
    mode_t st_mode;       /* protection */
    uid_t st_uid;         /* user ID of owner */
    gid_t st_gid;         /* group ID of owner */
    off_t st_size;        /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for filesystem I/O */
    blkcnt_t st_blocks;   /* number of 512B blocks allocated */
    time_t st_atime;      /* time of last access */
    time_t st_mtime;      /* time of last modification */
    time_t st_ctime;      /* time of last status change */
};
```

Here is the full list of components of stat:

```
struct stat {
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */ 
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */ 
    uid_t     st_uid;     /* user ID of owner */ 
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file, that this inode represents) */
    off_t     st_size;    /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for file system I/O */
    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
    time_t    st_atime;   /* time of last access */
    time_t    st_mtime;   /* time of last modification */
    time_t    st_ctime;   /* time of last status change */
};
```

### How to use it?

The stat function takes in a file name and the struct stat variable you want to store the metadata in; it returns 0 upon success, and -1 on error.

```
struct stat s;
if (stat(<file path name>, &s) != 0) {
    ...
}
```

### Modes

mode_t mode = s.mode;

```
is directory?   user permissions    group permissions   other permissions
d               rwx                 rwx                 rwx
-               ---                 ---                 ---
```

Executing:
- executing a file: running the file
- executing a directory: can you enter it

Representation:
- each permission has two possibilities (r or -, w or -, x or -)
- binary! each permission can be represented by a 0 or 1 bit
- each permission rwx group can be represented with an octal number

E.g.
```
                           rw-r--r--
mode_t mode = 0b .....     110100100
                           000000100
```

- i.e. the other permissions read bit is represented by (mode & (1 << 2)) >> 2

- note: the way to represent whether it is a directory or not is different and you can find this out using the functions defined in the library below

### Useful stat constants

> S_ISREG(mode_t m) - returns is it a regular file? \
> S_ISDIR(mode_t m) - returns directory?

https://manpages.org/stat/2

Note from Andrew Serb: slide 53 of lectures goes through the constants for permissions e.g. S_IWOTH

### Chmod function

chmod - change mode
