#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

ListNode* mergeKLists(ListNode** lists, int listsSize) {
    ListNode* head = NULL;
    ListNode** tail = &head;
    
    while (1) {
        int minIndex = -1;
        for (int i = 0; i < listsSize; ++i) {
            if (lists[i] && (minIndex == -1 || lists[i]->val < lists[minIndex]->val)) {
                minIndex = i;
            }
        }
        if (minIndex == -1) break;
        *tail = lists[minIndex];
        lists[minIndex] = lists[minIndex]->next;
        tail = &(*tail)->next;
    }
    return head;
}

void printList(ListNode* node) {
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int main() {
    // Example 1
    ListNode l1a = {1, NULL}, l1b = {4, NULL}, l1c = {5, NULL};
    l1a.next = &l1b;
    l1b.next = &l1c;
    
    ListNode l2a = {1, NULL}, l2b = {3, NULL}, l2c = {4, NULL};
    l2a.next = &l2b;
    l2b.next = &l2c;
    
    ListNode l3a = {2, NULL}, l3b = {6, NULL};
    l3a.next = &l3b;
    
    ListNode* lists1[] = {&l1a, &l2a, &l3a};
    printList(mergeKLists(lists1, 3));

    // Example 2
    ListNode* lists2[] = {};
    printList(mergeKLists(lists2, 0));

    // Example 3
    ListNode l0 = {0, NULL};
    ListNode* lists3[] = {&l0};
    printList(mergeKLists(lists3, 1));

    // Test case 4
    ListNode l1 = {1, NULL};
    ListNode* lists4[] = {&l1};
    printList(mergeKLists(lists4, 1));

    // Test case 5
    ListNode l5a = {5, NULL}, l5b = {10, NULL};
    l5a.next = &l5b;
    
    ListNode l6a = {3, NULL}, l6b = {4, NULL};
    l6a.next = &l6b;
    
    ListNode l7a = {8, NULL}, l7b = {9, NULL};
    l7a.next = &l7b;
    
    ListNode* lists5[] = {&l5a, &l6a, &l7a};
    printList(mergeKLists(lists5, 3));

    return 0;
}