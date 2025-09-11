
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
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

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    
    int interval = 1;
    while (interval < listsSize) {
        for (int i = 0; i < listsSize - interval; i += interval * 2) {
            lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
        }
        interval *= 2;
    }
    
    return lists[0];
}

int main() {
    // Test case 1
    struct ListNode* lists1[3];
    lists1[0] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[0]->val = 1;
    lists1[0]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[0]->next->val = 4;
    lists1[0]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[0]->next->next->val = 5;
    lists1[0]->next->next->next = NULL;
    
    lists1[1] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[1]->val = 1;
    lists1[1]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[1]->next->val = 3;
    lists1[1]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[1]->next->next->val = 4;
    lists1[1]->next->next->next = NULL;
    
    lists1[2] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[2]->val = 2;
    lists1[2]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists1[2]->next->val = 6;
    lists1[2]->next->next = NULL;
    
    struct ListNode* result1 = mergeKLists(lists1, 3);
    
    // Test case 2
    struct ListNode** lists2 = NULL;
    struct ListNode* result2 = mergeKLists(lists2, 0);
    
    // Test case 3
    struct ListNode* lists3[1] = {NULL};
    struct ListNode* result3 = mergeKLists(lists3, 1);
    
    // Test case 4
    struct ListNode* lists4[2];
    lists4[0] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists4[0]->val = 1;
    lists4[0]->next = NULL;
    lists4[1] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists4[1]->val = 2;
    lists4[1]->next = NULL;
    
    struct ListNode* result4 = mergeKLists(lists4, 2);
    
    // Test case 5
    struct ListNode* lists5[3];
    lists5[0] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists5[0]->val = 1;
    lists5[0]->next = NULL;
    lists5[1] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists5[1]->val = 1;
    lists5[1]->next = NULL;
    lists5[2] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists5[2]->val = 2;
    lists5[2]->next = NULL;
    
    struct ListNode* result5 = mergeKLists(lists5, 3);
    
    return 0;
}
