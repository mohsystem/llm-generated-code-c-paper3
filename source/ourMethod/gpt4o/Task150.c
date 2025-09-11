#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Task150;

Task150* createList() {
    Task150* list = (Task150*)malloc(sizeof(Task150));
    list->head = NULL;
    return list;
}

void insert(Task150* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (!list->head) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int deleteNode(Task150* list, int data) {
    if (!list->head) return 0;

    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return 1;
    }

    Node* current = list->head;
    while (current->next && current->next->data != data) {
        current = current->next;
    }

    if (!current->next) return 0;

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    return 1;
}

int search(Task150* list, int data) {
    Node* current = list->head;
    while (current) {
        if (current->data == data) return 1;
        current = current->next;
    }
    return 0;
}

int main() {
    Task150* list = createList();
    
    // Test cases
    insert(list, 1);
    insert(list, 2);
    insert(list, 3);
    printf("%d\n", search(list, 2)); // 1
    printf("%d\n", search(list, 4)); // 0
    printf("%d\n", deleteNode(list, 2)); // 1
    printf("%d\n", search(list, 2)); // 0
    printf("%d\n", deleteNode(list, 4)); // 0
    
    return 0;
}