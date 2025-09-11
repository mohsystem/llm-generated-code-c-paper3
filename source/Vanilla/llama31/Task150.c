#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert at the beginning
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    newNode->next = head;
    return newNode;
}

// Function to insert at the end
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    Node* last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    return head;
}

// Function to delete a node
Node* deleteNode(Node* head, int key) {
    if (head == NULL) return NULL;
    if (head->data == key) {
        return head->next;
    }
    Node* current = head;
    while (current->next != NULL && current->next->data != key) {
        current = current->next;
    }
    if (current->next != NULL) {
        current->next = current->next->next;
    }
    return head;
}

// Function to search for a node
int searchNode(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Function to print the list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;

    // Test cases
    head = insertAtEnd(head, 2);
    head = insertAtEnd(head, 3);
    head = insertAtEnd(head, 5);
    head = insertAtEnd(head, 7);

    printf("Created Linked List: \n");
    printList(head);

    head = insertAtBeginning(head, 1);
    printf("Linked List after insertion at beginning: \n");
    printList(head);

    head = deleteNode(head, 3);
    printf("Linked List after deletion of 3: \n");
    printList(head);

    printf("Is 5 in the list? %s\n", searchNode(head, 5) ? "True" : "False");
    printf("Is 3 in the list? %s\n", searchNode(head, 3) ? "True" : "False");

    return 0;
}