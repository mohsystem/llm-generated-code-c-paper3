#include <stdio.h>
#include <stdlib.h>

// Structure to hold a list element
typedef struct ListElement {
    int value;
    char isString;
    char* strValue;
    struct ListElement* next;
} ListElement;

// Function to create a new list element
ListElement* createListElement(int value, char isString, char* strValue) {
    ListElement* element = (ListElement*) malloc(sizeof(ListElement));
    element->value = value;
    element->isString = isString;
    element->strValue = strValue;
    element->next = NULL;
    return element;
}

// Function to filter out strings from the list
ListElement* filterList(ListElement* head) {
    ListElement* current = head;
    ListElement* resultHead = NULL;
    ListElement* resultTail = NULL;

    while (current != NULL) {
        if (!current->isString) {
            if (resultHead == NULL) {
                resultHead = current;
                resultTail = resultHead;
            } else {
                resultTail->next = current;
                resultTail = resultTail->next;
            }
        }
        current = current->next;
    }

    // Set next of last element to NULL
    if (resultTail != NULL) {
        resultTail->next = NULL;
    }

    return resultHead;
}

// Function to print the list
void printList(ListElement* head) {
    while (head != NULL) {
        if (!head->isString) {
            printf("%d ", head->value);
        }
        head = head->next;
    }
    printf("\n");
}

int main() {
    // Create test lists
    ListElement* list1 = createListElement(1, 0, NULL);
    list1->next = createListElement(2, 0, NULL);
    list1->next->next = createListElement(0, 1, "a");
    list1->next->next->next = createListElement(0, 1, "b");

    ListElement* list2 = createListElement(1, 0, NULL);
    list2->next = createListElement(0, 1, "a");
    list2->next->next = createListElement(0, 1, "b");
    list2->next->next->next = createListElement(0, 0, NULL);
    list2->next->next->next->value = 0;
    list2->next->next->next->next = createListElement(15, 0, NULL);

    ListElement* list3 = createListElement(1, 0, NULL);
    list3->next = createListElement(2, 0, NULL);
    list3->next->next = createListElement(0, 1, "a");
    list3->next->next->next = createListElement(0, 1, "b");
    list3->next->next->next->next = createListElement(0, 1, "aasf");
    list3->next->next->next->next->next = createListElement(0, 1, "1");
    list3->next->next->next->next->next->next = createListElement(123, 0, NULL);
    list3->next->next->next->next->next->next->next = createListElement(123, 0, NULL);

    // Filter and print lists
    ListElement* result1 = filterList(list1);
    ListElement* result2 = filterList(list2);
    ListElement* result3 = filterList(list3);

    printList(result1); // [1, 2]
    printList(result2); // [1, 0, 15]
    printList(result3); // [1, 2, 123]

    return 0;
}