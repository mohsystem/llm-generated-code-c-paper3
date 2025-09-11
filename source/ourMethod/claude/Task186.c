
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy = {0, NULL};
    struct ListNode* curr = &dummy;
    
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    
    curr->next = l1 ? l1 : l2;
    return dummy.next;
}

struct ListNode* mergeKListsHelper(struct ListNode** lists, int start, int end) {
    if (start == end) return lists[start];
    if (start > end) return NULL;
    
    int mid = start + (end - start) / 2;
    struct ListNode* left = mergeKListsHelper(lists, start, mid);
    struct ListNode* right = mergeKListsHelper(lists, mid + 1, end);
    return mergeTwoLists(left, right);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    return mergeKListsHelper(lists, 0, listsSize - 1);
}

void printList(struct ListNode* head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\\n");
}

struct ListNode* createNode(int value) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = value;
    node->next = NULL;
    return node;
}

int main() {
    // Test case 1: [[1,4,5],[1,3,4],[2,6]]
    struct ListNode** test1 = (struct ListNode**)malloc(3 * sizeof(struct ListNode*));
    test1[0] = createNode(1);
    test1[0]->next = createNode(4);
    test1[0]->next->next = createNode(5);
    
    test1[1] = createNode(1);
    test1[1]->next = createNode(3);
    test1[1]->next->next = createNode(4);
    
    test1[2] = createNode(2);
    test1[2]->next = createNode(6);
    
    // Test case 2: []
    struct ListNode** test2 = NULL;
    
    // Test case 3: [[]]
    struct ListNode** test3 = (struct ListNode**)malloc(sizeof(struct ListNode*));
    test3[0] = NULL;
    
    // Test case 4: [[1]]
    struct ListNode** test4 = (struct ListNode**)malloc(sizeof(struct ListNode*));
    test4[0] = createNode(1);
    
    // Test case 5: [[1,2],[3,4]]
    struct ListNode** test5 = (struct ListNode**)malloc(2 * sizeof(struct ListNode*));
    test5[0] = createNode(1);
    test5[0]->next = createNode(2);
    test5[1] = createNode(3);
    test5[1]->next = createNode(4);
    
    printList(mergeKLists(test1, 3));
    printList(mergeKLists(test2, 0));
    printList(mergeKLists(test3, 1));
    printList(mergeKLists(test4, 1));
    printList(mergeKLists(test5, 2));
    
    // Free memory (implementation omitted for brevity)
    return 0;
}
