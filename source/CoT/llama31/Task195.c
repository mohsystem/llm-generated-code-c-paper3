#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int size;
    int capacity;
} Task195;

Task195* Task195Create() {
    Task195* obj = (Task195*) malloc(sizeof(Task195));
    obj->arr = (int*) malloc(100000 * sizeof(int));
    obj->size = 0;
    obj->capacity = 100000;
    return obj;
}

void Task195AddNum(Task195* obj, int num) {
    obj->arr[obj->size++] = num;
    for (int i = obj->size - 1; i > 0; i--) {
        if (obj->arr[i] < obj->arr[i - 1]) {
            int temp = obj->arr[i];
            obj->arr[i] = obj->arr[i - 1];
            obj->arr[i - 1] = temp;
        } else {
            break;
        }
    }
}

double Task195FindMedian(Task195* obj) {
    int n = obj->size;
    if (n % 2 == 0) {
        return (obj->arr[n / 2 - 1] + obj->arr[n / 2]) / 2.0;
    } else {
        return (double) obj->arr[n / 2];
    }
}

void Task195Free(Task195* obj) {
    free(obj->arr);
    free(obj);
}

int main() {
    Task195* medianFinder = Task195Create();
    Task195AddNum(medianFinder, 1);
    Task195AddNum(medianFinder, 2);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 1.5
    Task195AddNum(medianFinder, 3);
    printf("%f\n", Task195FindMedian(medianFinder));  // Output: 2.0
    Task195Free(medianFinder);
    return 0;
}