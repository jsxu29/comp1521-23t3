# Threads and Processes

Parallelism vs Concurrency

## Parallelism
- code that runs at the same time
- how is this possible? (because our computers can have multiple processors)

## Concurrency
- not necessarily at the same time

## Processes
- An instance of a program running on the computer
- Use posix_spawn to create a process

```
int posix_spawn(pid_t *restrict pid,
        const char *restrict path,
        const posix_spawn_file_actions_t *file_actions,
        const posix_spawnattr_t *restrict attrp,
        char *const argv[restrict],
        char *const envp[restrict]);
```

> pid_t *restrict pid - process id number

> const char *restrict path - path of the executable that we want to run

> const posix_spawn_file_actions_t *file_actions - usually NULL

> const posix_spawnattr_t *restrict attrp - usually NULL

> char *const argv[restrict] - array of command line arguments for the executable, last argument should be NULL to signify the end (like null terminators in strings)

> char *const envp[restrict] - environment variable

- posix_spawn - requires the full path name of the executable
    - int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
- posix_spawnp - same thing but searchs for the executable
- Use waitpid to wait for the process to terminate and return a status value

## Threads
- A lightweight flow of control (runs code)
- #include <pthread.h>
- Like processes, use pthread_create to create a thread

```
int pthread_create(pthread_t *thread,
        const pthread_attr_t *attr,
        void *(*start_routine)(void *),
        void *arg)
```

> pthread_t *thread - used to store the ID of the created thread

> const pthread_attr_t *attr - attributes (NULL for no attributes)

> void *(*start_routine)(void *) - function pointer \
> void * - can be type casted to a type

> void *arg - argument passed to start routine

- pthread_create
    - takes in a function pointer (void *(*start_routine)(void *))
    - function return type (void *) // pointer to function (*start_routine) // function argument (void *)
- Always error check
- Use pthread_join to wait for a thread to terminate

### Process vs Threads
- Processes can be executed by one or many threads
- Processes can be run by multiple threads (helps us achieve parallelism/concurrency)
- You can have multiple threads that share the same memory and file descriptors etc


## Errors - Data Race

Consider C operations in MIPS.

### Atomic types
- atomic - smallest possible unit
- #include <stdatomic.h>
- don't need to keep in mind locks yourselves
- issues: only specific atomic operations allowed (i.e. only the smallest possible operations are allowed)

### Mutex locks
- create pthread_mutex_t objects that are specified to be locked or unlocked - if it is locked, can not be accessed in another thread
- create a mutex lock object - phread_mutex_t <lock_variable_name> = PTHREAD_MUTEX_INITIALIZER
- manipulate this lock object by locking and unlocking it - pthread_mutex_lock(&<lock_variable_name>) and pthread_mutex_unlock(&<lock_variable_name>)

- potential issues: deadlock - multiple threads enter a waiting state because the resource/mutex lock is held by another waiting process
    - i.e. A waits on B and B waits on A :>
