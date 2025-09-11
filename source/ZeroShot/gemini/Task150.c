#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

void insert(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void delete(int data) {
    if (head == NULL) {
        return;
    }
    if (head->data == data) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return;
    }
    struct Node* current = head;
    struct Node* prev = NULL;
    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return;
    }
    prev->next = current->next;
    free(current);
}

bool search(int data) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int main() {
    insert(10);
    insert(20);
    insert(30);
    printf("%d\n", search(20)); // 1 (true)
    printf("%d\n", search(40)); // 0 (false)
    delete(20);
    printf("%d\n", search(20)); // 0 (false)
    insert(40);
    delete(10);
    printf("%d\n", search(10)); // 0 (false)
    printf("%d\n", search(40)); // 1 (true)
    return 0;
}