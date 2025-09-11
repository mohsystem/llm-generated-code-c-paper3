#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* insertAtHead(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

Node* insertAtEnd(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

bool search(Node* head, int data) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) return true;
        temp = temp->next;
    }
    return false;
}

Node* deleteNode(Node* head, int data) {
    if (head == NULL) return NULL;

    if (head->data == data) {
        return head->next;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        if (temp->next->data == data) {
            temp->next = temp->next->next;
            return head;
        }
        temp = temp->next;
    }
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void mainFunction() {
    Node* head = NULL;

    // Insert operations
    head = insertAtHead(head, 1);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 3);
    head = insertAtEnd(head, 4);
    head = insertAtEnd(head, 5);

    // Print linked list
    printf("Linked List: ");
    printList(head);

    // Search operation
    printf("Is 3 in the list? %s\n", search(head, 3) ? "True" : "False");

    // Delete operation
    head = deleteNode(head, 3);

    // Print linked list after deletion
    printf("Linked List after deletion: ");
    printList(head);
}

int main() {
    mainFunction();
    return 0;
}