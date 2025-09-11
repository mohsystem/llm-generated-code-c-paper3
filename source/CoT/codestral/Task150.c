#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// LinkedList structure
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

// Function to insert a new node at the beginning
void insert(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

// Function to delete a node with given key
void deleteNode(LinkedList* list, int key) {
    Node* temp = list->head, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        list->head = temp->next;
        free(temp);
        return;
    }

    // Search for the key to be deleted
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;
    free(temp);
}

// Function to search a node with given key
bool search(LinkedList* list, int key) {
    Node* temp = list->head;
    while (temp != NULL) {
        if (temp->data == key)
            return true;
        temp = temp->next;
    }
    return false;
}

// Utility function to print the linked list
void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

// Main function for testing
int main() {
    LinkedList llist = {NULL};

    insert(&llist, 1);
    insert(&llist, 2);
    insert(&llist, 3);

    printf("Linked List:\n");
    printList(&llist);

    printf("\nSearch for 2: %s\n", search(&llist, 2) ? "true" : "false");

    deleteNode(&llist, 2);
    printf("\nLinked List after deleting 2:\n");
    printList(&llist);

    return 0;
}