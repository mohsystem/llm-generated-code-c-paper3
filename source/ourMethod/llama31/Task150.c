#include <stdio.h>
#include <stdlib.h>

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

// Function to insert at the beginning
void insertAtBeginning(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }
}

// Function to insert at the end
void insertAtEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* last = list->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
}

// Function to delete a node
void deleteNode(LinkedList* list, int key) {
    if (list->head == NULL) return;

    if (list->head->data == key) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    Node* current = list->head;
    while (current->next != NULL) {
        if (current->next->data == key) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

// Function to search for a node
int searchNode(LinkedList* list, int key) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == key) {
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
    insertAtBeginning(&list, 10);
    insertAtBeginning(&list, 20);
    insertAtEnd(&list, 30);
    insertAtEnd(&list, 40);

    printf("Linked List: ");
    printList(&list);

    printf("Search for 20: %d\n", searchNode(&list, 20));
    printf("Search for 50: %d\n", searchNode(&list, 50));

    deleteNode(&list, 20);

    printf("Linked List after deletion: ");
    printList(&list);

    return 0;
}