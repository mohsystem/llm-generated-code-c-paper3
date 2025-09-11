// Define the ListNode struct for linked list nodes
struct ListNode {
    int val;
    struct ListNode *next;
};

// Define the mergeKLists function
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    // Edge case: if the lists array is null or empty, return null
    if (lists == NULL || listsSize == 0) return NULL;

    // Start merging the lists from the first list
    struct ListNode* result = lists[0];

    // Iterate through the rest of the lists
    for (int i = 1; i < listsSize; i++) {
        // Merge the current list with the result list
        result = mergeTwoLists(result, lists[i]);
    }

    // Return the merged list
    return result;
}

// Define the mergeTwoLists function to merge two sorted linked lists
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    // Create a dummy node to serve as the head of the merged list
    struct ListNode dummy = {0, NULL};
    struct ListNode* current = &dummy;

    // Iterate through both lists
    while (l1 != NULL && l2 != NULL) {
        // If the value of l1 is less than or equal to the value of l2, append l1 to the merged list
        if (l1->val <= l2->val) {
            current->next = l1;
            l1 = l1->next;
        }
        // Otherwise, append l2 to the merged list
        else {
            current->next = l2;
            l2 = l2->next;
        }
        // Move to the next node in the merged list
        current = current->next;
    }

    // If there are remaining nodes in l1, append them to the merged list
    if (l1 != NULL) current->next = l1;
    // If there are remaining nodes in l2, append them to the merged list
    else current->next = l2;

    // Return the head of the merged list
    return dummy.next;
}

// Define the main function for testing
int main() {
    // Test case 1
    struct ListNode* lists1[] = {
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

    struct ListNode* result1 = mergeKLists(lists1, 3);
    // Print the merged list
    while (result1 != NULL) {
        printf("%d ", result1->val);
        result1 = result1->next;
    }
    printf("\n");

    // Test case 2
    struct ListNode* lists2[] = {};
    struct ListNode* result2 = mergeKLists(lists2, 0);
    // Print the merged list
    if (result2 == NULL) printf("[]\n");

    // Test case 3
    struct ListNode* lists3[] = {NULL};
    struct ListNode* result3 = mergeKLists(lists3, 1);
    // Print the merged list
    if (result3 == NULL) printf("[]\n");

    return 0;
}