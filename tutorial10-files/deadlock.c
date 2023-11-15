#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

// thread 1 locks lock1 (pthread_mutex_lock(&lock1);)
// thread 2 locks lock2 (pthread_mutex_lock(&lock2);)

// thread 1 wants to lock lock2 but it can not as it is already locked by thread 2
// thread 2 wants to lock lock1 but it can not as it is already locked by thread 1

// deadlock... multiple threads enter a waiting state because the resource/mutex lock is held by another waiting process
// thread 1 waits on thread 2, and thread 2 waits on thread 1

void *func1(void *data) {
    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);
    // body
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    return NULL;
}

void *func2(void *data) {
    pthread_mutex_lock(&lock2);
    pthread_mutex_lock(&lock1);
    // body
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    return NULL;
}

int main(void) {
    pthread_t thread1;
    pthread_create(&thread1, NULL, func1, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, func2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}
