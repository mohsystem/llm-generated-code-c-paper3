#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* mergeKLists(ListNode** lists, int listsSize) {
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));
    ListNode* current = dummy;
    int minIndex;
    while (1) {
        minIndex = -1;
        for (int i = 0; i < listsSize; ++i) {
            if (lists[i] && (minIndex == -1 || lists[i]->val < lists[minIndex]->val)) {
                minIndex = i;
            }
        }
        if (minIndex == -1) break;
        current->next = lists[minIndex];
        current = current->next;
        lists[minIndex] = lists[minIndex]->next;
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
    ListNode* lists[3];
    lists[0] = (ListNode*)malloc(sizeof(ListNode));
    lists[0]->val = 1;
    lists[0]->next = (ListNode*)malloc(sizeof(ListNode));
    lists[0]->next->val = 4;
    lists[0]->next->next = (ListNode*)malloc(sizeof(ListNode));
    lists[0]->next->next->val = 5;
    lists[0]->next->next->next = NULL;

    lists[1] = (ListNode*)malloc(sizeof(ListNode));
    lists[1]->val = 1;
    lists[1]->next = (ListNode*)malloc(sizeof(ListNode));
    lists[1]->next->val = 3;
    lists[1]->next->next = (ListNode*)malloc(sizeof(ListNode));
    lists[1]->next->next->val = 4;
    lists[1]->next->next->next = NULL;

    lists[2] = (ListNode*)malloc(sizeof(ListNode));
    lists[2]->val = 2;
    lists[2]->next = (ListNode*)malloc(sizeof(ListNode));
    lists[2]->next->val = 6;
    lists[2]->next->next = NULL;

    ListNode* result = mergeKLists(lists, 3);
    printList(result);

    ListNode* lists2[] = {};
    result = mergeKLists(lists2, 0);
    printList(result);

    ListNode* lists3[] = {NULL};
    result = mergeKLists(lists3, 1);
    printList(result);

    ListNode* lists4[1];
    lists4[0] = (ListNode*)malloc(sizeof(ListNode));
    lists4[0]->val = 1;
    lists4[0]->next = NULL;
    result = mergeKLists(lists4, 1);
    printList(result);

    ListNode* lists5[2];
    lists5[0] = (ListNode*)malloc(sizeof(ListNode));
    lists5[0]->val = -1;
    lists5[0]->next = (ListNode*)malloc(sizeof(ListNode));
    lists5[0]->next->val = 3;
    lists5[0]->next->next = NULL;
    lists5[1] = (ListNode*)malloc(sizeof(ListNode));
    lists5[1]->val = 1;
    lists5[1]->next = NULL;
    result = mergeKLists(lists5, 2);
    printList(result);

    return 0;
}