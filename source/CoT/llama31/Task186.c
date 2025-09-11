// Note: C does not support priority queues natively, so this implementation uses a simple array-based approach.
// This is less efficient than using a priority queue but serves as an example.

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int k) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = NULL;

    struct ListNode* current = dummy;

    while (1) {
        int minVal = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < k; i++) {
            if (lists[i] && lists[i]->val < minVal) {
                minVal = lists[i]->val;
                minIndex = i;
            }
        }

        if (minIndex == -1) break;

        current->next = lists[minIndex];
        current = current->next;
        lists[minIndex] = lists[minIndex]->next;
    }

    return dummy->next;
}

void printList(struct ListNode* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main() {
    // Test case 1
    struct ListNode* lists1[] = {
        (struct ListNode*)malloc(sizeof(struct ListNode)),
        (struct ListNode*)malloc(sizeof(struct ListNode)),
        (struct ListNode*)malloc(sizeof(struct ListNode))
    };
    lists1[0]->val = 1; lists1[0]->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists1[0]->next->val = 4; lists1[0]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists1[0]->next->next->val = 5; lists1[0]->next->next->next = NULL;
    lists1[1]->val = 1; lists1[1]->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists1[1]->next->val = 3; lists1[1]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists1[1]->next->next->val = 4; lists1[1]->next->next->next = NULL;
    lists1[2]->val = 2; lists1[2]->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists1[2]->next->val = 6; lists1[2]->next->next = NULL;

    struct ListNode* head1 = mergeKLists(lists1, 3);
    printList(head1);

    // Test case 2
    struct ListNode** lists2 = NULL;
    struct ListNode* head2 = mergeKLists(lists2, 0);
    printList(head2);

    // Test case 3
    struct ListNode** lists3 = (struct ListNode**)malloc(sizeof(struct ListNode*));
    lists3[0] = NULL;
    struct ListNode* head3 = mergeKLists(lists3, 1);
    printList(head3);

    // Test case 4
    struct ListNode* lists4[] = {
        (struct ListNode*)malloc(sizeof(struct ListNode)),
        (struct ListNode*)malloc(sizeof(struct ListNode))
    };
    lists4[0]->val = 1; lists4[0]->next = NULL;
    lists4[1]->val = 2; lists4[1]->next = NULL;

    struct ListNode* head4 = mergeKLists(lists4, 2);
    printList(head4);

    // Test case 5
    struct ListNode* lists5[] = {
        (struct ListNode*)malloc(sizeof(struct ListNode)),
        (struct ListNode*)malloc(sizeof(struct ListNode)),
        (struct ListNode*)malloc(sizeof(struct ListNode))
    };
    lists5[0]->val = 1; lists5[0]->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists5[0]->next->val = 3; lists5[0]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists5[0]->next->next->val = 7; lists5[0]->next->next->next = NULL;
    lists5[1]->val = 2; lists5[1]->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists5[1]->next->val = 4; lists5[1]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode)); lists5[1]->next->next->val = 8; lists5[1]->next->next->next = NULL;
    lists5[2]->val = 9; lists5[2]->next = NULL;

    struct ListNode* head5 = mergeKLists(lists5, 3);
    printList(head5);

    return 0;
}