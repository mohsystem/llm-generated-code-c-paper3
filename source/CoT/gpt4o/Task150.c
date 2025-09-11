#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct SinglyLinkedList {
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

int deleteNode(SinglyLinkedList* list, int data) {
    if (list->head == NULL) return 0;
    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return 1;
    }
    Node* current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    if (current->next == NULL) return 0;
    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    return 1;
}

int search(SinglyLinkedList* list, int data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int main() {
    SinglyLinkedList* list = createList();

    insert(list, 10);
    insert(list, 20);
    insert(list, 30);
    insert(list, 40);
    insert(list, 50);

    printf("%d\n", search(list, 30)); // 1
    printf("%d\n", deleteNode(list, 20)); // 1
    printf("%d\n", search(list, 20)); // 0
    printf("%d\n", search(list, 10)); // 1
    printf("%d\n", deleteNode(list, 50)); // 1

    return 0;
}