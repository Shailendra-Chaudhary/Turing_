#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared_variable = 0;

void *increment_thread(void *arg) {
    for (int i = 0; i < 100000; i++) {
        shared_variable++;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int rc;

    // Create two threads
    rc = pthread_create(&thread1, NULL, increment_thread, NULL);
    if (rc != 0) {
        fprintf(stderr, "Error creating thread: %s\n", strerror(rc));
        return 1;
    }

    rc = pthread_create(&thread2, NULL, increment_thread, NULL);
    if (rc != 0) {
        fprintf(stderr, "Error creating thread: %s\n", strerror(rc));
        pthread_cancel(thread1);
        return 1;
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Output final shared variable value
    printf("Final shared variable value: %d\n", shared_variable);

    return 0;
}
