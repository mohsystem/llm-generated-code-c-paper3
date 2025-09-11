#include <stdio.h>
#include <stdlib.h>

// Node structure to represent a node of the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Linked list structure
typedef struct LinkedList {
    Node* head;
} LinkedList;

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

// Function to insert at the beginning of the linked list
void insertAtHead(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }
}

// Function to insert at the end of the linked list
void insertAtEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node* lastNode = list->head;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
}

// Function to delete a node with the given data
void deleteNode(LinkedList* list, int data) {
    if (list->head == NULL) return;

    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    Node* current = list->head;
    while (current->next != NULL) {
        if (current->next->data == data) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

// Function to search for a node with the given data
int searchNode(LinkedList* list, int data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Function to print the linked list
void printList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    LinkedList list;
    list.head = NULL;

    // Test cases
    insertAtHead(&list, 1);
    insertAtHead(&list, 2);
    insertAtEnd(&list, 3);
    insertAtEnd(&list, 4);

    printf("Linked List: ");
    printList(&list);

    printf("Search for 2: %s\n", searchNode(&list, 2) ? "True" : "False");
    printf("Search for 5: %s\n", searchNode(&list, 5) ? "True" : "False");

    deleteNode(&list, 2);
    printf("After deleting 2: ");
    printList(&list);

    return 0;
}