#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

// Function to create a new node
ListNode* createNode(int val) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Function to merge k sorted linked lists using a min heap
ListNode* mergeKLists(ListNode** lists, int k) {
    // Create a min heap
    ListNode** heap = (ListNode**)malloc(k * sizeof(ListNode*));
    for (int i = 0; i < k; i++) {
        heap[i] = lists[i];
    }

    ListNode dummy = {0, NULL};
    ListNode* current = &dummy;

    while (1) {
        int minIndex = -1;
        for (int i = 0; i < k; i++) {
            if (heap[i] && (minIndex == -1 || heap[i]->val < heap[minIndex]->val)) {
                minIndex = i;
            }
        }

        if (minIndex == -1) break;

        current->next = heap[minIndex];
        current = current->next;
        heap[minIndex] = heap[minIndex]->next;
    }

    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main() {
    // Test case 1
    ListNode* list1 = createNode(1);
    list1->next = createNode(4);
    list1->next->next = createNode(5);

    ListNode* list2 = createNode(1);
    list2->next = createNode(3);
    list2->next->next = createNode(4);

    ListNode* list3 = createNode(2);
    list3->next = createNode(6);

    ListNode* lists[] = {list1, list2, list3};
    ListNode* result = mergeKLists(lists, 3);
    printList(result);

    // Test case 2
    ListNode** emptyLists[] = {};
    result = mergeKLists(emptyLists, 0);
    printList(result);

    // Test case 3
    ListNode** singleEmptyList[] = {NULL};
    result = mergeKLists(singleEmptyList, 1);
    printList(result);

    return 0;
}