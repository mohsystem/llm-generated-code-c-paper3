#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* mergeKLists(ListNode** lists, int listsSize) {
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));
    dummy->val = 0;
    dummy->next = NULL;
    ListNode* current = dummy;

    int done = 0;
    while (!done) {
        done = 1;
        int minIndex = -1;
        for (int i = 0; i < listsSize; i++) {
            if (lists[i] != NULL) {
                if (minIndex == -1 || lists[i]->val < lists[minIndex]->val) {
                    minIndex = i;
                }
                done = 0;
            }
        }
        if (minIndex != -1) {
            current->next = lists[minIndex];
            lists[minIndex] = lists[minIndex]->next;
            current = current->next;
        }
    }

    current = dummy->next;
    free(dummy);
    return current;
}

void printList(ListNode* node) {
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int main() {
    // Test case 1
    ListNode* l1 = (ListNode*)malloc(sizeof(ListNode));
    l1->val = 1;
    l1->next = (ListNode*)malloc(sizeof(ListNode));
    l1->next->val = 4;
    l1->next->next = (ListNode*)malloc(sizeof(ListNode));
    l1->next->next->val = 5;
    l1->next->next->next = NULL;

    ListNode* l2 = (ListNode*)malloc(sizeof(ListNode));
    l2->val = 1;
    l2->next = (ListNode*)malloc(sizeof(ListNode));
    l2->next->val = 3;
    l2->next->next = (ListNode*)malloc(sizeof(ListNode));
    l2->next->next->val = 4;
    l2->next->next->next = NULL;

    ListNode* l3 = (ListNode*)malloc(sizeof(ListNode));
    l3->val = 2;
    l3->next = (ListNode*)malloc(sizeof(ListNode));
    l3->next->val = 6;
    l3->next->next = NULL;

    ListNode* lists1[] = {l1, l2, l3};
    ListNode* result1 = mergeKLists(lists1, 3);
    printList(result1);

    // Test case 2
    ListNode* lists2[] = {};
    ListNode* result2 = mergeKLists(lists2, 0);
    printList(result2);

    // Test case 3
    ListNode* l4 = (ListNode*)malloc(sizeof(ListNode));
    l4->val = 0;
    l4->next = NULL;
    ListNode* lists3[] = {l4};
    ListNode* result3 = mergeKLists(lists3, 1);
    printList(result3);

    // Test case 4
    ListNode* lists4[] = {NULL};
    ListNode* result4 = mergeKLists(lists4, 1);
    printList(result4);

    // Test case 5
    ListNode* l5 = (ListNode*)malloc(sizeof(ListNode));
    l5->val = -1;
    l5->next = (ListNode*)malloc(sizeof(ListNode));
    l5->next->val = 0;
    l5->next->next = (ListNode*)malloc(sizeof(ListNode));
    l5->next->next->val = 1;
    l5->next->next->next = NULL;

    ListNode* lists5[] = {l5};
    ListNode* result5 = mergeKLists(lists5, 1);
    printList(result5);

    return 0;
}