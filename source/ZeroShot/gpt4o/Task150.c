#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} SinglyLinkedList;

SinglyLinkedList* createList() {
    SinglyLinkedList* list = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    list->head = NULL;
    return list;
}

void insert(SinglyLinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool deleteNode(SinglyLinkedList* list, int data) {
    if (list->head == NULL) return false;

    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return true;
    }

    Node* current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    if (current->next == NULL) return false;

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    return true;
}

bool search(SinglyLinkedList* list, int data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) return true;
        current = current->next;
    }
    return false;
}

int main() {
    SinglyLinkedList* list = createList();
    insert(list, 10);
    insert(list, 20);
    insert(list, 30);
    printf("%d\n", search(list, 20));  // 1 (true)
    printf("%d\n", deleteNode(list, 20));  // 1 (true)
    printf("%d\n", search(list, 20));  // 0 (false)
    insert(list, 40);
    printf("%d\n", search(list, 40));  // 1 (true)
    printf("%d\n", deleteNode(list, 50));  // 0 (false)
    
    return 0;
}