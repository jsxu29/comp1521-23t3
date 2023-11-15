#include <stdio.h>
#include <pthread.h>

int global_total = 0;

void *add_5000_to_counter(void *data) {
    for (int i = 0; i < 5000; i++) {
        // sleep for 1 nanosecond
        nanosleep (&(struct timespec){.tv_nsec = 1}, NULL);

        // increment the global total by 1
        global_total++;
        // global_total = global_total + 1;
        // this is performed in 3 steps:
        // 1. Load the global_total into a register
        // 2. Increment the value in the register
        // 3. Store the new value back into the global_total

        // data race issues - both threads are incrementing at the exact same time, so rather than incrementing global total twice, we only increment it once
        // 1.1. access global_total - 900
        // 2.2. add 1 to global_total - 901
        // 1.2. add 1 to global_total - 900 + 1 = 901
        // 1.3. save this number back to global_total - 901
        // 2.3. save this number back to global_total - 901

        // we can solve this using atomic types or mutex locks
    }

    return NULL;
}

int main(void) {
    pthread_t thread1;
    pthread_create(&thread1, NULL, add_5000_to_counter, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, add_5000_to_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // if program works correctly, should print 10000
    printf("Final total: %d\n", global_total);
}
