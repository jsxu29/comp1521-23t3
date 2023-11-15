// Write a C program that creates a thread that infinitely prints some message provided by main
// (eg. "Hello\n"), while the main (default) thread infinitely prints a different message
// (eg. "there!\n").

#include <stdio.h>
#include <pthread.h>

void *func(void *arg) {
    while (1) {
        printf("there!\n");
    }
    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &func, NULL);

    // while (1) {
    //     printf("Hello\n");
    // }

    // waits for our thread that prints "there!\n" to terminate before terminating our program
    pthread_join(thread_id, NULL);
    return 0;
}