
// Note: C doesn't have built-in thread support. \n// You would need to use platform-specific threading libraries like pthreads.\n// Here's a version using pthreads:

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int current_counter;
    int max_counter;
    pthread_mutex_t mutex;
} SharedResource;

void init_resource(SharedResource* resource, int max_counter) {
    resource->current_counter = 0;
    resource->max_counter = max_counter;
    pthread_mutex_init(&resource->mutex, NULL);
}

void access_resource(SharedResource* resource, const char* thread_name) {
    if (resource->current_counter <= resource->max_counter) {
        pthread_mutex_lock(&resource->mutex);
        if (resource->current_counter <= resource->max_counter) {
            resource->current_counter++;
            printf("Thread %s accessing counter: %d\\n", thread_name, resource->current_counter);
        }
        pthread_mutex_unlock(&resource->mutex);
    }
}

void* thread_function(void* arg) {
    SharedResource* resource = ((void**)arg)[0];
    char* thread_name = ((void**)arg)[1];
    access_resource(resource, thread_name);
    return NULL;
}

int main() {
    SharedResource resource1, resource2, resource3, resource4, resource5;
    pthread_t threads[5];
    void* args[5][2];
    char thread_names[5][3] = {"T0", "T1", "T2", "T3", "T4"};

    // Test case 1: Single thread
    init_resource(&resource1, 10);
    args[0][0] = &resource1;
    args[0][1] = thread_names[0];
    pthread_create(&threads[0], NULL, thread_function, args[0]);
    pthread_join(threads[0], NULL);

    // Test case 2: Multiple threads accessing simultaneously
    init_resource(&resource2, 10);
    for(int i = 0; i < 5; i++) {
        args[i][0] = &resource2;
        args[i][1] = thread_names[i];
        pthread_create(&threads[i], NULL, thread_function, args[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Test case 3: Thread accessing after max limit
    init_resource(&resource3, 2);
    for(int i = 0; i < 5; i++) {
        args[i][0] = &resource3;
        args[i][1] = thread_names[i];
        pthread_create(&threads[i], NULL, thread_function, args[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Test case 4: Multiple threads with sleep
    init_resource(&resource4, 5);
    void* sleep_thread(void* arg) {
        usleep(100000);  // 100ms
        return thread_function(arg);
    }
    for(int i = 0; i < 3; i++) {
        args[i][0] = &resource4;
        args[i][1] = thread_names[i];
        pthread_create(&threads[i], NULL, sleep_thread, args[i]);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Test case 5: Single thread multiple access
    init_resource(&resource5, 3);
    void* multiple_access(void* arg) {
        for(int i = 0; i < 4; i++) {
            access_resource(&resource5, "T5");
        }
        return NULL;
    }
    pthread_create(&threads[0], NULL, multiple_access, NULL);
    pthread_join(threads[0], NULL);

    return 0;
}
