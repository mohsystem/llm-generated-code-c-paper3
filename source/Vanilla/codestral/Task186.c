// C code

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    if (!listsSize) return NULL;

    struct ListNode dummy = {0, NULL};
    struct ListNode* tail = &dummy;

    while (1) {
        int minIndex = -1;
        for (int i = 0; i < listsSize; ++i) {
            if (lists[i] && (minIndex == -1 || lists[i]->val < lists[minIndex]->val)) {
                minIndex = i;
            }
        }

        if (minIndex == -1) break;

        tail->next = lists[minIndex];
        tail = tail->next;
        lists[minIndex] = lists[minIndex]->next;
    }
    return dummy.next;
}

void printList(struct ListNode* node) {
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct ListNode* lists1[3] = {
        (struct ListNode*)malloc(sizeof(struct ListNode)),
        (struct ListNode*)malloc(sizeof(struct ListNode)),
        (struct ListNode*)malloc(sizeof(struct ListNode))
    };
    lists1[0]->val = 1;
    lists1[0]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[0]->next->val = 4;
    lists1[0]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[0]->next->next->val = 5;
    lists1[0]->next->next->next = NULL;

    lists1[1]->val = 1;
    lists1[1]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[1]->next->val = 3;
    lists1[1]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[1]->next->next->val = 4;
    lists1[1]->next->next->next = NULL;

    lists1[2]->val = 2;
    lists1[2]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[2]->next->val = 6;
    lists1[2]->next->next = NULL;

    printList(mergeKLists(lists1, 3));

    struct ListNode* lists2[0] = {};
    printList(mergeKLists(lists2, 0));

    struct ListNode* lists3[1] = {NULL};
    printList(mergeKLists(lists3, 1));

    return 0;
}