#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int key;
    struct Node* next;
};

struct Node* createNode(int key) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

struct Node* table[SIZE];

int hash(int key) {
    return key % SIZE;
}

void insert(int key) {
    int hashIndex = hash(key);
    struct Node* newNode = createNode(key);
    newNode->next = table[hashIndex];
    table[hashIndex] = newNode;
}

void deleteKey(int key) {
    int hashIndex = hash(key);
    struct Node* temp = table[hashIndex];
    struct Node* prev = NULL;

    if (temp != NULL && temp->key == key) {
        table[hashIndex] = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

int search(int key) {
    int hashIndex = hash(key);
    struct Node* temp = table[hashIndex];

    while (temp != NULL) {
        if (temp->key == key)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int main() {
    for (int i = 0; i < SIZE; i++)
        table[i] = NULL;

    insert(10);
    insert(20);
    insert(30);
    printf("%d\n", search(20));
    deleteKey(20);
    printf("%d\n", search(20));

    return 0;
}