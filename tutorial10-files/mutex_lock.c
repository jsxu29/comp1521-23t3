#include <stdio.h>
#include <pthread.h>

int global_total = 0;
pthread_mutex_t global_total_lock = PTHREAD_MUTEX_INITIALIZER;

void *add_5000_to_counter(void *data) {
    for (int i = 0; i < 5000; i++) {
        // sets our global_total_lock to be locked
        // e.g. thread 1 has locked this variable
        //      thread 2 can't lock this variable, needs to wait for the variable to be unlocked, before locking it itself
        // ensures that the threads don't access the variables at the exact same time
        pthread_mutex_lock(&global_total_lock);

        // increment the global total by 1
        global_total++;

        pthread_mutex_unlock(&global_total_lock);
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
