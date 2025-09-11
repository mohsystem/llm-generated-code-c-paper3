
// Note: Thread synchronization in C requires platform-specific implementations
// Here's a simplified version using POSIX threads (pthread)\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <pthread.h>\n#include <semaphore.h>\n\n#define MAX_LENGTH 60\n\ntypedef struct {\n    sem_t hydrogen_sem;\n    sem_t oxygen_sem;\n    sem_t barrier;\n    pthread_mutex_t mutex;\n    int hydrogen_count;\n    char* result;\n    int result_index;\n} Task187;\n\nvoid task_init(Task187* task) {\n    sem_init(&task->hydrogen_sem, 0, 2);\n    sem_init(&task->oxygen_sem, 0, 1);\n    sem_init(&task->barrier, 0, 0);\n    pthread_mutex_init(&task->mutex, NULL);\n    task->hydrogen_count = 0;\n    task->result = (char*)malloc(MAX_LENGTH);\n    task->result_index = 0;\n}\n\nvoid task_destroy(Task187* task) {\n    sem_destroy(&task->hydrogen_sem);\n    sem_destroy(&task->oxygen_sem);\n    sem_destroy(&task->barrier);\n    pthread_mutex_destroy(&task->mutex);\n    free(task->result);\n}\n\nvoid* hydrogen(void* arg) {\n    Task187* task = (Task187*)arg;\n    \n    sem_wait(&task->hydrogen_sem);\n    pthread_mutex_lock(&task->mutex);\n    task->result[task->result_index++] = 'H';\n    task->hydrogen_count++;\n    \n    if (task->hydrogen_count == 2) {\n        task->hydrogen_count = 0;\n        sem_post(&task->barrier);\n    }\n    pthread_mutex_unlock(&task->mutex);\n    \n    sem_wait(&task->barrier);\n    sem_post(&task->hydrogen_sem);\n    \n    return NULL;\n}\n\nvoid* oxygen(void* arg) {\n    Task187* task = (Task187*)arg;\n    \n    sem_wait(&task->oxygen_sem);\n    pthread_mutex_lock(&task->mutex);\n    task->result[task->result_index++] = 'O';\n    pthread_mutex_unlock(&task->mutex);\n    \n    sem_post(&task->barrier);\n    sem_wait(&task->barrier);\n    sem_post(&task->oxygen_sem);\n    \n    return NULL;\n}\n\nchar* buildWater(const char* water) {\n    Task187 task;\n    task_init(&task);\n    \n    int len = strlen(water);\n    pthread_t threads[MAX_LENGTH];\n    int thread_count = 0;\n    \n    for (int i = 0; i < len; i++) {\n        if (water[i] == 'H') {\n            pthread_create(&threads[thread_count++], NULL, hydrogen, &task);\n        } else {\n            pthread_create(&threads[thread_count++], NULL, oxygen, &task);\n        }\n    }\n    \n    for (int i = 0; i < thread_count; i++) {\n        pthread_join(threads[i], NULL);\n    }\n    \n    task.result[task.result_index] = '\\0';
    char* result = strdup(task.result);
    task_destroy(&task);
    return result;
}

int main() {
    const char* test_cases[] = {"HOH", "OOHHHH", "HOHHHO", "OHHHHO", "HHOHOH"};
    int num_tests = 5;
    
    for (int i = 0; i < num_tests; i++) {
        printf("Input: %s\\n", test_cases[i]);
        char* result = buildWater(test_cases[i]);
        printf("Output: %s\\n\\n", result);
        free(result);
    }
    
    return 0;
}
