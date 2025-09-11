#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    char name[100];
    char email[100];
    char password[100];
} User;

typedef struct Node {
    User user;
    struct Node* next;
} Node;

Node* head = NULL;

void registerUser(const char* name, const char* email, const char* password) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->user.name, name);
    strcpy(newNode->user.email, email);
    strcpy(newNode->user.password, password);
    newNode->next = head;
    head = newNode;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        char name[100], email[100], password[100];
        printf("Enter name: ");
        scanf("%99s", name);
        printf("Enter email: ");
        scanf("%99s", email);
        printf("Enter password: ");
        scanf("%99s", password);

        registerUser(name, email, password);
    }

    // Display stored users
    Node* temp = head;
    while (temp != NULL) {
        printf("Name: %s, Email: %s, Password: %s\n", temp->user.name, temp->user.email, temp->user.password);
        temp = temp->next;
    }

    return 0;
}