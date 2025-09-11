
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* curr = dummy;
    
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
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}

struct ListNode* mergeKListsHelper(struct ListNode** lists, int start, int end) {
    if (start == end) return lists[start];
    if (start + 1 == end) return mergeTwoLists(lists[start], lists[end]);
    
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

struct ListNode* createNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

int main() {
    // Test case 1: [[1,4,5],[1,3,4],[2,6]]
    struct ListNode* lists1[3];
    lists1[0] = createNode(1);
    lists1[0]->next = createNode(4);
    lists1[0]->next->next = createNode(5);
    
    lists1[1] = createNode(1);
    lists1[1]->next = createNode(3);
    lists1[1]->next->next = createNode(4);
    
    lists1[2] = createNode(2);
    lists1[2]->next = createNode(6);
    
    printList(mergeKLists(lists1, 3));
    
    // Test case 2: []
    printList(mergeKLists(NULL, 0));
    
    // Test case 3: [[]]
    struct ListNode* lists3[1] = {NULL};
    printList(mergeKLists(lists3, 1));
    
    // Test case 4: [[1]]
    struct ListNode* lists4[1];
    lists4[0] = createNode(1);
    printList(mergeKLists(lists4, 1));
    
    // Test case 5: [[1,2,3],[4,5,6],[7,8,9]]
    struct ListNode* lists5[3];
    lists5[0] = createNode(1);
    lists5[0]->next = createNode(2);
    lists5[0]->next->next = createNode(3);
    
    lists5[1] = createNode(4);
    lists5[1]->next = createNode(5);
    lists5[1]->next->next = createNode(6);
    
    lists5[2] = createNode(7);
    lists5[2]->next = createNode(8);
    lists5[2]->next->next = createNode(9);
    
    printList(mergeKLists(lists5, 3));
    
    return 0;
}
