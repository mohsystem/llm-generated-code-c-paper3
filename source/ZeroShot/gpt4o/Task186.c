#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = NULL;
    struct ListNode* current = dummy;

    int minIndex;
    struct ListNode* minNode;

    while (1) {
        minNode = NULL;
        minIndex = -1;
        for (int i = 0; i < listsSize; i++) {
            if (lists[i] != NULL) {
                if (minNode == NULL || lists[i]->val < minNode->val) {
                    minNode = lists[i];
                    minIndex = i;
                }
            }
        }
        if (minNode == NULL) break;

        current->next = minNode;
        current = current->next;
        lists[minIndex] = lists[minIndex]->next;
    }

    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}

void printList(struct ListNode* node) {
    while (node != NULL) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int main() {
    // Test cases
    struct ListNode n1 = {1, NULL}, n2 = {4, NULL}, n3 = {5, NULL};
    n1.next = &n2;
    n2.next = &n3;

    struct ListNode n4 = {1, NULL}, n5 = {3, NULL}, n6 = {4, NULL};
    n4.next = &n5;
    n5.next = &n6;

    struct ListNode n7 = {2, NULL}, n8 = {6, NULL};
    n7.next = &n8;

    struct ListNode* lists1[] = {&n1, &n4, &n7};
    printList(mergeKLists(lists1, 3));

    struct ListNode* lists2[] = {};
    printList(mergeKLists(lists2, 0));

    struct ListNode n9 = {0, NULL};
    struct ListNode* lists3[] = {&n9};
    printList(mergeKLists(lists3, 1));

    struct ListNode n10 = {-10, NULL}, n11 = {-9, NULL};
    n10.next = &n11;
    struct ListNode n12 = {-5, NULL}, n13 = {-4, NULL};
    n12.next = &n13;
    struct ListNode n14 = {4, NULL}, n15 = {6, NULL};
    n14.next = &n15;

    struct ListNode* lists4[] = {&n10, &n12, &n14};
    printList(mergeKLists(lists4, 3));

    struct ListNode* lists5[] = {NULL, &n14};
    printList(mergeKLists(lists5, 2));

    return 0;
}