#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    int age;
} UserData;

void deserialize(const char* data, UserData* userData) {
    sscanf(data, "%99s %d", userData->name, &userData->age);
}

void serialize(const UserData* userData, char* buffer) {
    sprintf(buffer, "%s %d", userData->name, userData->age);
}

int main() {
    // Test cases
    const int bufferSize = 100;
    char buffer[bufferSize];

    UserData testData1 = {"John Doe", 30};
    serialize(&testData1, buffer);
    UserData deserializedData1;
    deserialize(buffer, &deserializedData1);
    printf("Deserialized Data 1: %s, %d\n", deserializedData1.name, deserializedData1.age);

    UserData testData2 = {"Jane Doe", 25};
    serialize(&testData2, buffer);
    UserData deserializedData2;
    deserialize(buffer, &deserializedData2);
    printf("Deserialized Data 2: %s, %d\n", deserializedData2.name, deserializedData2.age);

    UserData testData3 = {"Bob Smith", 40};
    serialize(&testData3, buffer);
    UserData deserializedData3;
    deserialize(buffer, &deserializedData3);
    printf("Deserialized Data 3: %s, %d\n", deserializedData3.name, deserializedData3.age);

    UserData testData4 = {"Alice Johnson", 35};
    serialize(&testData4, buffer);
    UserData deserializedData4;
    deserialize(buffer, &deserializedData4);
    printf("Deserialized Data 4: %s, %d\n", deserializedData4.name, deserializedData4.age);

    UserData testData5 = {"Mike Brown", 20};
    serialize(&testData5, buffer);
    UserData deserializedData5;
    deserialize(buffer, &deserializedData5);
    printf("Deserialized Data 5: %s, %d\n", deserializedData5.name, deserializedData5.age);

    return 0;
}