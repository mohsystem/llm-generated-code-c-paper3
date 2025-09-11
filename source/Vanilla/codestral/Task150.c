#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

void insert(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (head == NULL) {
        head = node;
    } else {
        Node* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = node;
    }
}

void deleteNode(int key) {
    Node* temp = head;
    Node* prev = NULL;
    if (temp != NULL && temp->data == key) {
        head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

int search(int key) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == key)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int main() {
    insert(1);
    insert(2);
    insert(3);
    printf("%d\n", search(2)); // 1
    deleteNode(2);
    printf("%d\n", search(2)); // 0
    return 0;
}