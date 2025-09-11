
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    
    struct ListNode* result = lists[0];
    for (int i = 1; i < listsSize; i++) {
        result = mergeTwoLists(result, lists[i]);
    }
    
    return result;
}

void printList(struct ListNode* head) {
    while (head) {
        printf("%d->", head->val);
        head = head->next;
    }
    printf("NULL\\n");
}

struct ListNode* createNode(int value) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = value;
    node->next = NULL;
    return node;
}

int main() {
    // Test case 1
    struct ListNode* lists1[3];
    lists1[0] = createNode(1);
    lists1[0]->next = createNode(4);
    lists1[0]->next->next = createNode(5);
    
    lists1[1] = createNode(1);
    lists1[1]->next = createNode(3);
    lists1[1]->next->next = createNode(4);
    
    lists1[2] = createNode(2);
    lists1[2]->next = createNode(6);
    
    struct ListNode* result1 = mergeKLists(lists1, 3);
    printList(result1);
    
    // Test case 2
    struct ListNode* lists2[0];
    struct ListNode* result2 = mergeKLists(lists2, 0);
    printList(result2);
    
    // Test case 3
    struct ListNode* lists3[1] = {NULL};
    struct ListNode* result3 = mergeKLists(lists3, 1);
    printList(result3);
    
    // Test case 4
    struct ListNode* lists4[1];
    lists4[0] = createNode(1);
    struct ListNode* result4 = mergeKLists(lists4, 1);
    printList(result4);
    
    // Test case 5
    struct ListNode* lists5[2];
    lists5[0] = createNode(2);
    lists5[1] = createNode(1);
    struct ListNode* result5 = mergeKLists(lists5, 2);
    printList(result5);
    
    return 0;
}
