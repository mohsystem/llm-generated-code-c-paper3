#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *next;
};


struct Node *head = NULL;


void insert(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}


void delete(int data) {
    if (head == NULL) {
        return;
    }


    if (head->data == data) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }


    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

bool search(int data) {
    struct Node *temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}


void printList() {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {

    // Test cases
    insert(10);
    insert(20);
    insert(30);
    printList(); // Output: 10 20 30

    delete (20);
    printList(); // Output: 10 30

    printf("%s\n", search(30) ? "true" : "false"); // Output: true
    printf("%s\n", search(20) ? "true" : "false"); // Output: false

    delete (10);
    printList(); // Output: 30


    insert(40);
    insert(50);
    printList(); // Output: 30 40 50

    return 0;
}