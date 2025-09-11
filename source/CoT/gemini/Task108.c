#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include necessary headers for RPC (e.g., gRPC, Thrift) if using a specific framework.
// This example demonstrates a basic concept and would require an RPC framework for real-world use.

// Placeholder structure for storing object information (replace with appropriate data structures for your objects).
typedef struct {
    char name[256];
    void* data;
    size_t size;
} ObjectInfo;


// Placeholder for RPC service implementation (replace with actual RPC framework code)
ObjectInfo* objects[100];  // A simple array to store objects (replace with a more robust data structure)
int objectCount = 0;

ObjectInfo* getObject(const char* name) {
    for (int i = 0; i < objectCount; i++) {
        if (strcmp(objects[i]->name, name) == 0) {
            return objects[i];
        }
    }
    return NULL;
}

void setObject(const char* name, void* data, size_t size) {
    ObjectInfo* obj = (ObjectInfo*)malloc(sizeof(ObjectInfo));
    strcpy(obj->name, name);
    obj->data = malloc(size);  // Allocate memory for the object data
    memcpy(obj->data, data, size);  // Copy the object data
    obj->size = size;
    objects[objectCount++] = obj;
}



int main() {

    int x = 10;
    setObject("test1", &x, sizeof(int));
    ObjectInfo* retrievedX = getObject("test1");
    if (retrievedX) {
        printf("%d\n", *(int*)retrievedX->data); // Output: 10
    }


    double y[3] = {1.1, 2.2, 3.3};
    setObject("test2", y, sizeof(y));
    ObjectInfo * retrievedY = getObject("test2");
    if (retrievedY)
    {
        for (int i=0; i<3; i++)
            printf("%f ", ((double *)retrievedY->data)[i]);
        printf("\n");
    }



    // Free allocated memory when done
    for (int i = 0; i < objectCount; i++) {
        free(objects[i]->data);
        free(objects[i]);
    }


    return 0;
}