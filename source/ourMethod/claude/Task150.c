
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Task150;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void init_list(Task150* list) {
    if (list != NULL) {
        list->head = NULL;
    }
}

void cleanup_list(Task150* list) {
    if (list == NULL) return;
    
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

bool insert(Task150* list, int data) {
    if (list == NULL) return false;
    
    Node* new_node = create_node(data);
    if (new_node == NULL) return false;
    
    if (list->head == NULL) {
        list->head = new_node;
        return true;
    }
    
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return true;
}

bool delete_node(Task150* list, int data) {
    if (list == NULL || list->head == NULL) return false;
    
    if (list->head->data == data) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return true;
    }
    
    Node* current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
        return true;
    }
    return false;
}

bool search(const Task150* list, int data) {
    if (list == NULL) return false;
    
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int main() {
    Task150 list;
    init_list(&list);
    
    // Test case 1: Insert elements
    insert(&list, 10);
    insert(&list, 20);
    insert(&list, 30);
    
    // Test case 2: Search existing element
    printf("Search 20: %s\\n", search(&list, 20) ? "true" : "false");
    
    // Test case 3: Search non-existing element
    printf("Search 40: %s\\n", search(&list, 40) ? "true" : "false");
    
    // Test case 4: Delete element
    printf("Delete 20: %s\\n", delete_node(&list, 20) ? "true" : "false");
    
    // Test case 5: Search deleted element
    printf("Search 20: %s\\n", search(&list, 20) ? "true" : "false");
    
    // Cleanup
    cleanup_list(&list);
    
    return 0;
}
