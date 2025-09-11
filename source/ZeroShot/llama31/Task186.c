#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* mergeKLists(ListNode** lists, int k) {
    if (k == 0) return NULL;
    return merge(lists, 0, k - 1);
}

ListNode* merge(ListNode** lists, int start, int end) {
    if (start == end) return lists[start];
    int mid = start + (end - start) / 2;
    ListNode* left = merge(lists, start, mid);
    ListNode* right = merge(lists, mid + 1, end);
    return mergeTwoLists(left, right);
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));
    dummy->val = 0;
    dummy->next = NULL;
    ListNode* current = dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    current->next = l1 ? l1 : l2;
    return dummy->next;
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
    ListNode* lists1[] = {
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode))
    };
    lists1[0]->val = 1; lists1[0]->next = lists1[1];
    lists1[1]->val = 4; lists1[1]->next = lists1[2];
    lists1[2]->val = 5; lists1[2]->next = NULL;
    lists1[3]->val = 1; lists1[3]->next = lists1[4];
    lists1[4]->val = 3; lists1[4]->next = lists1[5];
    lists1[5]->val = 4; lists1[5]->next = NULL;
    lists1[6]->val = 2; lists1[6]->next = lists1[7];
    lists1[7]->val = 6; lists1[7]->next = NULL;

    ListNode** arr1 = lists1;
    ListNode* result1 = mergeKLists(arr1, 3);
    printf("Test Case 1:\n");
    printList(result1);

    // Test case 2
    ListNode** lists2 = NULL;
    ListNode* result2 = mergeKLists(lists2, 0);
    printf("Test Case 2:\n");
    printList(result2);

    // Test case 3
    ListNode** lists3 = (ListNode**)malloc(sizeof(ListNode*));
    *lists3 = NULL;
    ListNode* result3 = mergeKLists(lists3, 1);
    printf("Test Case 3:\n");
    printList(result3);

    // Test case 4
    ListNode* lists4[] = {
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode))
    };
    lists4[0]->val = 1; lists4[0]->next = lists4[1];
    lists4[1]->val = 2; lists4[1]->next = lists4[2];
    lists4[2]->val = 3; lists4[2]->next = NULL;
    lists4[3]->val = 4; lists4[3]->next = lists4[4];
    lists4[4]->val = 5; lists4[4]->next = lists4[5];
    lists4[5]->val = 6; lists4[5]->next = NULL;
    lists4[6]->val = 7; lists4[6]->next = lists4[7];
    lists4[7]->val = 8; lists4[7]->next = NULL;

    ListNode** arr4 = lists4;
    ListNode* result4 = mergeKLists(arr4, 3);
    printf("Test Case 4:\n");
    printList(result4);

    // Test case 5
    ListNode* lists5[] = {
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode))
    };
    lists5[0]->val = -10; lists5[0]->next = lists5[1];
    lists5[1]->val = -9; lists5[1]->next = lists5[2];
    lists5[2]->val = -8; lists5[2]->next = NULL;
    lists5[3]->val = -7; lists5[3]->next = lists5[4];
    lists5[4]->val = -6; lists5[4]->next = lists5[5];
    lists5[5]->val = -5; lists5[5]->next = NULL;
    lists5[6]->val = -4; lists5[6]->next = lists5[7];
    lists5[7]->val = -3;