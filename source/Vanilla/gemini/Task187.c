#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int h_count;
    int o_count;
    char molecule[42]; // Maximum length for the constraints + null terminator
    int molecule_len;
} H2O;

void* releaseHydrogen(void* arg) {
    H2O* h2o = (H2O*)arg;

    pthread_mutex_lock(&h2o->mutex);
    h2o->h_count++;
    pthread_cond_broadcast(&h2o->cond);

    while (h2o->h_count < 2 || h2o->o_count < 1) {
        pthread_cond_wait(&h2o->cond, &h2o->mutex);
    }

    h2o->molecule[h2o->molecule_len++] = 'H';
    h2o->h_count -= 2;
    h2o->o_count--;
    pthread_cond_broadcast(&h2o->cond);
    pthread_mutex_unlock(&h2o->mutex);

    return NULL;
}

void* releaseOxygen(void* arg) {
    H2O* h2o = (H2O*)arg;

    pthread_mutex_lock(&h2o->mutex);
    h2o->o_count++;
    pthread_cond_broadcast(&h2o->cond);
    
    while (h2o->h_count < 2 || h2o->o_count < 1) {
        pthread_cond_wait(&h2o->cond, &h2o->mutex);
    }

    h2o->molecule[h2o->molecule_len++] = 'O';
    h2o->h_count -= 2;
    h2o->o_count--;
    pthread_cond_broadcast(&h2o->cond);
    pthread_mutex_unlock(&h2o->mutex);
    
    return NULL;
}

char* getMolecule(H2O* h2o) {
    char* result = (char*)malloc(sizeof(char) * (h2o->molecule_len + 1));
    strcpy(result, h2o->molecule);
    result[h2o->molecule_len] = '\0';
    h2o->molecule_len = 0;
    return result;
}


int main() {
    char* inputs[] = {"HOH", "OOHHHH", "HOHHOH", "OHH", "HHHHOO"};
    char* expectedOutputs[] = {"HHO", "HHOHHO", "HHOHHO", "HHO", "HHHOHO"};
    int num_tests = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_tests; i++) {
        H2O h2o;
        pthread_mutex_init(&h2o.mutex, NULL);
        pthread_cond_init(&h2o.cond, NULL);
        h2o.h_count = 0;
        h2o.o_count = 0;
        h2o.molecule_len = 0;

        pthread_t threads[strlen(inputs[i])];
        for (int j = 0; j < strlen(inputs[i]); j++) {
            if (inputs[i][j] == 'H') {
                pthread_create(&threads[j], NULL, releaseHydrogen, &h2o);
            } else {
                pthread_create(&threads[j], NULL, releaseOxygen, &h2o);
            }
        }

        for (int j = 0; j < strlen(inputs[i]); j++) {
            pthread_join(&threads[j], NULL);
        }

        char* actualOutput = getMolecule(&h2o);
        printf("Input: %s, Expected: %s, Actual: %s\n", inputs[i], expectedOutputs[i], actualOutput);

         // Clean up allocated memory
        free(actualOutput);
        pthread_mutex_destroy(&h2o.mutex);
        pthread_cond_destroy(&h2o.cond);

    }

    return 0;
}