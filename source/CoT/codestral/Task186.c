// Node structure for linked list
struct ListNode {
    int val;
    struct ListNode *next;
};

// Function to merge k sorted linked lists
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0)
        return NULL;
    while (listsSize > 1) {
        lists[listsSize - 2] = mergeTwoLists(lists[listsSize - 1], lists[listsSize - 2]);
        listsSize--;
    }
    return lists[0];
}

// Function to merge two sorted linked lists
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* tail = dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    if (l1)
        tail->next = l1;
    else
        tail->next = l2;
    return dummy->next;
}

// Main function for testing
int main() {
    struct ListNode* lists[3];
    lists[0] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[0]->val = 1;
    lists[0]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[0]->next->val = 4;
    lists[0]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[0]->next->next->val = 5;
    lists[0]->next->next->next = NULL;

    lists[1] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[1]->val = 1;
    lists[1]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[1]->next->val = 3;
    lists[1]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[1]->next->next->val = 4;
    lists[1]->next->next->next = NULL;

    lists[2] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[2]->val = 2;
    lists[2]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[2]->next->val = 6;
    lists[2]->next->next = NULL;

    struct ListNode* result = mergeKLists(lists, 3);
    while (result) {
        printf("%d ", result->val);
        result = result->next;
    }
    return 0;
}