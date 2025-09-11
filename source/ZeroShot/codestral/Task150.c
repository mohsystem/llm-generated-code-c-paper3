#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Task150 {
    Node* head;
} Task150;

void insert(Task150* list, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node* last = list->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = node;
    }
}

void deleteNode(Task150* list, int data) {
    Node* temp = list->head;
    Node* prev = NULL;
    if (temp != NULL && temp->data == data) {
        list->head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

int search(Task150* list, int data) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (temp->data == data)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int main() {
    Task150 list = {NULL};
    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    printf("%d\n", search(&list, 2));
    deleteNode(&list, 2);
    printf("%d\n", search(&list, 2));
    return 0;
}