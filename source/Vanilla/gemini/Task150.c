#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Task150;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(Task150* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void deleteNode(Task150* list, int data) {
    if (list->head == NULL) {
        return;
    }
    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }
    Node* current = list->head;
    Node* prev = NULL;
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

bool search(Task150* list, int data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int main() {
    Task150 list;
    list.head = NULL;

    insert(&list, 10);
    insert(&list, 20);
    insert(&list, 30);
    printf("%s\n", search(&list, 20) ? "true" : "false"); // true
    deleteNode(&list, 20);
    printf("%s\n", search(&list, 20) ? "true" : "false"); // false
    printf("%s\n", search(&list, 10) ? "true" : "false"); // true
    deleteNode(&list, 10);
    printf("%s\n", search(&list, 10) ? "true" : "false"); // false
    insert(&list, 40);
    printf("%s\n", search(&list, 40) ? "true" : "false"); // true
    deleteNode(&list, 30);
    printf("%s\n", search(&list, 30) ? "true" : "false"); // false

    return 0;
}